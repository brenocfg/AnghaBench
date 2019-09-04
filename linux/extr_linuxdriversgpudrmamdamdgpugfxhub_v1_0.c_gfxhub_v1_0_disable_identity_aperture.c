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
 int /*<<< orphan*/  GC ; 
 int /*<<< orphan*/  WREG32_SOC15 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mmVM_L2_CONTEXT1_IDENTITY_APERTURE_HIGH_ADDR_HI32 ; 
 int /*<<< orphan*/  mmVM_L2_CONTEXT1_IDENTITY_APERTURE_HIGH_ADDR_LO32 ; 
 int /*<<< orphan*/  mmVM_L2_CONTEXT1_IDENTITY_APERTURE_LOW_ADDR_HI32 ; 
 int /*<<< orphan*/  mmVM_L2_CONTEXT1_IDENTITY_APERTURE_LOW_ADDR_LO32 ; 
 int /*<<< orphan*/  mmVM_L2_CONTEXT_IDENTITY_PHYSICAL_OFFSET_HI32 ; 
 int /*<<< orphan*/  mmVM_L2_CONTEXT_IDENTITY_PHYSICAL_OFFSET_LO32 ; 

__attribute__((used)) static void gfxhub_v1_0_disable_identity_aperture(struct amdgpu_device *adev)
{
	WREG32_SOC15(GC, 0, mmVM_L2_CONTEXT1_IDENTITY_APERTURE_LOW_ADDR_LO32,
		     0XFFFFFFFF);
	WREG32_SOC15(GC, 0, mmVM_L2_CONTEXT1_IDENTITY_APERTURE_LOW_ADDR_HI32,
		     0x0000000F);

	WREG32_SOC15(GC, 0, mmVM_L2_CONTEXT1_IDENTITY_APERTURE_HIGH_ADDR_LO32,
		     0);
	WREG32_SOC15(GC, 0, mmVM_L2_CONTEXT1_IDENTITY_APERTURE_HIGH_ADDR_HI32,
		     0);

	WREG32_SOC15(GC, 0, mmVM_L2_CONTEXT_IDENTITY_PHYSICAL_OFFSET_LO32, 0);
	WREG32_SOC15(GC, 0, mmVM_L2_CONTEXT_IDENTITY_PHYSICAL_OFFSET_HI32, 0);

}