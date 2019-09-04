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
struct radeon_vm {int /*<<< orphan*/  ib_bo_va; } ;
struct radeon_fpriv {struct radeon_vm vm; } ;
struct TYPE_2__ {int /*<<< orphan*/  bo; } ;
struct radeon_device {scalar_t__ family; TYPE_1__ ring_tmp_bo; scalar_t__ accel_working; } ;
struct drm_file {struct radeon_fpriv* driver_priv; } ;
struct drm_device {int /*<<< orphan*/  dev; struct radeon_device* dev_private; } ;

/* Variables and functions */
 scalar_t__ CHIP_CAYMAN ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  RADEON_VA_IB_OFFSET ; 
 int RADEON_VM_PAGE_READABLE ; 
 int RADEON_VM_PAGE_SNOOPED ; 
 int /*<<< orphan*/  kfree (struct radeon_fpriv*) ; 
 struct radeon_fpriv* kzalloc (int,int /*<<< orphan*/ ) ; 
 int pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_mark_last_busy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put_autosuspend (int /*<<< orphan*/ ) ; 
 int radeon_bo_reserve (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  radeon_vm_bo_add (struct radeon_device*,struct radeon_vm*,int /*<<< orphan*/ ) ; 
 int radeon_vm_bo_set_addr (struct radeon_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  radeon_vm_fini (struct radeon_device*,struct radeon_vm*) ; 
 int radeon_vm_init (struct radeon_device*,struct radeon_vm*) ; 
 scalar_t__ unlikely (int) ; 

int radeon_driver_open_kms(struct drm_device *dev, struct drm_file *file_priv)
{
	struct radeon_device *rdev = dev->dev_private;
	int r;

	file_priv->driver_priv = NULL;

	r = pm_runtime_get_sync(dev->dev);
	if (r < 0)
		return r;

	/* new gpu have virtual address space support */
	if (rdev->family >= CHIP_CAYMAN) {
		struct radeon_fpriv *fpriv;
		struct radeon_vm *vm;

		fpriv = kzalloc(sizeof(*fpriv), GFP_KERNEL);
		if (unlikely(!fpriv)) {
			r = -ENOMEM;
			goto out_suspend;
		}

		if (rdev->accel_working) {
			vm = &fpriv->vm;
			r = radeon_vm_init(rdev, vm);
			if (r) {
				kfree(fpriv);
				goto out_suspend;
			}

			r = radeon_bo_reserve(rdev->ring_tmp_bo.bo, false);
			if (r) {
				radeon_vm_fini(rdev, vm);
				kfree(fpriv);
				goto out_suspend;
			}

			/* map the ib pool buffer read only into
			 * virtual address space */
			vm->ib_bo_va = radeon_vm_bo_add(rdev, vm,
							rdev->ring_tmp_bo.bo);
			r = radeon_vm_bo_set_addr(rdev, vm->ib_bo_va,
						  RADEON_VA_IB_OFFSET,
						  RADEON_VM_PAGE_READABLE |
						  RADEON_VM_PAGE_SNOOPED);
			if (r) {
				radeon_vm_fini(rdev, vm);
				kfree(fpriv);
				goto out_suspend;
			}
		}
		file_priv->driver_priv = fpriv;
	}

out_suspend:
	pm_runtime_mark_last_busy(dev->dev);
	pm_runtime_put_autosuspend(dev->dev);
	return r;
}