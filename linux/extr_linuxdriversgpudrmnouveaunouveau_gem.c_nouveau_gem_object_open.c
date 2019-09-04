#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct nouveau_vma {int dummy; } ;
struct nouveau_drm {TYPE_1__* dev; } ;
struct TYPE_8__ {scalar_t__ oclass; } ;
struct TYPE_9__ {TYPE_2__ object; } ;
struct TYPE_11__ {TYPE_3__ vmm; } ;
struct nouveau_cli {TYPE_6__ vmm; } ;
struct TYPE_10__ {int /*<<< orphan*/  bdev; } ;
struct nouveau_bo {TYPE_4__ bo; } ;
struct drm_gem_object {int dummy; } ;
struct drm_file {int dummy; } ;
struct device {int dummy; } ;
struct TYPE_7__ {struct device* dev; } ;

/* Variables and functions */
 int EACCES ; 
 scalar_t__ NVIF_CLASS_VMM_NV50 ; 
 struct nouveau_drm* nouveau_bdev (int /*<<< orphan*/ ) ; 
 struct nouveau_cli* nouveau_cli (struct drm_file*) ; 
 struct nouveau_bo* nouveau_gem_object (struct drm_gem_object*) ; 
 int nouveau_vma_new (struct nouveau_bo*,TYPE_6__*,struct nouveau_vma**) ; 
 int pm_runtime_get_sync (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_mark_last_busy (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_put_autosuspend (struct device*) ; 
 int ttm_bo_reserve (TYPE_4__*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ttm_bo_unreserve (TYPE_4__*) ; 

int
nouveau_gem_object_open(struct drm_gem_object *gem, struct drm_file *file_priv)
{
	struct nouveau_cli *cli = nouveau_cli(file_priv);
	struct nouveau_bo *nvbo = nouveau_gem_object(gem);
	struct nouveau_drm *drm = nouveau_bdev(nvbo->bo.bdev);
	struct device *dev = drm->dev->dev;
	struct nouveau_vma *vma;
	int ret;

	if (cli->vmm.vmm.object.oclass < NVIF_CLASS_VMM_NV50)
		return 0;

	ret = ttm_bo_reserve(&nvbo->bo, false, false, NULL);
	if (ret)
		return ret;

	ret = pm_runtime_get_sync(dev);
	if (ret < 0 && ret != -EACCES)
		goto out;

	ret = nouveau_vma_new(nvbo, &cli->vmm, &vma);
	pm_runtime_mark_last_busy(dev);
	pm_runtime_put_autosuspend(dev);
out:
	ttm_bo_unreserve(&nvbo->bo);
	return ret;
}