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
struct bio_set {int /*<<< orphan*/  bio_pool; int /*<<< orphan*/  front_pad; int /*<<< orphan*/  bvec_pool; } ;
struct bio {int /*<<< orphan*/  bi_io_vec; struct bio_set* bi_pool; } ;

/* Variables and functions */
 int /*<<< orphan*/  BVEC_POOL_IDX (struct bio*) ; 
 int /*<<< orphan*/  bio_uninit (struct bio*) ; 
 int /*<<< orphan*/  bvec_free (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct bio*) ; 
 int /*<<< orphan*/  mempool_free (void*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void bio_free(struct bio *bio)
{
	struct bio_set *bs = bio->bi_pool;
	void *p;

	bio_uninit(bio);

	if (bs) {
		bvec_free(&bs->bvec_pool, bio->bi_io_vec, BVEC_POOL_IDX(bio));

		/*
		 * If we have front padding, adjust the bio pointer before freeing
		 */
		p = bio;
		p -= bs->front_pad;

		mempool_free(p, &bs->bio_pool);
	} else {
		/* Bio was allocated by bio_kmalloc() */
		kfree(bio);
	}
}