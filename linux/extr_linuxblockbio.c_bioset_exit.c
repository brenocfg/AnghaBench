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
struct bio_set {int /*<<< orphan*/ * bio_slab; int /*<<< orphan*/  bvec_pool; int /*<<< orphan*/  bio_pool; int /*<<< orphan*/ * rescue_workqueue; } ;

/* Variables and functions */
 int /*<<< orphan*/  bio_put_slab (struct bio_set*) ; 
 int /*<<< orphan*/  bioset_integrity_free (struct bio_set*) ; 
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mempool_exit (int /*<<< orphan*/ *) ; 

void bioset_exit(struct bio_set *bs)
{
	if (bs->rescue_workqueue)
		destroy_workqueue(bs->rescue_workqueue);
	bs->rescue_workqueue = NULL;

	mempool_exit(&bs->bio_pool);
	mempool_exit(&bs->bvec_pool);

	bioset_integrity_free(bs);
	if (bs->bio_slab)
		bio_put_slab(bs);
	bs->bio_slab = NULL;
}