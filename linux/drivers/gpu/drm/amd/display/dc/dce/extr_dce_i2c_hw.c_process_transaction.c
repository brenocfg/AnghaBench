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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint32_t ;
struct i2c_request_transaction_data {int action; int /*<<< orphan*/  address; int /*<<< orphan*/  status; int /*<<< orphan*/ * data; scalar_t__ length; } ;
struct dce_i2c_hw {int transaction_count; int /*<<< orphan*/  buffer_used_bytes; scalar_t__ buffer_used_write; } ;

/* Variables and functions */
 int DCE_I2C_TRANSACTION_ACTION_I2C_READ ; 
 int DCE_I2C_TRANSACTION_ACTION_I2C_WRITE ; 
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
 int /*<<< orphan*/  DC_I2C_TRANSACTION1 ; 
 int /*<<< orphan*/  DC_I2C_TRANSACTION2 ; 
 int /*<<< orphan*/  DC_I2C_TRANSACTION3 ; 
 int /*<<< orphan*/  I2C_CHANNEL_OPERATION_ENGINE_BUSY ; 
 scalar_t__ REG_SET_2 (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ REG_SET_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  REG_UPDATE_5 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int) ; 
 scalar_t__ is_hw_busy (struct dce_i2c_hw*) ; 

__attribute__((used)) static bool process_transaction(
	struct dce_i2c_hw *dce_i2c_hw,
	struct i2c_request_transaction_data *request)
{
	uint32_t length = request->length;
	uint8_t *buffer = request->data;

	bool last_transaction = false;
	uint32_t value = 0;

	if (is_hw_busy(dce_i2c_hw)) {
		request->status = I2C_CHANNEL_OPERATION_ENGINE_BUSY;
		return false;
	}

	last_transaction = ((dce_i2c_hw->transaction_count == 3) ||
			(request->action == DCE_I2C_TRANSACTION_ACTION_I2C_WRITE) ||
			(request->action & DCE_I2C_TRANSACTION_ACTION_I2C_READ));


	switch (dce_i2c_hw->transaction_count) {
	case 0:
		REG_UPDATE_5(DC_I2C_TRANSACTION0,
				 DC_I2C_STOP_ON_NACK0, 1,
				 DC_I2C_START0, 1,
				 DC_I2C_RW0, 0 != (request->action & DCE_I2C_TRANSACTION_ACTION_I2C_READ),
				 DC_I2C_COUNT0, length,
				 DC_I2C_STOP0, last_transaction ? 1 : 0);
		break;
	case 1:
		REG_UPDATE_5(DC_I2C_TRANSACTION1,
				 DC_I2C_STOP_ON_NACK0, 1,
				 DC_I2C_START0, 1,
				 DC_I2C_RW0, 0 != (request->action & DCE_I2C_TRANSACTION_ACTION_I2C_READ),
				 DC_I2C_COUNT0, length,
				 DC_I2C_STOP0, last_transaction ? 1 : 0);
		break;
	case 2:
		REG_UPDATE_5(DC_I2C_TRANSACTION2,
				 DC_I2C_STOP_ON_NACK0, 1,
				 DC_I2C_START0, 1,
				 DC_I2C_RW0, 0 != (request->action & DCE_I2C_TRANSACTION_ACTION_I2C_READ),
				 DC_I2C_COUNT0, length,
				 DC_I2C_STOP0, last_transaction ? 1 : 0);
		break;
	case 3:
		REG_UPDATE_5(DC_I2C_TRANSACTION3,
				 DC_I2C_STOP_ON_NACK0, 1,
				 DC_I2C_START0, 1,
				 DC_I2C_RW0, 0 != (request->action & DCE_I2C_TRANSACTION_ACTION_I2C_READ),
				 DC_I2C_COUNT0, length,
				 DC_I2C_STOP0, last_transaction ? 1 : 0);
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
	 * for I2C receive operation, the LSB must be programmed to 1.
	 */
	if (dce_i2c_hw->transaction_count == 0) {
		value = REG_SET_4(DC_I2C_DATA, 0,
				  DC_I2C_DATA_RW, false,
				  DC_I2C_DATA, request->address,
				  DC_I2C_INDEX, 0,
				  DC_I2C_INDEX_WRITE, 1);
		dce_i2c_hw->buffer_used_write = 0;
	} else
		value = REG_SET_2(DC_I2C_DATA, 0,
			  DC_I2C_DATA_RW, false,
			  DC_I2C_DATA, request->address);

	dce_i2c_hw->buffer_used_write++;

	if (!(request->action & DCE_I2C_TRANSACTION_ACTION_I2C_READ)) {
		while (length) {
			REG_SET_2(DC_I2C_DATA, value,
				  DC_I2C_INDEX_WRITE, 0,
				  DC_I2C_DATA, *buffer++);
			dce_i2c_hw->buffer_used_write++;
			--length;
		}
	}

	++dce_i2c_hw->transaction_count;
	dce_i2c_hw->buffer_used_bytes += length + 1;

	return last_transaction;
}