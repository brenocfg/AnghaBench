#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_3__ {int /*<<< orphan*/  DC_I2C_DDCX_SETUP; } ;
struct i2c_hw_engine_dce80 {int engine_id; TYPE_1__ addr; } ;
struct TYPE_4__ {int /*<<< orphan*/  ctx; } ;
struct i2c_engine {TYPE_2__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  DC_I2C_ARBITRATION ; 
 int DC_I2C_ARBITRATION__DC_I2C_SW_PRIORITY_NORMAL ; 
 int /*<<< orphan*/  DC_I2C_CONTROL ; 
 int /*<<< orphan*/  DC_I2C_DDC1_ENABLE ; 
 int /*<<< orphan*/  DC_I2C_DDC1_SETUP ; 
 int /*<<< orphan*/  DC_I2C_DDC1_TIME_LIMIT ; 
 int /*<<< orphan*/  DC_I2C_DDC_SELECT ; 
 int /*<<< orphan*/  DC_I2C_GO ; 
 int /*<<< orphan*/  DC_I2C_NO_QUEUED_SW_GO ; 
 int /*<<< orphan*/  DC_I2C_SEND_RESET ; 
 int /*<<< orphan*/  DC_I2C_SOFT_RESET ; 
 int /*<<< orphan*/  DC_I2C_SW_PRIORITY ; 
 int /*<<< orphan*/  DC_I2C_SW_STATUS_RESET ; 
 int /*<<< orphan*/  DC_I2C_TRANSACTION_COUNT ; 
 struct i2c_hw_engine_dce80* FROM_I2C_ENGINE (struct i2c_engine*) ; 
 int I2C_SETUP_TIME_LIMIT ; 
 int /*<<< orphan*/  dm_read_reg (int /*<<< orphan*/ ,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  dm_write_reg (int /*<<< orphan*/ ,int /*<<< orphan*/  const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  const mmDC_I2C_ARBITRATION ; 
 int /*<<< orphan*/  mmDC_I2C_CONTROL ; 
 int /*<<< orphan*/  set_reg_field_value (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool setup_engine(
	struct i2c_engine *i2c_engine)
{
	uint32_t value = 0;
	struct i2c_hw_engine_dce80 *engine = FROM_I2C_ENGINE(i2c_engine);

	/* Program pin select */
	{
		const uint32_t addr = mmDC_I2C_CONTROL;

		value = dm_read_reg(i2c_engine->base.ctx, addr);

		set_reg_field_value(
			value,
			0,
			DC_I2C_CONTROL,
			DC_I2C_GO);

		set_reg_field_value(
			value,
			0,
			DC_I2C_CONTROL,
			DC_I2C_SOFT_RESET);

		set_reg_field_value(
			value,
			0,
			DC_I2C_CONTROL,
			DC_I2C_SEND_RESET);

		set_reg_field_value(
			value,
			0,
			DC_I2C_CONTROL,
			DC_I2C_SW_STATUS_RESET);

		set_reg_field_value(
			value,
			0,
			DC_I2C_CONTROL,
			DC_I2C_TRANSACTION_COUNT);

		set_reg_field_value(
			value,
			engine->engine_id,
			DC_I2C_CONTROL,
			DC_I2C_DDC_SELECT);

		dm_write_reg(i2c_engine->base.ctx, addr, value);
	}

	/* Program time limit */
	{
		const uint32_t addr = engine->addr.DC_I2C_DDCX_SETUP;

		value = dm_read_reg(i2c_engine->base.ctx, addr);

		set_reg_field_value(
			value,
			I2C_SETUP_TIME_LIMIT,
			DC_I2C_DDC1_SETUP,
			DC_I2C_DDC1_TIME_LIMIT);

		set_reg_field_value(
			value,
			1,
			DC_I2C_DDC1_SETUP,
			DC_I2C_DDC1_ENABLE);

		dm_write_reg(i2c_engine->base.ctx, addr, value);
	}

	/* Program HW priority
	 * set to High - interrupt software I2C at any time
	 * Enable restart of SW I2C that was interrupted by HW
	 * disable queuing of software while I2C is in use by HW */
	{
		value = dm_read_reg(i2c_engine->base.ctx,
				mmDC_I2C_ARBITRATION);

		set_reg_field_value(
			value,
			0,
			DC_I2C_ARBITRATION,
			DC_I2C_NO_QUEUED_SW_GO);

		set_reg_field_value(
			value,
			DC_I2C_ARBITRATION__DC_I2C_SW_PRIORITY_NORMAL,
			DC_I2C_ARBITRATION,
			DC_I2C_SW_PRIORITY);

		dm_write_reg(i2c_engine->base.ctx,
				mmDC_I2C_ARBITRATION, value);
	}

	return true;
}