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
struct bio_vec {int /*<<< orphan*/  bv_page; } ;
struct bio {int bi_vcnt; struct bio_vec* bi_io_vec; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  __free_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  alloc_page (int /*<<< orphan*/ ) ; 

int bch_bio_alloc_pages(struct bio *bio, gfp_t gfp_mask)
{
	int i;
	struct bio_vec *bv;

	/*
	 * This is called on freshly new bio, so it is safe to access the
	 * bvec table directly.
	 */
	for (i = 0, bv = bio->bi_io_vec; i < bio->bi_vcnt; bv++, i++) {
		bv->bv_page = alloc_page(gfp_mask);
		if (!bv->bv_page) {
			while (--bv >= bio->bi_io_vec)
				__free_page(bv->bv_page);
			return -ENOMEM;
		}
	}

	return 0;
}