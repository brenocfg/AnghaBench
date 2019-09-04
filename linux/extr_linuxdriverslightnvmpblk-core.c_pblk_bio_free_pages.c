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
struct bio_vec {int /*<<< orphan*/  bv_page; } ;
struct bio {int bi_vcnt; struct bio_vec* bi_io_vec; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  mempool_free (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void pblk_bio_free_pages(struct pblk *pblk, struct bio *bio, int off,
			 int nr_pages)
{
	struct bio_vec bv;
	int i;

	WARN_ON(off + nr_pages != bio->bi_vcnt);

	for (i = off; i < nr_pages + off; i++) {
		bv = bio->bi_io_vec[i];
		mempool_free(bv.bv_page, &pblk->page_bio_pool);
	}
}