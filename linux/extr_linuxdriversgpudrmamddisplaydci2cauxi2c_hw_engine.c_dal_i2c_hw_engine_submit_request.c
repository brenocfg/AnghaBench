#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_7__ {scalar_t__ length; int /*<<< orphan*/  data; scalar_t__ address; } ;
struct i2caux_transaction_request {scalar_t__ operation; TYPE_2__ payload; int /*<<< orphan*/  status; } ;
struct i2c_request_transaction_data {scalar_t__ length; scalar_t__ status; int /*<<< orphan*/  data; scalar_t__ address; int /*<<< orphan*/  action; } ;
struct i2c_reply_transaction_data {scalar_t__ length; int /*<<< orphan*/  data; } ;
struct TYPE_9__ {TYPE_3__* funcs; } ;
struct i2c_hw_engine {TYPE_4__ base; TYPE_1__* funcs; } ;
struct engine {int dummy; } ;
typedef  enum i2c_channel_operation_result { ____Placeholder_i2c_channel_operation_result } i2c_channel_operation_result ;
struct TYPE_8__ {int /*<<< orphan*/  (* process_channel_reply ) (TYPE_4__*,struct i2c_reply_transaction_data*) ;int /*<<< orphan*/  (* submit_channel_request ) (TYPE_4__*,struct i2c_request_transaction_data*) ;} ;
struct TYPE_6__ {scalar_t__ (* get_hw_buffer_available_size ) (struct i2c_hw_engine*) ;int (* wait_on_operation_result ) (struct i2c_hw_engine*,int /*<<< orphan*/ ,scalar_t__) ;int /*<<< orphan*/  (* get_transaction_timeout ) (struct i2c_hw_engine*,scalar_t__) ;} ;

/* Variables and functions */
 struct i2c_hw_engine* FROM_ENGINE (struct engine*) ; 
 int /*<<< orphan*/  I2CAUX_TRANSACTION_ACTION_I2C_READ ; 
 int /*<<< orphan*/  I2CAUX_TRANSACTION_ACTION_I2C_READ_MOT ; 
 int /*<<< orphan*/  I2CAUX_TRANSACTION_ACTION_I2C_WRITE ; 
 int /*<<< orphan*/  I2CAUX_TRANSACTION_ACTION_I2C_WRITE_MOT ; 
 scalar_t__ I2CAUX_TRANSACTION_READ ; 
 int /*<<< orphan*/  I2CAUX_TRANSACTION_STATUS_FAILED_BUFFER_OVERFLOW ; 
 int /*<<< orphan*/  I2CAUX_TRANSACTION_STATUS_FAILED_CHANNEL_BUSY ; 
 int /*<<< orphan*/  I2CAUX_TRANSACTION_STATUS_FAILED_INCOMPLETE ; 
 int /*<<< orphan*/  I2CAUX_TRANSACTION_STATUS_FAILED_INVALID_OPERATION ; 
 int /*<<< orphan*/  I2CAUX_TRANSACTION_STATUS_FAILED_NACK ; 
 int /*<<< orphan*/  I2CAUX_TRANSACTION_STATUS_FAILED_OPERATION ; 
 int /*<<< orphan*/  I2CAUX_TRANSACTION_STATUS_FAILED_TIMEOUT ; 
 int /*<<< orphan*/  I2CAUX_TRANSACTION_STATUS_SUCCEEDED ; 
 scalar_t__ I2CAUX_TRANSACTION_WRITE ; 
 scalar_t__ I2C_CHANNEL_OPERATION_ENGINE_BUSY ; 
