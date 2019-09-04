#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
struct i2c_request_transaction_data {int length; int action; int address; int /*<<< orphan*/ * data; } ;
struct TYPE_4__ {struct dc_context* ctx; } ;
struct TYPE_5__ {TYPE_1__ base; } ;
struct TYPE_6__ {TYPE_2__ base; } ;
struct i2c_hw_engine_dce80 {size_t transaction_count; int buffer_used_bytes; TYPE_3__ base; } ;
struct dc_context {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DC_I2C_COUNT0 ; 
 int /*<<< orphan*/  DC_I2C_DATA ; 
 int /*<<< orphan*/  DC_I2C_DATA_RW ; 
 int /*<<< orphan*/  DC_I2C_INDEX ; 
 int /*<<< orphan*/  DC_I2C_INDEX_WRITE ; 
 int /*<<< orphan*/  DC_I2C_RW0 ; 
 int /*<<< orphan*/  DC_I2C_START0 ; 
 int /*<<< orphan*/  DC_I2C_STOP0 ; 
 int /*<<< orphan*/  DC_I2C_STOP_ON_NACK0 ; 
 int /*<<< orphan*/  DC_I2C_TRANSACTION0 ; 
 int I2CAUX_TRANSACTION_ACTION_I2C_READ ; 
 int I2CAUX_TRANSACTION_ACTION_I2C_WRITE ; 
 int dm_read_reg (struct dc_context*,int const) ; 
 int /*<<< orphan*/  dm_write_reg (struct dc_context*,int const,int) ; 
 int const mmDC_I2C_DATA ; 
 int /*<<< orphan*/  set_reg_field_value (int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int* transaction_addr ; 

__attribute__((used)) static bool process_transaction(
	struct i2c_hw_engine_dce80 *engine,
	struct i2c_request_transaction_data *request)
{
	uint32_t length = request->length;
	uint8_t *buffer = request->data;

	bool last_transaction = false;
	uint32_t value = 0;

	struct dc_context *ctx = NULL;

	ctx = engine->base.base.base.ctx;

	{
		const uint32_t addr =
			transaction_addr[engine->transaction_count];

		value = dm_read_reg(ctx, addr);

		set_reg_field_value(
			value,
			1,
			DC_I2C_TRANSACTION0,
			DC_I2C_STOP_ON_NACK0);

		set_reg_field_value(
			value,
			1,
			DC_I2C_TRANSACTION0,
			DC_I2C_START0);

		if ((engine->transaction_count == 3) ||
		(request->action == I2CAUX_TRANSACTION_ACTION_I2C_WRITE) ||
		(request->action & I2CAUX_TRANSACTION_ACTION_I2C_READ)) {

			set_reg_field_value(
				value,
				1,
				DC_I2C_TRANSACTION0,
				DC_I2C_STOP0);

			last_transaction = true;
		} else
			set_reg_field_value(
				value,
				0,
				DC_I2C_TRANSACTION0,
				DC_I2C_STOP0);

		set_reg_field_value(
			value,
			(0 != (request->action &
					I2CAUX_TRANSACTION_ACTION_I2C_READ)),
			DC_I2C_TRANSACTION0,
			DC_I2C_RW0);

		set_reg_field_value(
			value,
			length,
			DC_I2C_TRANSACTION0,
			DC_I2C_COUNT0);

		dm_write_reg(ctx, addr, value);
	}

	/* Write the I2C address and I2C data
	 * into the hardware circular buffer, one byte per entry.
	 * As an example, the 7-bit I2C slave address for CRT monitor
	 * for reading DDC/EDID information is 0b1010001.
	 * For an I2C send operation, the LSB must be programmed to 0;
	 * for I2C receive operation, the LSB must be programmed to 1. */

	{
		value = 0;

		set_reg_field_value(
			value,
			false,
			DC_I2C_DATA,
			DC_I2C_DATA_RW);

		set_reg_field_value(
			value,
			request->address,
			DC_I2C_DATA,
			DC_I2C_DATA);

		if (engine->transaction_count == 0) {
			set_reg_field_value(
				value,
				0,
				DC_I2C_DATA,
				DC_I2C_INDEX);

			/*enable index write*/
			set_reg_field_value(
				value,
				1,
				DC_I2C_DATA,
				DC_I2C_INDEX_WRITE);
		}

		dm_write_reg(ctx, mmDC_I2C_DATA, value);

		if (!(request->action & I2CAUX_TRANSACTION_ACTION_I2C_READ)) {

			set_reg_field_value(
				value,
				0,
				DC_I2C_DATA,
				DC_I2C_INDEX_WRITE);

			while (length) {

				set_reg_field_value(
					value,
					*buffer++,
					DC_I2C_DATA,
					DC_I2C_DATA);

				dm_write_reg(ctx, mmDC_I2C_DATA, value);
				--length;
			}
		}
	}

	++engine->transaction_count;
	engine->buffer_used_bytes += length + 1;

	return last_transaction;
}