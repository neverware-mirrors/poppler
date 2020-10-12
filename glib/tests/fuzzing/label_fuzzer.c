#include <stdint.h>
#include <poppler.h>
#include <cairo.h>

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    GError *err = NULL;
    PopplerDocument *doc;
    PopplerPage *page;
    int npages, n;

    doc = poppler_document_new_from_data(data, size, NULL, &err);
    if (doc == NULL) {
        g_error_free(err);
        return 0;
    }

    npages = poppler_document_get_n_pages(doc);
    if (npages < 1) {
        return 0;
    }

    for (n = 0; n < poppler_document_get_n_pages(doc); n++) {
        page = poppler_document_get_page_by_label(doc, data);
        if (!page) {
            continue;
        }
        g_object_unref(page);
    }
    return 0;
}
