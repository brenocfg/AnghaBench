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
struct ttm_buffer_object {int /*<<< orphan*/  list_kref; int /*<<< orphan*/  lru; int /*<<< orphan*/  swap; struct ttm_bo_device* bdev; } ;
struct ttm_bo_device {TYPE_1__* driver; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* del_from_lru_notify ) (struct ttm_buffer_object*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct ttm_buffer_object*) ; 
 int /*<<< orphan*/  ttm_bo_ref_bug ; 

void ttm_bo_del_from_lru(struct ttm_buffer_object *bo)
{
	struct ttm_bo_device *bdev = bo->bdev;
	bool notify = false;

	if (!list_empty(&bo->swap)) {
		list_del_init(&bo->swap);
		kref_put(&bo->list_kref, ttm_bo_ref_bug);
		notify = true;
	}
	if (!list_empty(&bo->lru)) {
		list_del_init(&bo->lru);
		kref_put(&bo->list_kref, ttm_bo_ref_bug);
		notify = true;
	}

	if (notify && bdev->driver->del_from_lru_notify)
		bdev->driver->del_from_lru_notify(bo);
}