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
struct i2c_adapter {int dummy; } ;
struct amdgpu_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SMUIO ; 
 int /*<<< orphan*/  WREG32_SOC15 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mmCKSVII2C_IC_FS_SPKLEN ; 
 int /*<<< orphan*/  mmCKSVII2C_IC_SDA_HOLD ; 
 int /*<<< orphan*/  mmCKSVII2C_IC_SS_SCL_HCNT ; 
 int /*<<< orphan*/  mmCKSVII2C_IC_SS_SCL_LCNT ; 
 struct amdgpu_device* to_amdgpu_device (struct i2c_adapter*) ; 

__attribute__((used)) static void smu_v11_0_i2c_set_clock(struct i2c_adapter *control)
{
	struct amdgpu_device *adev = to_amdgpu_device(control);

	/*
	 * Standard mode speed, These values are taken from SMUIO MAS,
	 * but are different from what is given is
	 * Synopsys spec. The values here are based on assumption
	 * that refclock is 100MHz
	 *
	 * Configuration for standard mode; Speed = 100kbps
	 * Scale linearly, for now only support standard speed clock
	 * This will work only with 100M ref clock
	 *
	 * TBD:Change the calculation to take into account ref clock values also.
	 */

	WREG32_SOC15(SMUIO, 0, mmCKSVII2C_IC_FS_SPKLEN, 2);
	WREG32_SOC15(SMUIO, 0, mmCKSVII2C_IC_SS_SCL_HCNT, 120);
	WREG32_SOC15(SMUIO, 0, mmCKSVII2C_IC_SS_SCL_LCNT, 130);
	WREG32_SOC15(SMUIO, 0, mmCKSVII2C_IC_SDA_HOLD, 20);
}