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
typedef  scalar_t__ uint32_t ;
struct i2c_request_transaction_data {int action; int /*<<< orphan*/  address; int /*<<< orphan*/ * data; scalar_t__ length; } ;
struct TYPE_4__ {struct dc_context* ctx; } ;
struct TYPE_5__ {TYPE_1__ base; } ;
struct TYPE_6__ {TYPE_2__ base; } ;
struct i2c_hw_engine_dce110 {int transaction_count; int /*<<< orphan*/  buffer_used_bytes; scalar_t__ buffer_used_write; TYPE_3__ base; } ;
struct dc_context {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DC_I2C_DATA ; 
 int /*<<< orphan*/  DC_I2C_DATA_RW ; 
 int /*<<< orphan*/  DC_I2C_INDEX ; 
 int /*<<< orphan*/  DC_I2C_INDEX_WRITE ; 
 int I2CAUX_TRANSACTION_ACTION_I2C_READ ; 
 scalar_t__ REG_SET_2 (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ REG_SET_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SET_I2C_TRANSACTION (int) ; 

__attribute__((used)) static bool process_transaction(
	struct i2c_hw_engine_dce110 *hw_engine,
	struct i2c_request_transaction_data *request)
{
	uint32_t length = request->length;
	uint8_t *buffer = request->data;
	uint32_t value = 0;

	bool last_transaction = false;

	struct dc_context *ctx = NULL;

	ctx = hw_engine->base.base.base.ctx;



	switch (hw_engine->transaction_count) {
	case 0:
		SET_I2C_TRANSACTION(0);
		break;
	case 1:
		SET_I2C_TRANSACTION(1);
		break;
	case 2:
		SET_I2C_TRANSACTION(2);
		break;
	case 3:
		SET_I2C_TRANSACTION(3);
		break;
	default:
		/* TODO Warning ? */
		break;
	}


	/* Write the I2C address and I2C data
	 * into the hardware circular buffer, one byte per entry.
	 * As an example, the 7-bit I2C slave address for CRT monitor
	 * for reading DDC/EDID information is 0b1010001.
	 * For an I2C send operation, the LSB must be programmed to 0;
	 * for I2C receive operation, the LSB must be programmed to 1. */
	if (hw_engine->transaction_count == 0) {
		value = REG_SET_4(DC_I2C_DATA, 0,
				  DC_I2C_DATA_RW, false,
				  DC_I2C_DATA, request->address,
				  DC_I2C_INDEX, 0,
				  DC_I2C_INDEX_WRITE, 1);
		hw_engine->buffer_used_write = 0;
	} else
		value = REG_SET_2(DC_I2C_DATA, 0,
				  DC_I2C_DATA_RW, false,
				  DC_I2C_DATA, request->address);

	hw_engine->buffer_used_write++;

	if (!(request->action & I2CAUX_TRANSACTION_ACTION_I2C_READ)) {
		while (length) {
			REG_SET_2(DC_I2C_DATA, value,
					DC_I2C_INDEX_WRITE, 0,
					DC_I2C_DATA, *buffer++);
			hw_engine->buffer_used_write++;
			--length;
		}
	}

	++hw_engine->transaction_count;
	hw_engine->buffer_used_bytes += length + 1;

	return last_transaction;
}