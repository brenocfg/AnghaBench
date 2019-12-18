#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct pblk {int /*<<< orphan*/  page_bio_pool; } ;
struct page {int dummy; } ;
struct bio_vec {int bv_len; struct page* bv_page; } ;
struct bio {int bi_vcnt; struct bio_vec* bi_io_vec; } ;

/* Variables and functions */
 scalar_t__ PBLK_EXPOSED_PAGE_SIZE ; 
 int /*<<< orphan*/  mempool_free (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void pblk_bio_free_pages(struct pblk *pblk, struct bio *bio, int off,
			 int nr_pages)
{
	struct bio_vec *bv;
	struct page *page;
	int i, e, nbv = 0;

	for (i = 0; i < bio->bi_vcnt; i++) {
		bv = &bio->bi_io_vec[i];
		page = bv->bv_page;
		for (e = 0; e < bv->bv_len; e += PBLK_EXPOSED_PAGE_SIZE, nbv++)
			if (nbv >= off)
				mempool_free(page++, &pblk->page_bio_pool);
	}
}