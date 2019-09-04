#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_8__ {int /*<<< orphan*/  DC_I2C_DDCX_SETUP; } ;
struct TYPE_5__ {struct dc_context* ctx; } ;
struct TYPE_6__ {TYPE_1__ base; } ;
struct TYPE_7__ {TYPE_2__ base; } ;
struct i2c_hw_engine_dce80 {int transaction_count; scalar_t__ buffer_used_bytes; TYPE_4__ addr; TYPE_3__ base; } ;
struct dc_context {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DC_I2C_CONTROL ; 
 int /*<<< orphan*/  DC_I2C_DDC1_CLK_DRIVE_EN ; 
 int /*<<< orphan*/  DC_I2C_DDC1_DATA_DRIVE_EN ; 
 int /*<<< orphan*/  DC_I2C_DDC1_DATA_DRIVE_SEL ; 
 int /*<<< orphan*/  DC_I2C_DDC1_INTRA_BYTE_DELAY ; 
 int /*<<< orphan*/  DC_I2C_DDC1_INTRA_TRANSACTION_DELAY ; 
 int /*<<< orphan*/  DC_I2C_DDC1_SETUP ; 
 int /*<<< orphan*/  DC_I2C_GO ; 
 int /*<<< orphan*/  DC_I2C_SEND_RESET ; 
 int /*<<< orphan*/  DC_I2C_SOFT_RESET ; 
 int /*<<< orphan*/  DC_I2C_SW_STATUS_RESET ; 
 int /*<<< orphan*/  DC_I2C_TRANSACTION_COUNT ; 
 int /*<<< orphan*/  dm_read_reg (struct dc_context*,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  dm_write_reg (struct dc_context*,int /*<<< orphan*/  const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmDC_I2C_CONTROL ; 
 int /*<<< orphan*/  set_reg_field_value (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void execute_transaction(
	struct i2c_hw_engine_dce80 *engine)
{
	uint32_t value = 0;
	struct dc_context *ctx = NULL;

	ctx = engine->base.base.base.ctx;

	{
		const uint32_t addr = engine->addr.DC_I2C_DDCX_SETUP;

		value = dm_read_reg(ctx, addr);

		set_reg_field_value(
			value,
			0,
			DC_I2C_DDC1_SETUP,
			DC_I2C_DDC1_DATA_DRIVE_EN);

		set_reg_field_value(
			value,
			0,
			DC_I2C_DDC1_SETUP,
			DC_I2C_DDC1_CLK_DRIVE_EN);

		set_reg_field_value(
			value,
			0,
			DC_I2C_DDC1_SETUP,
			DC_I2C_DDC1_DATA_DRIVE_SEL);

		set_reg_field_value(
			value,
			0,
			DC_I2C_DDC1_SETUP,
			DC_I2C_DDC1_INTRA_TRANSACTION_DELAY);

		set_reg_field_value(
			value,
			0,
			DC_I2C_DDC1_SETUP,
			DC_I2C_DDC1_INTRA_BYTE_DELAY);

		dm_write_reg(ctx, addr, value);
	}

	{
		const uint32_t addr = mmDC_I2C_CONTROL;

		value = dm_read_reg(ctx, addr);

		set_reg_field_value(
			value,
			0,
			DC_I2C_CONTROL,
			DC_I2C_SOFT_RESET);

		set_reg_field_value(
			value,
			0,
			DC_I2C_CONTROL,
			DC_I2C_SW_STATUS_RESET);

		set_reg_field_value(
			value,
			0,
			DC_I2C_CONTROL,
			DC_I2C_SEND_RESET);

		set_reg_field_value(
			value,
			0,
			DC_I2C_CONTROL,
			DC_I2C_GO);

		set_reg_field_value(
			value,
			engine->transaction_count - 1,
			DC_I2C_CONTROL,
			DC_I2C_TRANSACTION_COUNT);

		dm_write_reg(ctx, addr, value);
	}

	/* start I2C transfer */
	{
		const uint32_t addr = mmDC_I2C_CONTROL;

		value	= dm_read_reg(ctx, addr);

		set_reg_field_value(
			value,
			1,
			DC_I2C_CONTROL,
			DC_I2C_GO);

		dm_write_reg(ctx, addr, value);
	}

	/* all transactions were executed and HW buffer became empty
	 * (even though it actually happens when status becomes DONE) */
	engine->transaction_count = 0;
	engine->buffer_used_bytes = 0;
}