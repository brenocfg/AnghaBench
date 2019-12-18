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
typedef  int u64 ;
struct TYPE_2__ {int nvm; int vram_base_offset; } ;
struct radeon_device {int flags; TYPE_1__ vm_manager; } ;

/* Variables and functions */
 int /*<<< orphan*/  FUS_MC_VM_FB_OFFSET ; 
 int RADEON_IS_IGP ; 
 int RREG32 (int /*<<< orphan*/ ) ; 

int cayman_vm_init(struct radeon_device *rdev)
{
	/* number of VMs */
	rdev->vm_manager.nvm = 8;
	/* base offset of vram pages */
	if (rdev->flags & RADEON_IS_IGP) {
		u64 tmp = RREG32(FUS_MC_VM_FB_OFFSET);
		tmp <<= 22;
		rdev->vm_manager.vram_base_offset = tmp;
	} else
		rdev->vm_manager.vram_base_offset = 0;
	return 0;
}