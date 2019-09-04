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
struct i2c_hw_engine_dce110 {TYPE_1__* i2c_mask; } ;
struct i2c_engine {int dummy; } ;
typedef  enum i2c_channel_operation_result { ____Placeholder_i2c_channel_operation_result } i2c_channel_operation_result ;
struct TYPE_2__ {scalar_t__ DC_I2C_SW_STOPPED_ON_NACK; scalar_t__ DC_I2C_SW_TIMEOUT; scalar_t__ DC_I2C_SW_ABORTED; scalar_t__ DC_I2C_SW_DONE; } ;

/* Variables and functions */
 scalar_t__ DC_I2C_STATUS__DC_I2C_STATUS_USED_BY_SW ; 
 int /*<<< orphan*/  DC_I2C_SW_STATUS ; 
 struct i2c_hw_engine_dce110* FROM_I2C_ENGINE (struct i2c_engine*) ; 
 int I2C_CHANNEL_OPERATION_ENGINE_BUSY ; 
 int I2C_CHANNEL_OPERATION_FAILED ; 
 int I2C_CHANNEL_OPERATION_NO_RESPONSE ; 
 int I2C_CHANNEL_OPERATION_SUCCEEDED ; 
 int I2C_CHANNEL_OPERATION_TIMEOUT ; 
 scalar_t__ REG_GET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 

__attribute__((used)) static enum i2c_channel_operation_result get_channel_status(
	struct i2c_engine *i2c_engine,
	uint8_t *returned_bytes)
{
	uint32_t i2c_sw_status = 0;
	struct i2c_hw_engine_dce110 *hw_engine = FROM_I2C_ENGINE(i2c_engine);
	uint32_t value =
			REG_GET(DC_I2C_SW_STATUS, DC_I2C_SW_STATUS, &i2c_sw_status);

	if (i2c_sw_status == DC_I2C_STATUS__DC_I2C_STATUS_USED_BY_SW)
		return I2C_CHANNEL_OPERATION_ENGINE_BUSY;
	else if (value & hw_engine->i2c_mask->DC_I2C_SW_STOPPED_ON_NACK)
		return I2C_CHANNEL_OPERATION_NO_RESPONSE;
	else if (value & hw_engine->i2c_mask->DC_I2C_SW_TIMEOUT)
		return I2C_CHANNEL_OPERATION_TIMEOUT;
	else if (value & hw_engine->i2c_mask->DC_I2C_SW_ABORTED)
		return I2C_CHANNEL_OPERATION_FAILED;
	else if (value & hw_engine->i2c_mask->DC_I2C_SW_DONE)
		return I2C_CHANNEL_OPERATION_SUCCEEDED;

	/*
	 * this is the case when HW used for communication, I2C_SW_STATUS
	 * could be zero
	 */
	return I2C_CHANNEL_OPERATION_SUCCEEDED;
}