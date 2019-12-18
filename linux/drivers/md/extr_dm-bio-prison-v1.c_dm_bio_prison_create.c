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
struct dm_bio_prison {int /*<<< orphan*/  cells; int /*<<< orphan*/  cell_pool; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MIN_CELLS ; 
 int /*<<< orphan*/  RB_ROOT ; 
 int /*<<< orphan*/  _cell_cache ; 
 int /*<<< orphan*/  kfree (struct dm_bio_prison*) ; 
 struct dm_bio_prison* kzalloc (int,int /*<<< orphan*/ ) ; 
 int mempool_init_slab_pool (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

struct dm_bio_prison *dm_bio_prison_create(void)
{
	struct dm_bio_prison *prison = kzalloc(sizeof(*prison), GFP_KERNEL);
	int ret;

	if (!prison)
		return NULL;

	spin_lock_init(&prison->lock);

	ret = mempool_init_slab_pool(&prison->cell_pool, MIN_CELLS, _cell_cache);
	if (ret) {
		kfree(prison);
		return NULL;
	}

	prison->cells = RB_ROOT;

	return prison;
}