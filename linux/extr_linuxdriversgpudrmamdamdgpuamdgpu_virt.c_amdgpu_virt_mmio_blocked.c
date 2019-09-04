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
struct amdgpu_device {int dummy; } ;

/* Variables and functions */
 int RREG32_NO_KIQ (int) ; 

bool amdgpu_virt_mmio_blocked(struct amdgpu_device *adev)
{
	/* By now all MMIO pages except mailbox are blocked */
	/* if blocking is enabled in hypervisor. Choose the */
	/* SCRATCH_REG0 to test. */
	return RREG32_NO_KIQ(0xc040) == 0xffffffff;
}