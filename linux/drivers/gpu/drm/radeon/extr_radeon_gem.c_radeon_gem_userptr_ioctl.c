#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct ttm_operation_ctx {int member_0; int member_1; } ;
struct radeon_device {scalar_t__ family; int /*<<< orphan*/  exclusive_lock; } ;
struct TYPE_5__ {int /*<<< orphan*/  ttm; } ;
struct radeon_bo {int /*<<< orphan*/  placement; TYPE_2__ tbo; } ;
struct drm_radeon_gem_userptr {int addr; int size; int flags; int /*<<< orphan*/  handle; } ;
struct drm_gem_object {int dummy; } ;
struct drm_file {int dummy; } ;
struct drm_device {struct radeon_device* dev_private; } ;
struct TYPE_6__ {TYPE_1__* mm; } ;
struct TYPE_4__ {int /*<<< orphan*/  mmap_sem; } ;

/* Variables and functions */
 scalar_t__ CHIP_R600 ; 
 int EACCES ; 
 int EINVAL ; 
 int /*<<< orphan*/  RADEON_GEM_DOMAIN_CPU ; 
 int /*<<< orphan*/  RADEON_GEM_DOMAIN_GTT ; 
 int RADEON_GEM_USERPTR_ANONONLY ; 
 int RADEON_GEM_USERPTR_READONLY ; 
 int RADEON_GEM_USERPTR_REGISTER ; 
 int RADEON_GEM_USERPTR_VALIDATE ; 
 TYPE_3__* current ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int drm_gem_handle_create (struct drm_file*,struct drm_gem_object*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_gem_object_put_unlocked (struct drm_gem_object*) ; 
 struct radeon_bo* gem_to_radeon_bo (struct drm_gem_object*) ; 
 scalar_t__ offset_in_page (int) ; 
 int radeon_bo_reserve (struct radeon_bo*,int) ; 
 int /*<<< orphan*/  radeon_bo_unreserve (struct radeon_bo*) ; 
 int radeon_gem_handle_lockup (struct radeon_device*,int) ; 
 int radeon_gem_object_create (struct radeon_device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct drm_gem_object**) ; 
 int radeon_mn_register (struct radeon_bo*,int) ; 
 int /*<<< orphan*/  radeon_ttm_placement_from_domain (struct radeon_bo*,int /*<<< orphan*/ ) ; 
 int radeon_ttm_tt_set_userptr (int /*<<< orphan*/ ,int,int) ; 
 int ttm_bo_validate (TYPE_2__*,int /*<<< orphan*/ *,struct ttm_operation_ctx*) ; 
 int untagged_addr (int) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

int radeon_gem_userptr_ioctl(struct drm_device *dev, void *data,
			     struct drm_file *filp)
{
	struct ttm_operation_ctx ctx = { true, false };
	struct radeon_device *rdev = dev->dev_private;
	struct drm_radeon_gem_userptr *args = data;
	struct drm_gem_object *gobj;
	struct radeon_bo *bo;
	uint32_t handle;
	int r;

	args->addr = untagged_addr(args->addr);

	if (offset_in_page(args->addr | args->size))
		return -EINVAL;

	/* reject unknown flag values */
	if (args->flags & ~(RADEON_GEM_USERPTR_READONLY |
	    RADEON_GEM_USERPTR_ANONONLY | RADEON_GEM_USERPTR_VALIDATE |
	    RADEON_GEM_USERPTR_REGISTER))
		return -EINVAL;

	if (args->flags & RADEON_GEM_USERPTR_READONLY) {
		/* readonly pages not tested on older hardware */
		if (rdev->family < CHIP_R600)
			return -EINVAL;

	} else if (!(args->flags & RADEON_GEM_USERPTR_ANONONLY) ||
		   !(args->flags & RADEON_GEM_USERPTR_REGISTER)) {

		/* if we want to write to it we must require anonymous
		   memory and install a MMU notifier */
		return -EACCES;
	}

	down_read(&rdev->exclusive_lock);

	/* create a gem object to contain this object in */
	r = radeon_gem_object_create(rdev, args->size, 0,
				     RADEON_GEM_DOMAIN_CPU, 0,
				     false, &gobj);
	if (r)
		goto handle_lockup;

	bo = gem_to_radeon_bo(gobj);
	r = radeon_ttm_tt_set_userptr(bo->tbo.ttm, args->addr, args->flags);
	if (r)
		goto release_object;

	if (args->flags & RADEON_GEM_USERPTR_REGISTER) {
		r = radeon_mn_register(bo, args->addr);
		if (r)
			goto release_object;
	}

	if (args->flags & RADEON_GEM_USERPTR_VALIDATE) {
		down_read(&current->mm->mmap_sem);
		r = radeon_bo_reserve(bo, true);
		if (r) {
			up_read(&current->mm->mmap_sem);
			goto release_object;
		}

		radeon_ttm_placement_from_domain(bo, RADEON_GEM_DOMAIN_GTT);
		r = ttm_bo_validate(&bo->tbo, &bo->placement, &ctx);
		radeon_bo_unreserve(bo);
		up_read(&current->mm->mmap_sem);
		if (r)
			goto release_object;
	}

	r = drm_gem_handle_create(filp, gobj, &handle);
	/* drop reference from allocate - handle holds it now */
	drm_gem_object_put_unlocked(gobj);
	if (r)
		goto handle_lockup;

	args->handle = handle;
	up_read(&rdev->exclusive_lock);
	return 0;

release_object:
	drm_gem_object_put_unlocked(gobj);

handle_lockup:
	up_read(&rdev->exclusive_lock);
	r = radeon_gem_handle_lockup(rdev, r);

	return r;
}