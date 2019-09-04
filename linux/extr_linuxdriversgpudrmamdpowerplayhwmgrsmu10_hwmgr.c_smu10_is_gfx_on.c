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
typedef  int uint32_t ;
struct pp_hwmgr {struct amdgpu_device* adev; } ;
struct amdgpu_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PWR ; 
 int PWR_MISC_CNTL_STATUS__PWR_GFXOFF_STATUS_MASK ; 
 int PWR_MISC_CNTL_STATUS__PWR_GFXOFF_STATUS__SHIFT ; 
 int RREG32_SOC15 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmPWR_MISC_CNTL_STATUS ; 

__attribute__((used)) static bool smu10_is_gfx_on(struct pp_hwmgr *hwmgr)
{
	uint32_t reg;
	struct amdgpu_device *adev = hwmgr->adev;

	reg = RREG32_SOC15(PWR, 0, mmPWR_MISC_CNTL_STATUS);
	if ((reg & PWR_MISC_CNTL_STATUS__PWR_GFXOFF_STATUS_MASK) ==
	    (0x2 << PWR_MISC_CNTL_STATUS__PWR_GFXOFF_STATUS__SHIFT))
		return true;

	return false;
}