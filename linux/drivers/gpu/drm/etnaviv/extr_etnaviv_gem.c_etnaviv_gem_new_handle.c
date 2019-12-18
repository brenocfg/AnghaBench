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
typedef  int /*<<< orphan*/  u32 ;
struct drm_gem_object {TYPE_1__* filp; } ;
struct drm_file {int dummy; } ;
struct drm_device {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  lock; } ;
struct TYPE_3__ {int /*<<< orphan*/  f_mapping; } ;

/* Variables and functions */
 int GFP_HIGHUSER ; 
 int /*<<< orphan*/  PAGE_ALIGN (int /*<<< orphan*/ ) ; 
 int __GFP_NOWARN ; 
 int __GFP_RETRY_MAYFAIL ; 
 int drm_gem_handle_create (struct drm_file*,struct drm_gem_object*,int /*<<< orphan*/ *) ; 
 int drm_gem_object_init (struct drm_device*,struct drm_gem_object*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_gem_object_put_unlocked (struct drm_gem_object*) ; 
 int etnaviv_gem_new_impl (struct drm_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct drm_gem_object**) ; 
 int /*<<< orphan*/  etnaviv_gem_obj_add (struct drm_device*,struct drm_gem_object*) ; 
 int /*<<< orphan*/  etnaviv_gem_shmem_ops ; 
 int /*<<< orphan*/  etnaviv_shm_lock_class ; 
 int /*<<< orphan*/  lockdep_set_class (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mapping_set_gfp_mask (int /*<<< orphan*/ ,int) ; 
 TYPE_2__* to_etnaviv_bo (struct drm_gem_object*) ; 

int etnaviv_gem_new_handle(struct drm_device *dev, struct drm_file *file,
	u32 size, u32 flags, u32 *handle)
{
	struct drm_gem_object *obj = NULL;
	int ret;

	size = PAGE_ALIGN(size);

	ret = etnaviv_gem_new_impl(dev, size, flags,
				   &etnaviv_gem_shmem_ops, &obj);
	if (ret)
		goto fail;

	lockdep_set_class(&to_etnaviv_bo(obj)->lock, &etnaviv_shm_lock_class);

	ret = drm_gem_object_init(dev, obj, size);
	if (ret)
		goto fail;

	/*
	 * Our buffers are kept pinned, so allocating them from the MOVABLE
	 * zone is a really bad idea, and conflicts with CMA. See comments
	 * above new_inode() why this is required _and_ expected if you're
	 * going to pin these pages.
	 */
	mapping_set_gfp_mask(obj->filp->f_mapping, GFP_HIGHUSER |
			     __GFP_RETRY_MAYFAIL | __GFP_NOWARN);

	etnaviv_gem_obj_add(dev, obj);

	ret = drm_gem_handle_create(file, obj, handle);

	/* drop reference from allocate - handle holds it now */
fail:
	drm_gem_object_put_unlocked(obj);

	return ret;
}