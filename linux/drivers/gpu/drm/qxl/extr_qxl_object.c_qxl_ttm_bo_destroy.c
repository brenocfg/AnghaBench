#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct ttm_buffer_object {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  mutex; } ;
struct qxl_device {TYPE_1__ gem; } ;
struct TYPE_8__ {TYPE_2__* dev; } ;
struct TYPE_7__ {TYPE_4__ base; } ;
struct qxl_bo {scalar_t__ map_count; TYPE_3__ tbo; int /*<<< orphan*/  list; } ;
struct TYPE_6__ {scalar_t__ dev_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  drm_gem_object_release (TYPE_4__*) ; 
 int /*<<< orphan*/  kfree (struct qxl_bo*) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qxl_surface_evict (struct qxl_device*,struct qxl_bo*,int) ; 
 struct qxl_bo* to_qxl_bo (struct ttm_buffer_object*) ; 

__attribute__((used)) static void qxl_ttm_bo_destroy(struct ttm_buffer_object *tbo)
{
	struct qxl_bo *bo;
	struct qxl_device *qdev;

	bo = to_qxl_bo(tbo);
	qdev = (struct qxl_device *)bo->tbo.base.dev->dev_private;

	qxl_surface_evict(qdev, bo, false);
	WARN_ON_ONCE(bo->map_count > 0);
	mutex_lock(&qdev->gem.mutex);
	list_del_init(&bo->list);
	mutex_unlock(&qdev->gem.mutex);
	drm_gem_object_release(&bo->tbo.base);
	kfree(bo);
}