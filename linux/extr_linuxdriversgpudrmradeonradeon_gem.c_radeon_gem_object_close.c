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
struct radeon_vm {int dummy; } ;
struct radeon_fpriv {struct radeon_vm vm; } ;
struct radeon_device {scalar_t__ family; int /*<<< orphan*/  dev; int /*<<< orphan*/  accel_working; } ;
struct radeon_bo_va {scalar_t__ ref_count; } ;
struct radeon_bo {struct radeon_device* rdev; } ;
struct drm_gem_object {int dummy; } ;
struct drm_file {struct radeon_fpriv* driver_priv; } ;

/* Variables and functions */
 scalar_t__ CHIP_CAYMAN ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 struct radeon_bo* gem_to_radeon_bo (struct drm_gem_object*) ; 
 int radeon_bo_reserve (struct radeon_bo*,int) ; 
 int /*<<< orphan*/  radeon_bo_unreserve (struct radeon_bo*) ; 
 struct radeon_bo_va* radeon_vm_bo_find (struct radeon_vm*,struct radeon_bo*) ; 
 int /*<<< orphan*/  radeon_vm_bo_rmv (struct radeon_device*,struct radeon_bo_va*) ; 

void radeon_gem_object_close(struct drm_gem_object *obj,
			     struct drm_file *file_priv)
{
	struct radeon_bo *rbo = gem_to_radeon_bo(obj);
	struct radeon_device *rdev = rbo->rdev;
	struct radeon_fpriv *fpriv = file_priv->driver_priv;
	struct radeon_vm *vm = &fpriv->vm;
	struct radeon_bo_va *bo_va;
	int r;

	if ((rdev->family < CHIP_CAYMAN) ||
	    (!rdev->accel_working)) {
		return;
	}

	r = radeon_bo_reserve(rbo, true);
	if (r) {
		dev_err(rdev->dev, "leaking bo va because "
			"we fail to reserve bo (%d)\n", r);
		return;
	}
	bo_va = radeon_vm_bo_find(vm, rbo);
	if (bo_va) {
		if (--bo_va->ref_count == 0) {
			radeon_vm_bo_rmv(rdev, bo_va);
		}
	}
	radeon_bo_unreserve(rbo);
}