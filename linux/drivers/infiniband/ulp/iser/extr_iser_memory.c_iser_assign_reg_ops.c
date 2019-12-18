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
struct iser_device {int /*<<< orphan*/  remote_inv_sup; int /*<<< orphan*/ * reg_ops; struct ib_device* ib_device; } ;
struct TYPE_3__ {int device_cap_flags; } ;
struct TYPE_4__ {scalar_t__ unmap_fmr; scalar_t__ map_phys_fmr; scalar_t__ dealloc_fmr; scalar_t__ alloc_fmr; } ;
struct ib_device {TYPE_1__ attrs; TYPE_2__ ops; } ;

/* Variables and functions */
 int IB_DEVICE_MEM_MGT_EXTENSIONS ; 
 int /*<<< orphan*/  fastreg_ops ; 
 int /*<<< orphan*/  fmr_ops ; 
 int /*<<< orphan*/  iser_always_reg ; 
 int /*<<< orphan*/  iser_err (char*) ; 
 int /*<<< orphan*/  iser_info (char*) ; 

int iser_assign_reg_ops(struct iser_device *device)
{
	struct ib_device *ib_dev = device->ib_device;

	/* Assign function handles  - based on FMR support */
	if (ib_dev->ops.alloc_fmr && ib_dev->ops.dealloc_fmr &&
	    ib_dev->ops.map_phys_fmr && ib_dev->ops.unmap_fmr) {
		iser_info("FMR supported, using FMR for registration\n");
		device->reg_ops = &fmr_ops;
	} else if (ib_dev->attrs.device_cap_flags & IB_DEVICE_MEM_MGT_EXTENSIONS) {
		iser_info("FastReg supported, using FastReg for registration\n");
		device->reg_ops = &fastreg_ops;
		device->remote_inv_sup = iser_always_reg;
	} else {
		iser_err("IB device does not support FMRs nor FastRegs, can't register memory\n");
		return -1;
	}

	return 0;
}