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
 int /*<<< orphan*/  mmCKSVII2C_IC_ENABLE ; 
 struct amdgpu_device* to_amdgpu_device (struct i2c_adapter*) ; 

__attribute__((used)) static void smu_v11_0_i2c_enable(struct i2c_adapter *control, bool enable)
{
	struct amdgpu_device *adev = to_amdgpu_device(control);

	WREG32_SOC15(SMUIO, 0, mmCKSVII2C_IC_ENABLE, enable ? 1 : 0);
}