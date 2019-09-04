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
typedef  scalar_t__ uint32_t ;
struct engine {int /*<<< orphan*/  ctx; } ;

/* Variables and functions */
 scalar_t__ DC_I2C_STATUS__DC_I2C_STATUS_IDLE ; 
 int /*<<< orphan*/  DC_I2C_SW_STATUS ; 
 scalar_t__ dm_read_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ get_reg_field_value (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmDC_I2C_SW_STATUS ; 
 int /*<<< orphan*/  reset_hw_engine (struct engine*) ; 

__attribute__((used)) static bool is_hw_busy(struct engine *engine)
{
	uint32_t i2c_sw_status = 0;

	uint32_t value = dm_read_reg(engine->ctx, mmDC_I2C_SW_STATUS);

	i2c_sw_status = get_reg_field_value(
			value,
			DC_I2C_SW_STATUS,
			DC_I2C_SW_STATUS);

	if (i2c_sw_status == DC_I2C_STATUS__DC_I2C_STATUS_IDLE)
		return false;

	reset_hw_engine(engine);

	value = dm_read_reg(engine->ctx, mmDC_I2C_SW_STATUS);

	i2c_sw_status = get_reg_field_value(
			value,
			DC_I2C_SW_STATUS,
			DC_I2C_SW_STATUS);

	return i2c_sw_status != DC_I2C_STATUS__DC_I2C_STATUS_IDLE;
}