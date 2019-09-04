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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint32_t ;
struct TYPE_2__ {int /*<<< orphan*/  ctx; } ;
struct i2c_engine {TYPE_1__ base; } ;
typedef  enum i2c_channel_operation_result { ____Placeholder_i2c_channel_operation_result } i2c_channel_operation_result ;

/* Variables and functions */
 scalar_t__ DC_I2C_STATUS__DC_I2C_STATUS_USED_BY_SW ; 
 int /*<<< orphan*/  DC_I2C_SW_STATUS ; 
 scalar_t__ DC_I2C_SW_STATUS__DC_I2C_SW_ABORTED_MASK ; 
 scalar_t__ DC_I2C_SW_STATUS__DC_I2C_SW_DONE_MASK ; 
 scalar_t__ DC_I2C_SW_STATUS__DC_I2C_SW_STOPPED_ON_NACK_MASK ; 
 scalar_t__ DC_I2C_SW_STATUS__DC_I2C_SW_TIMEOUT_MASK ; 
 int I2C_CHANNEL_OPERATION_ENGINE_BUSY ; 
 int I2C_CHANNEL_OPERATION_FAILED ; 
 int I2C_CHANNEL_OPERATION_NO_RESPONSE ; 
 int I2C_CHANNEL_OPERATION_SUCCEEDED ; 
 int I2C_CHANNEL_OPERATION_TIMEOUT ; 
 scalar_t__ dm_read_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ get_reg_field_value (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmDC_I2C_SW_STATUS ; 

__attribute__((used)) static enum i2c_channel_operation_result get_channel_status(
	struct i2c_engine *engine,
	uint8_t *returned_bytes)
{
	uint32_t i2c_sw_status = 0;
	uint32_t value = dm_read_reg(engine->base.ctx, mmDC_I2C_SW_STATUS);

	i2c_sw_status = get_reg_field_value(
			value,
			DC_I2C_SW_STATUS,
			DC_I2C_SW_STATUS);

	if (i2c_sw_status == DC_I2C_STATUS__DC_I2C_STATUS_USED_BY_SW)
		return I2C_CHANNEL_OPERATION_ENGINE_BUSY;
	else if (value & DC_I2C_SW_STATUS__DC_I2C_SW_STOPPED_ON_NACK_MASK)
		return I2C_CHANNEL_OPERATION_NO_RESPONSE;
	else if (value & DC_I2C_SW_STATUS__DC_I2C_SW_TIMEOUT_MASK)
		return I2C_CHANNEL_OPERATION_TIMEOUT;
	else if (value & DC_I2C_SW_STATUS__DC_I2C_SW_ABORTED_MASK)
		return I2C_CHANNEL_OPERATION_FAILED;
	else if (value & DC_I2C_SW_STATUS__DC_I2C_SW_DONE_MASK)
		return I2C_CHANNEL_OPERATION_SUCCEEDED;

	/*
	 * this is the case when HW used for communication, I2C_SW_STATUS
	 * could be zero
	 */
	return I2C_CHANNEL_OPERATION_SUCCEEDED;
}