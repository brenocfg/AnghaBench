#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ttm_buffer_object {TYPE_1__* bdev; } ;
struct ttm_bo_global {int /*<<< orphan*/  lru_lock; } ;
struct TYPE_2__ {struct ttm_bo_global* glob; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ttm_bo_del_from_lru (struct ttm_buffer_object*) ; 

void ttm_bo_del_sub_from_lru(struct ttm_buffer_object *bo)
{
	struct ttm_bo_global *glob = bo->bdev->glob;

	spin_lock(&glob->lru_lock);
	ttm_bo_del_from_lru(bo);
	spin_unlock(&glob->lru_lock);
}