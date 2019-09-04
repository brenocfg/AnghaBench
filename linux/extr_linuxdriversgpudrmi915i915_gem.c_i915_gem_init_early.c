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
struct TYPE_8__ {int /*<<< orphan*/  lock; } ;
struct TYPE_7__ {int /*<<< orphan*/  bsd_engine_dispatch_index; } ;
struct TYPE_6__ {int /*<<< orphan*/  reset_queue; int /*<<< orphan*/  wait_queue; } ;
struct TYPE_5__ {int /*<<< orphan*/  idle_work; int /*<<< orphan*/  retire_work; int /*<<< orphan*/  closed_vma; int /*<<< orphan*/  active_rings; int /*<<< orphan*/  timelines; } ;
struct drm_i915_private {void* objects; void* vmas; void* luts; void* requests; void* dependencies; TYPE_4__ fb_tracking; TYPE_3__ mm; TYPE_2__ gpu_error; TYPE_1__ gt; void* priorities; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_NOTE (char*,int) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 void* KMEM_CACHE (int /*<<< orphan*/ ,int) ; 
 int SLAB_HWCACHE_ALIGN ; 
 int SLAB_RECLAIM_ACCOUNT ; 
 int SLAB_TYPESAFE_BY_RCU ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_i915_gem_object ; 
 int /*<<< orphan*/  i915_dependency ; 
 int /*<<< orphan*/  i915_gem_idle_work_handler ; 
 int /*<<< orphan*/  i915_gem_init__mm (struct drm_i915_private*) ; 
 int /*<<< orphan*/  i915_gem_retire_work_handler ; 
 int i915_gemfs_init (struct drm_i915_private*) ; 
 int /*<<< orphan*/  i915_lut_handle ; 
 int /*<<< orphan*/  i915_priolist ; 
 int /*<<< orphan*/  i915_request ; 
 int /*<<< orphan*/  i915_vma ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kmem_cache_destroy (void*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

int i915_gem_init_early(struct drm_i915_private *dev_priv)
{
	int err = -ENOMEM;

	dev_priv->objects = KMEM_CACHE(drm_i915_gem_object, SLAB_HWCACHE_ALIGN);
	if (!dev_priv->objects)
		goto err_out;

	dev_priv->vmas = KMEM_CACHE(i915_vma, SLAB_HWCACHE_ALIGN);
	if (!dev_priv->vmas)
		goto err_objects;

	dev_priv->luts = KMEM_CACHE(i915_lut_handle, 0);
	if (!dev_priv->luts)
		goto err_vmas;

	dev_priv->requests = KMEM_CACHE(i915_request,
					SLAB_HWCACHE_ALIGN |
					SLAB_RECLAIM_ACCOUNT |
					SLAB_TYPESAFE_BY_RCU);
	if (!dev_priv->requests)
		goto err_luts;

	dev_priv->dependencies = KMEM_CACHE(i915_dependency,
					    SLAB_HWCACHE_ALIGN |
					    SLAB_RECLAIM_ACCOUNT);
	if (!dev_priv->dependencies)
		goto err_requests;

	dev_priv->priorities = KMEM_CACHE(i915_priolist, SLAB_HWCACHE_ALIGN);
	if (!dev_priv->priorities)
		goto err_dependencies;

	INIT_LIST_HEAD(&dev_priv->gt.timelines);
	INIT_LIST_HEAD(&dev_priv->gt.active_rings);
	INIT_LIST_HEAD(&dev_priv->gt.closed_vma);

	i915_gem_init__mm(dev_priv);

	INIT_DELAYED_WORK(&dev_priv->gt.retire_work,
			  i915_gem_retire_work_handler);
	INIT_DELAYED_WORK(&dev_priv->gt.idle_work,
			  i915_gem_idle_work_handler);
	init_waitqueue_head(&dev_priv->gpu_error.wait_queue);
	init_waitqueue_head(&dev_priv->gpu_error.reset_queue);

	atomic_set(&dev_priv->mm.bsd_engine_dispatch_index, 0);

	spin_lock_init(&dev_priv->fb_tracking.lock);

	err = i915_gemfs_init(dev_priv);
	if (err)
		DRM_NOTE("Unable to create a private tmpfs mount, hugepage support will be disabled(%d).\n", err);

	return 0;

err_dependencies:
	kmem_cache_destroy(dev_priv->dependencies);
err_requests:
	kmem_cache_destroy(dev_priv->requests);
err_luts:
	kmem_cache_destroy(dev_priv->luts);
err_vmas:
	kmem_cache_destroy(dev_priv->vmas);
err_objects:
	kmem_cache_destroy(dev_priv->objects);
err_out:
	return err;
}