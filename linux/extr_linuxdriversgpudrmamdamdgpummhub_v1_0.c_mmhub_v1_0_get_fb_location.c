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
typedef  int u64 ;
struct amdgpu_device {int dummy; } ;

/* Variables and functions */
 int MC_VM_FB_LOCATION_BASE__FB_BASE_MASK ; 
 int /*<<< orphan*/  MMHUB ; 
 int RREG32_SOC15 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmMC_VM_FB_LOCATION_BASE ; 

u64 mmhub_v1_0_get_fb_location(struct amdgpu_device *adev)
{
	u64 base = RREG32_SOC15(MMHUB, 0, mmMC_VM_FB_LOCATION_BASE);

	base &= MC_VM_FB_LOCATION_BASE__FB_BASE_MASK;
	base <<= 24;

	return base;
}