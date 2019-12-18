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
 int /*<<< orphan*/  MMHUB ; 
 int MMHUB_INSTANCE_REGISTER_OFFSET ; 
 int /*<<< orphan*/  WREG32_SOC15_OFFSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  mmVML2PF0_VM_L2_CONTEXT1_IDENTITY_APERTURE_HIGH_ADDR_HI32 ; 
 int /*<<< orphan*/  mmVML2PF0_VM_L2_CONTEXT1_IDENTITY_APERTURE_HIGH_ADDR_LO32 ; 
 int /*<<< orphan*/  mmVML2PF0_VM_L2_CONTEXT1_IDENTITY_APERTURE_LOW_ADDR_HI32 ; 
 int /*<<< orphan*/  mmVML2PF0_VM_L2_CONTEXT1_IDENTITY_APERTURE_LOW_ADDR_LO32 ; 
 int /*<<< orphan*/  mmVML2PF0_VM_L2_CONTEXT_IDENTITY_PHYSICAL_OFFSET_HI32 ; 
 int /*<<< orphan*/  mmVML2PF0_VM_L2_CONTEXT_IDENTITY_PHYSICAL_OFFSET_LO32 ; 

__attribute__((used)) static void mmhub_v9_4_disable_identity_aperture(struct amdgpu_device *adev,
						 int hubid)
{
	WREG32_SOC15_OFFSET(MMHUB, 0,
		    mmVML2PF0_VM_L2_CONTEXT1_IDENTITY_APERTURE_LOW_ADDR_LO32,
		    hubid * MMHUB_INSTANCE_REGISTER_OFFSET, 0XFFFFFFFF);
	WREG32_SOC15_OFFSET(MMHUB, 0,
		    mmVML2PF0_VM_L2_CONTEXT1_IDENTITY_APERTURE_LOW_ADDR_HI32,
		    hubid * MMHUB_INSTANCE_REGISTER_OFFSET, 0x0000000F);

	WREG32_SOC15_OFFSET(MMHUB, 0,
		    mmVML2PF0_VM_L2_CONTEXT1_IDENTITY_APERTURE_HIGH_ADDR_LO32,
		    hubid * MMHUB_INSTANCE_REGISTER_OFFSET, 0);
	WREG32_SOC15_OFFSET(MMHUB, 0,
		    mmVML2PF0_VM_L2_CONTEXT1_IDENTITY_APERTURE_HIGH_ADDR_HI32,
		    hubid * MMHUB_INSTANCE_REGISTER_OFFSET, 0);

	WREG32_SOC15_OFFSET(MMHUB, 0,
		    mmVML2PF0_VM_L2_CONTEXT_IDENTITY_PHYSICAL_OFFSET_LO32,
		    hubid * MMHUB_INSTANCE_REGISTER_OFFSET, 0);
	WREG32_SOC15_OFFSET(MMHUB, 0,
		    mmVML2PF0_VM_L2_CONTEXT_IDENTITY_PHYSICAL_OFFSET_HI32,
		    hubid * MMHUB_INSTANCE_REGISTER_OFFSET, 0);
}