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
struct bio_set {int /*<<< orphan*/  bio_integrity_pool; int /*<<< orphan*/  bvec_integrity_pool; } ;

/* Variables and functions */
 scalar_t__ biovec_init_pool (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  bip_slab ; 
 int /*<<< orphan*/  mempool_exit (int /*<<< orphan*/ *) ; 
 scalar_t__ mempool_init_slab_pool (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 scalar_t__ mempool_initialized (int /*<<< orphan*/ *) ; 

int bioset_integrity_create(struct bio_set *bs, int pool_size)
{
	if (mempool_initialized(&bs->bio_integrity_pool))
		return 0;

	if (mempool_init_slab_pool(&bs->bio_integrity_pool,
				   pool_size, bip_slab))
		return -1;

	if (biovec_init_pool(&bs->bvec_integrity_pool, pool_size)) {
		mempool_exit(&bs->bio_integrity_pool);
		return -1;
	}

	return 0;
}