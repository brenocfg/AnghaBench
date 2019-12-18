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
struct dce_i2c_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DC_I2C_ARBITRATION ; 
 int /*<<< orphan*/  DC_I2C_DDC1_HW_STATUS ; 
 int /*<<< orphan*/  DC_I2C_REG_RW_CNTL_STATUS ; 
 unsigned int DC_I2C_REG_RW_CNTL_STATUS_DMCU_ONLY ; 
 unsigned int DC_I2C_STATUS__DC_I2C_STATUS_USED_BY_HW ; 
 int /*<<< orphan*/  HW_STATUS ; 
 int /*<<< orphan*/  REG_GET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 

__attribute__((used)) static bool is_engine_available(struct dce_i2c_hw *dce_i2c_hw)
{
	unsigned int arbitrate;
	unsigned int i2c_hw_status;

	REG_GET(HW_STATUS, DC_I2C_DDC1_HW_STATUS, &i2c_hw_status);
	if (i2c_hw_status == DC_I2C_STATUS__DC_I2C_STATUS_USED_BY_HW)
		return false;

	REG_GET(DC_I2C_ARBITRATION, DC_I2C_REG_RW_CNTL_STATUS, &arbitrate);
	if (arbitrate == DC_I2C_REG_RW_CNTL_STATUS_DMCU_ONLY)
		return false;

	return true;
}