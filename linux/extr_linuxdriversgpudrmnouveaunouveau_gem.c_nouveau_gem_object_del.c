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
struct ttm_buffer_object {int /*<<< orphan*/  sg; int /*<<< orphan*/  bdev; } ;
struct nouveau_drm {TYPE_1__* dev; } ;
struct nouveau_bo {struct ttm_buffer_object bo; } ;
struct drm_gem_object {int /*<<< orphan*/ * filp; scalar_t__ import_attach; } ;
struct device {int dummy; } ;
struct TYPE_2__ {struct device* dev; } ;

/* Variables and functions */
 int EACCES ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  drm_gem_object_release (struct drm_gem_object*) ; 
 int /*<<< orphan*/  drm_prime_gem_destroy (struct drm_gem_object*,int /*<<< orphan*/ ) ; 
 struct nouveau_drm* nouveau_bdev (int /*<<< orphan*/ ) ; 
 struct nouveau_bo* nouveau_gem_object (struct drm_gem_object*) ; 
 int pm_runtime_get_sync (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_mark_last_busy (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_put_autosuspend (struct device*) ; 
 int /*<<< orphan*/  ttm_bo_unref (struct ttm_buffer_object**) ; 

void
nouveau_gem_object_del(struct drm_gem_object *gem)
{
	struct nouveau_bo *nvbo = nouveau_gem_object(gem);
	struct nouveau_drm *drm = nouveau_bdev(nvbo->bo.bdev);
	struct ttm_buffer_object *bo = &nvbo->bo;
	struct device *dev = drm->dev->dev;
	int ret;

	ret = pm_runtime_get_sync(dev);
	if (WARN_ON(ret < 0 && ret != -EACCES))
		return;

	if (gem->import_attach)
		drm_prime_gem_destroy(gem, nvbo->bo.sg);

	drm_gem_object_release(gem);

	/* reset filp so nouveau_bo_del_ttm() can test for it */
	gem->filp = NULL;
	ttm_bo_unref(&bo);

	pm_runtime_mark_last_busy(dev);
	pm_runtime_put_autosuspend(dev);
}