#define  I2C_CHANNEL_OPERATION_FAILED 131 
#define  I2C_CHANNEL_OPERATION_NO_RESPONSE 130 
#define  I2C_CHANNEL_OPERATION_SUCCEEDED 129 
#define  I2C_CHANNEL_OPERATION_TIMEOUT 128 
 scalar_t__ stub1 (struct i2c_hw_engine*) ; 
 int /*<<< orphan*/  stub2 (struct i2c_hw_engine*,scalar_t__) ; 
 int /*<<< orphan*/  stub3 (TYPE_4__*,struct i2c_request_transaction_data*) ; 
 int stub4 (struct i2c_hw_engine*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  stub5 (TYPE_4__*,struct i2c_reply_transaction_data*) ; 

bool dal_i2c_hw_engine_submit_request(
	struct engine *engine,
	struct i2caux_transaction_request *i2caux_request,
	bool middle_of_transaction)
{
	struct i2c_hw_engine *hw_engine = FROM_ENGINE(engine);

	struct i2c_request_transaction_data request;

	uint32_t transaction_timeout;

	enum i2c_channel_operation_result operation_result;

	bool result = false;

	/* We need following:
	 * transaction length will not exceed
	 * the number of free bytes in HW buffer (minus one for address)*/

	if (i2caux_request->payload.length >=
		hw_engine->funcs->get_hw_buffer_available_size(hw_engine)) {
		i2caux_request->status =
			I2CAUX_TRANSACTION_STATUS_FAILED_BUFFER_OVERFLOW;
		return false;
	}

	if (i2caux_request->operation == I2CAUX_TRANSACTION_READ)
		request.action = middle_of_transaction ?
			I2CAUX_TRANSACTION_ACTION_I2C_READ_MOT :
			I2CAUX_TRANSACTION_ACTION_I2C_READ;
	else if (i2caux_request->operation == I2CAUX_TRANSACTION_WRITE)
		request.action = middle_of_transaction ?
			I2CAUX_TRANSACTION_ACTION_I2C_WRITE_MOT :
			I2CAUX_TRANSACTION_ACTION_I2C_WRITE;
	else {
		i2caux_request->status =
			I2CAUX_TRANSACTION_STATUS_FAILED_INVALID_OPERATION;
		/* [anaumov] in DAL2, there was no "return false" */
		return false;
	}

	request.address = (uint8_t)i2caux_request->payload.address;
	request.length = i2caux_request->payload.length;
	request.data = i2caux_request->payload.data;

	/* obtain timeout value before submitting request */

	transaction_timeout = hw_engine->funcs->get_transaction_timeout(
		hw_engine, i2caux_request->payload.length + 1);

	hw_engine->base.funcs->submit_channel_request(
		&hw_engine->base, &request);

	if ((request.status == I2C_CHANNEL_OPERATION_FAILED) ||
		(request.status == I2C_CHANNEL_OPERATION_ENGINE_BUSY)) {
		i2caux_request->status =
			I2CAUX_TRANSACTION_STATUS_FAILED_CHANNEL_BUSY;
		return false;
	}

	/* wait until transaction proceed */

	operation_result = hw_engine->funcs->wait_on_operation_result(
		hw_engine,
		transaction_timeout,
		I2C_CHANNEL_OPERATION_ENGINE_BUSY);

	/* update transaction status */

	switch (operation_result) {
	case I2C_CHANNEL_OPERATION_SUCCEEDED:
		i2caux_request->status =
			I2CAUX_TRANSACTION_STATUS_SUCCEEDED;
		result = true;
	break;
	case I2C_CHANNEL_OPERATION_NO_RESPONSE:
		i2caux_request->status =
			I2CAUX_TRANSACTION_STATUS_FAILED_NACK;
	break;
	case I2C_CHANNEL_OPERATION_TIMEOUT:
		i2caux_request->status =
			I2CAUX_TRANSACTION_STATUS_FAILED_TIMEOUT;
	break;
	case I2C_CHANNEL_OPERATION_FAILED:
		i2caux_request->status =
			I2CAUX_TRANSACTION_STATUS_FAILED_INCOMPLETE;
	break;
	default:
		i2caux_request->status =
			I2CAUX_TRANSACTION_STATUS_FAILED_OPERATION;
	}

	if (result && (i2caux_request->operation == I2CAUX_TRANSACTION_READ)) {
		struct i2c_reply_transaction_data reply;

		reply.data = i2caux_request->payload.data;
		reply.length = i2caux_request->payload.length;

		hw_engine->base.funcs->
			process_channel_reply(&hw_engine->base, &reply);
	}

	return result;
}