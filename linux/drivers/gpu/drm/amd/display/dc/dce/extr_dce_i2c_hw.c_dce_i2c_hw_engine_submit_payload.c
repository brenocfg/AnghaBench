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
typedef  scalar_t__ uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct i2c_request_transaction_data {scalar_t__ length; scalar_t__ status; int /*<<< orphan*/  data; scalar_t__ address; int /*<<< orphan*/  action; } ;
struct i2c_payload {scalar_t__ length; int address; int /*<<< orphan*/  write; int /*<<< orphan*/  data; } ;
struct dce_i2c_hw {int dummy; } ;
typedef  enum i2c_channel_operation_result { ____Placeholder_i2c_channel_operation_result } i2c_channel_operation_result ;

/* Variables and functions */
 int /*<<< orphan*/  DCE_I2C_TRANSACTION_ACTION_I2C_READ ; 
 int /*<<< orphan*/  DCE_I2C_TRANSACTION_ACTION_I2C_READ_MOT ; 
 int /*<<< orphan*/  DCE_I2C_TRANSACTION_ACTION_I2C_WRITE ; 
 int /*<<< orphan*/  DCE_I2C_TRANSACTION_ACTION_I2C_WRITE_MOT ; 
 scalar_t__ I2C_CHANNEL_OPERATION_ENGINE_BUSY ; 
 scalar_t__ I2C_CHANNEL_OPERATION_FAILED ; 
 int I2C_CHANNEL_OPERATION_SUCCEEDED ; 
 int dce_i2c_hw_engine_wait_on_operation_result (struct dce_i2c_hw*,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ get_hw_buffer_available_size (struct dce_i2c_hw*) ; 
 int /*<<< orphan*/  get_transaction_timeout_hw (struct dce_i2c_hw*,scalar_t__) ; 
 int /*<<< orphan*/  process_channel_reply (struct dce_i2c_hw*,struct i2c_payload*) ; 
 int /*<<< orphan*/  submit_channel_request_hw (struct dce_i2c_hw*,struct i2c_request_transaction_data*) ; 

bool dce_i2c_hw_engine_submit_payload(
	struct dce_i2c_hw *dce_i2c_hw,
	struct i2c_payload *payload,
	bool middle_of_transaction)
{

	struct i2c_request_transaction_data request;

	uint32_t transaction_timeout;

	enum i2c_channel_operation_result operation_result;

	bool result = false;

	/* We need following:
	 * transaction length will not exceed
	 * the number of free bytes in HW buffer (minus one for address)
	 */

	if (payload->length >=
			get_hw_buffer_available_size(dce_i2c_hw)) {
		return false;
	}

	if (!payload->write)
		request.action = middle_of_transaction ?
			DCE_I2C_TRANSACTION_ACTION_I2C_READ_MOT :
			DCE_I2C_TRANSACTION_ACTION_I2C_READ;
	else
		request.action = middle_of_transaction ?
			DCE_I2C_TRANSACTION_ACTION_I2C_WRITE_MOT :
			DCE_I2C_TRANSACTION_ACTION_I2C_WRITE;


	request.address = (uint8_t) ((payload->address << 1) | !payload->write);
	request.length = payload->length;
	request.data = payload->data;

	/* obtain timeout value before submitting request */

	transaction_timeout = get_transaction_timeout_hw(
		dce_i2c_hw, payload->length + 1);

	submit_channel_request_hw(
		dce_i2c_hw, &request);

	if ((request.status == I2C_CHANNEL_OPERATION_FAILED) ||
		(request.status == I2C_CHANNEL_OPERATION_ENGINE_BUSY))
		return false;

	/* wait until transaction proceed */

	operation_result = dce_i2c_hw_engine_wait_on_operation_result(
		dce_i2c_hw,
		transaction_timeout,
		I2C_CHANNEL_OPERATION_ENGINE_BUSY);

	/* update transaction status */

	if (operation_result == I2C_CHANNEL_OPERATION_SUCCEEDED)
		result = true;

	if (result && (!payload->write))
		process_channel_reply(dce_i2c_hw, payload);

	return result;
}