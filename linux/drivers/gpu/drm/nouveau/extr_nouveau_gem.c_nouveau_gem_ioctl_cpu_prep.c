#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  resv; } ;
struct TYPE_4__ {TYPE_1__ base; } ;
struct nouveau_bo {TYPE_2__ bo; } ;
struct drm_nouveau_gem_cpu_prep {int flags; int /*<<< orphan*/  handle; } ;
struct drm_gem_object {int dummy; } ;
struct drm_file {int dummy; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENOENT ; 
 int HZ ; 
 int NOUVEAU_GEM_CPU_PREP_NOWAIT ; 
 int NOUVEAU_GEM_CPU_PREP_WRITE ; 
 long dma_resv_wait_timeout_rcu (int /*<<< orphan*/ ,int,int,int) ; 
 struct drm_gem_object* drm_gem_object_lookup (struct drm_file*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_gem_object_put_unlocked (struct drm_gem_object*) ; 
 int /*<<< orphan*/  nouveau_bo_sync_for_cpu (struct nouveau_bo*) ; 
 struct nouveau_bo* nouveau_gem_object (struct drm_gem_object*) ; 

int
nouveau_gem_ioctl_cpu_prep(struct drm_device *dev, void *data,
			   struct drm_file *file_priv)
{
	struct drm_nouveau_gem_cpu_prep *req = data;
	struct drm_gem_object *gem;
	struct nouveau_bo *nvbo;
	bool no_wait = !!(req->flags & NOUVEAU_GEM_CPU_PREP_NOWAIT);
	bool write = !!(req->flags & NOUVEAU_GEM_CPU_PREP_WRITE);
	long lret;
	int ret;

	gem = drm_gem_object_lookup(file_priv, req->handle);
	if (!gem)
		return -ENOENT;
	nvbo = nouveau_gem_object(gem);

	lret = dma_resv_wait_timeout_rcu(nvbo->bo.base.resv, write, true,
						   no_wait ? 0 : 30 * HZ);
	if (!lret)
		ret = -EBUSY;
	else if (lret > 0)
		ret = 0;
	else
		ret = lret;

	nouveau_bo_sync_for_cpu(nvbo);
	drm_gem_object_put_unlocked(gem);

	return ret;
}