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
struct amdgpu_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PWR ; 
 int PWR_MISC_CNTL_STATUS__PWR_GFXOFF_STATUS_MASK ; 
 int PWR_MISC_CNTL_STATUS__PWR_GFXOFF_STATUS__SHIFT ; 
 int PWR_MISC_CNTL_STATUS__PWR_GFX_RLC_CGPG_EN_MASK ; 
 int RREG32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SOC15_REG_OFFSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mmPWR_MISC_CNTL_STATUS ; 

__attribute__((used)) static void pwr_10_0_gfxip_control_over_cgpg(struct amdgpu_device *adev,
					     bool enable)
{
	uint32_t data = 0;
	uint32_t default_data = 0;

	default_data = data = RREG32(SOC15_REG_OFFSET(PWR, 0, mmPWR_MISC_CNTL_STATUS));
	if (enable == true) {
		/* enable GFXIP control over CGPG */
		data |= PWR_MISC_CNTL_STATUS__PWR_GFX_RLC_CGPG_EN_MASK;
		if(default_data != data)
			WREG32(SOC15_REG_OFFSET(PWR, 0, mmPWR_MISC_CNTL_STATUS), data);

		/* update status */
		data &= ~PWR_MISC_CNTL_STATUS__PWR_GFXOFF_STATUS_MASK;
		data |= (2 << PWR_MISC_CNTL_STATUS__PWR_GFXOFF_STATUS__SHIFT);
		if(default_data != data)
			WREG32(SOC15_REG_OFFSET(PWR, 0, mmPWR_MISC_CNTL_STATUS), data);
	} else {
		/* restore GFXIP control over GCPG */
		data &= ~PWR_MISC_CNTL_STATUS__PWR_GFX_RLC_CGPG_EN_MASK;
		if(default_data != data)
			WREG32(SOC15_REG_OFFSET(PWR, 0, mmPWR_MISC_CNTL_STATUS), data);
	}
}