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
typedef  int /*<<< orphan*/  uint32_t ;
struct i2c_adapter {int dummy; } ;
struct amdgpu_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CKSVII2C_IC_CON ; 
 int /*<<< orphan*/  IC_10BITADDR_MASTER ; 
 int /*<<< orphan*/  IC_10BITADDR_SLAVE ; 
 int /*<<< orphan*/  IC_MASTER_MODE ; 
 int /*<<< orphan*/  IC_MAX_SPEED_MODE ; 
 int /*<<< orphan*/  IC_RESTART_EN ; 
 int /*<<< orphan*/  IC_SLAVE_DISABLE ; 
 int /*<<< orphan*/  REG_SET_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SMUIO ; 
 int /*<<< orphan*/  WREG32_SOC15 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmCKSVII2C_IC_CON ; 
 struct amdgpu_device* to_amdgpu_device (struct i2c_adapter*) ; 

__attribute__((used)) static void smu_v11_0_i2c_configure(struct i2c_adapter *control)
{
	struct amdgpu_device *adev = to_amdgpu_device(control);
	uint32_t reg = 0;

	reg = REG_SET_FIELD(reg, CKSVII2C_IC_CON, IC_SLAVE_DISABLE, 1);
	reg = REG_SET_FIELD(reg, CKSVII2C_IC_CON, IC_RESTART_EN, 1);
	reg = REG_SET_FIELD(reg, CKSVII2C_IC_CON, IC_10BITADDR_MASTER, 0);
	reg = REG_SET_FIELD(reg, CKSVII2C_IC_CON, IC_10BITADDR_SLAVE, 0);
	/* Standard mode */
	reg = REG_SET_FIELD(reg, CKSVII2C_IC_CON, IC_MAX_SPEED_MODE, 2);
	reg = REG_SET_FIELD(reg, CKSVII2C_IC_CON, IC_MASTER_MODE, 1);

	WREG32_SOC15(SMUIO, 0, mmCKSVII2C_IC_CON, reg);
}