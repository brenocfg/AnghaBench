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
typedef  int /*<<< orphan*/  vm_fault_t ;
struct vm_fault {TYPE_1__* vma; } ;
struct ttm_buffer_object {int /*<<< orphan*/  bdev; } ;
struct TYPE_5__ {int /*<<< orphan*/  mclk_lock; } ;
struct radeon_device {TYPE_2__ pm; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* fault ) (struct vm_fault*) ;} ;
struct TYPE_4__ {scalar_t__ vm_private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  VM_FAULT_NOPAGE ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 struct radeon_device* radeon_get_rdev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct vm_fault*) ; 
 TYPE_3__* ttm_vm_ops ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static vm_fault_t radeon_ttm_fault(struct vm_fault *vmf)
{
	struct ttm_buffer_object *bo;
	struct radeon_device *rdev;
	vm_fault_t ret;

	bo = (struct ttm_buffer_object *)vmf->vma->vm_private_data;
	if (bo == NULL) {
		return VM_FAULT_NOPAGE;
	}
	rdev = radeon_get_rdev(bo->bdev);
	down_read(&rdev->pm.mclk_lock);
	ret = ttm_vm_ops->fault(vmf);
	up_read(&rdev->pm.mclk_lock);
	return ret;
}