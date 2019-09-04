#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct ttm_operation_ctx {int member_0; int member_1; } ;
struct drm_gem_object {int dummy; } ;
struct drm_file {int dummy; } ;
struct drm_device {struct amdgpu_device* dev_private; } ;
struct drm_amdgpu_gem_userptr {int addr; int size; int flags; int /*<<< orphan*/  handle; } ;
struct amdgpu_device {int dummy; } ;
struct TYPE_4__ {TYPE_2__* ttm; } ;
struct amdgpu_bo {TYPE_1__ tbo; int /*<<< orphan*/  placement; void* allowed_domains; void* preferred_domains; } ;
struct TYPE_5__ {int /*<<< orphan*/  num_pages; int /*<<< orphan*/  pages; } ;

/* Variables and functions */
 int /*<<< orphan*/  AMDGPU_GEM_DOMAIN_CPU ; 
 void* AMDGPU_GEM_DOMAIN_GTT ; 
 int AMDGPU_GEM_USERPTR_ANONONLY ; 
 int AMDGPU_GEM_USERPTR_READONLY ; 
 int AMDGPU_GEM_USERPTR_REGISTER ; 
 int AMDGPU_GEM_USERPTR_VALIDATE ; 
 int EACCES ; 
 int EINVAL ; 
 int /*<<< orphan*/  amdgpu_bo_placement_from_domain (struct amdgpu_bo*,void*) ; 
 int amdgpu_bo_reserve (struct amdgpu_bo*,int) ; 
 int /*<<< orphan*/  amdgpu_bo_unreserve (struct amdgpu_bo*) ; 
 int amdgpu_gem_object_create (struct amdgpu_device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct drm_gem_object**) ; 
 int amdgpu_mn_register (struct amdgpu_bo*,int) ; 
 int amdgpu_ttm_tt_get_user_pages (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int amdgpu_ttm_tt_set_userptr (TYPE_2__*,int,int) ; 
 int drm_gem_handle_create (struct drm_file*,struct drm_gem_object*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_gem_object_put_unlocked (struct drm_gem_object*) ; 
 struct amdgpu_bo* gem_to_amdgpu_bo (struct drm_gem_object*) ; 
 scalar_t__ offset_in_page (int) ; 
 int /*<<< orphan*/  release_pages (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ttm_bo_type_device ; 
 int ttm_bo_validate (TYPE_1__*,int /*<<< orphan*/ *,struct ttm_operation_ctx*) ; 

int amdgpu_gem_userptr_ioctl(struct drm_device *dev, void *data,
			     struct drm_file *filp)
{
	struct ttm_operation_ctx ctx = { true, false };
	struct amdgpu_device *adev = dev->dev_private;
	struct drm_amdgpu_gem_userptr *args = data;
	struct drm_gem_object *gobj;
	struct amdgpu_bo *bo;
	uint32_t handle;
	int r;

	if (offset_in_page(args->addr | args->size))
		return -EINVAL;

	/* reject unknown flag values */
	if (args->flags & ~(AMDGPU_GEM_USERPTR_READONLY |
	    AMDGPU_GEM_USERPTR_ANONONLY | AMDGPU_GEM_USERPTR_VALIDATE |
	    AMDGPU_GEM_USERPTR_REGISTER))
		return -EINVAL;

	if (!(args->flags & AMDGPU_GEM_USERPTR_READONLY) &&
	     !(args->flags & AMDGPU_GEM_USERPTR_REGISTER)) {

		/* if we want to write to it we must install a MMU notifier */
		return -EACCES;
	}

	/* create a gem object to contain this object in */
	r = amdgpu_gem_object_create(adev, args->size, 0, AMDGPU_GEM_DOMAIN_CPU,
				     0, ttm_bo_type_device, NULL, &gobj);
	if (r)
		return r;

	bo = gem_to_amdgpu_bo(gobj);
	bo->preferred_domains = AMDGPU_GEM_DOMAIN_GTT;
	bo->allowed_domains = AMDGPU_GEM_DOMAIN_GTT;
	r = amdgpu_ttm_tt_set_userptr(bo->tbo.ttm, args->addr, args->flags);
	if (r)
		goto release_object;

	if (args->flags & AMDGPU_GEM_USERPTR_REGISTER) {
		r = amdgpu_mn_register(bo, args->addr);
		if (r)
			goto release_object;
	}

	if (args->flags & AMDGPU_GEM_USERPTR_VALIDATE) {
		r = amdgpu_ttm_tt_get_user_pages(bo->tbo.ttm,
						 bo->tbo.ttm->pages);
		if (r)
			goto release_object;

		r = amdgpu_bo_reserve(bo, true);
		if (r)
			goto free_pages;

		amdgpu_bo_placement_from_domain(bo, AMDGPU_GEM_DOMAIN_GTT);
		r = ttm_bo_validate(&bo->tbo, &bo->placement, &ctx);
		amdgpu_bo_unreserve(bo);
		if (r)
			goto free_pages;
	}

	r = drm_gem_handle_create(filp, gobj, &handle);
	/* drop reference from allocate - handle holds it now */
	drm_gem_object_put_unlocked(gobj);
	if (r)
		return r;

	args->handle = handle;
	return 0;

free_pages:
	release_pages(bo->tbo.ttm->pages, bo->tbo.ttm->num_pages);

release_object:
	drm_gem_object_put_unlocked(gobj);

	return r;
}