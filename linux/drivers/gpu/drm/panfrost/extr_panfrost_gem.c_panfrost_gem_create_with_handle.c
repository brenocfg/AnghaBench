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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int u32 ;
struct panfrost_gem_object {int noexec; int is_heap; } ;
struct drm_gem_shmem_object {int /*<<< orphan*/  base; } ;
struct drm_file {int dummy; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 struct panfrost_gem_object* ERR_CAST (struct drm_gem_shmem_object*) ; 
 struct panfrost_gem_object* ERR_PTR (int) ; 
 scalar_t__ IS_ERR (struct drm_gem_shmem_object*) ; 
 int PANFROST_BO_HEAP ; 
 int PANFROST_BO_NOEXEC ; 
 int /*<<< orphan*/  SZ_2M ; 
 int drm_gem_handle_create (struct drm_file*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_gem_object_put_unlocked (int /*<<< orphan*/ *) ; 
 struct drm_gem_shmem_object* drm_gem_shmem_create (struct drm_device*,size_t) ; 
 size_t roundup (size_t,int /*<<< orphan*/ ) ; 
 struct panfrost_gem_object* to_panfrost_bo (int /*<<< orphan*/ *) ; 

struct panfrost_gem_object *
panfrost_gem_create_with_handle(struct drm_file *file_priv,
				struct drm_device *dev, size_t size,
				u32 flags,
				uint32_t *handle)
{
	int ret;
	struct drm_gem_shmem_object *shmem;
	struct panfrost_gem_object *bo;

	/* Round up heap allocations to 2MB to keep fault handling simple */
	if (flags & PANFROST_BO_HEAP)
		size = roundup(size, SZ_2M);

	shmem = drm_gem_shmem_create(dev, size);
	if (IS_ERR(shmem))
		return ERR_CAST(shmem);

	bo = to_panfrost_bo(&shmem->base);
	bo->noexec = !!(flags & PANFROST_BO_NOEXEC);
	bo->is_heap = !!(flags & PANFROST_BO_HEAP);

	/*
	 * Allocate an id of idr table where the obj is registered
	 * and handle has the id what user can see.
	 */
	ret = drm_gem_handle_create(file_priv, &shmem->base, handle);
	/* drop reference from allocate - handle holds it now. */
	drm_gem_object_put_unlocked(&shmem->base);
	if (ret)
		return ERR_PTR(ret);

	return bo;
}