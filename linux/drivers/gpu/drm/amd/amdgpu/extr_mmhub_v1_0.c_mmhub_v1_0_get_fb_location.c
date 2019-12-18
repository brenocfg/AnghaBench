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
struct TYPE_2__ {int fb_start; int fb_end; } ;
struct amdgpu_device {TYPE_1__ gmc; } ;

/* Variables and functions */
 int MC_VM_FB_LOCATION_BASE__FB_BASE_MASK ; 
 int MC_VM_FB_LOCATION_TOP__FB_TOP_MASK ; 
 int /*<<< orphan*/  MMHUB ; 
 int RREG32_SOC15 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmMC_VM_FB_LOCATION_BASE ; 
 int /*<<< orphan*/  mmMC_VM_FB_LOCATION_TOP ; 

u64 mmhub_v1_0_get_fb_location(struct amdgpu_device *adev)
{
	u64 base = RREG32_SOC15(MMHUB, 0, mmMC_VM_FB_LOCATION_BASE);
	u64 top = RREG32_SOC15(MMHUB, 0, mmMC_VM_FB_LOCATION_TOP);

	base &= MC_VM_FB_LOCATION_BASE__FB_BASE_MASK;
	base <<= 24;

	top &= MC_VM_FB_LOCATION_TOP__FB_TOP_MASK;
	top <<= 24;

	adev->gmc.fb_start = base;
	adev->gmc.fb_end = top;

	return base;
}