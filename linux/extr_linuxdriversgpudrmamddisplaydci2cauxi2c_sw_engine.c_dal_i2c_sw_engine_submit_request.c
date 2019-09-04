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
typedef  scalar_t__ uint8_t ;
struct TYPE_3__ {int /*<<< orphan*/  data; int /*<<< orphan*/  length; scalar_t__ address; } ;
struct i2caux_transaction_request {scalar_t__ operation; int /*<<< orphan*/  status; TYPE_1__ payload; } ;
struct i2c_engine {TYPE_2__* funcs; } ;
struct i2c_sw_engine {struct i2c_engine base; } ;
struct i2c_request_transaction_data {scalar_t__ status; int /*<<< orphan*/  data; int /*<<< orphan*/  length; scalar_t__ address; int /*<<< orphan*/  action; } ;
struct engine {int dummy; } ;
typedef  enum i2c_channel_operation_result { ____Placeholder_i2c_channel_operation_result } i2c_channel_operation_result ;
struct TYPE_4__ {int (* get_channel_status ) (struct i2c_engine*,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* submit_channel_request ) (struct i2c_engine*,struct i2c_request_transaction_data*) ;} ;

/* Variables and functions */
 struct i2c_sw_engine* FROM_ENGINE (struct engine*) ; 
 int /*<<< orphan*/  I2CAUX_TRANSACTION_ACTION_I2C_READ ; 
 int /*<<< orphan*/  I2CAUX_TRANSACTION_ACTION_I2C_READ_MOT ; 
 int /*<<< orphan*/  I2CAUX_TRANSACTION_ACTION_I2C_WRITE ; 
 int /*<<< orphan*/  I2CAUX_TRANSACTION_ACTION_I2C_WRITE_MOT ; 
 scalar_t__ I2CAUX_TRANSACTION_READ ; 
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
 int /*<<< orphan*/  stub1 (struct i2c_engine*,struct i2c_request_transaction_data*) ; 
 int stub2 (struct i2c_engine*,int /*<<< orphan*/ *) ; 

bool dal_i2c_sw_engine_submit_request(
	struct engine *engine,
	struct i2caux_transaction_request *i2caux_request,
	bool middle_of_transaction)
{
	struct i2c_sw_engine *sw_engine = FROM_ENGINE(engine);

	struct i2c_engine *base = &sw_engine->base;

	struct i2c_request_transaction_data request;
	bool operation_succeeded = false;

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
		/* in DAL2, there was no "return false" */
		return false;
	}

	request.address = (uint8_t)i2caux_request->payload.address;
	request.length = i2caux_request->payload.length;
	request.data = i2caux_request->payload.data;

	base->funcs->submit_channel_request(base, &request);

	if ((request.status == I2C_CHANNEL_OPERATION_ENGINE_BUSY) ||
		(request.status == I2C_CHANNEL_OPERATION_FAILED))
		i2caux_request->status =
			I2CAUX_TRANSACTION_STATUS_FAILED_CHANNEL_BUSY;
	else {
		enum i2c_channel_operation_result operation_result;

		do {
			operation_result =
				base->funcs->get_channel_status(base, NULL);

			switch (operation_result) {
			case I2C_CHANNEL_OPERATION_SUCCEEDED:
				i2caux_request->status =
					I2CAUX_TRANSACTION_STATUS_SUCCEEDED;
				operation_succeeded = true;
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
			break;
			}
		} while (operation_result == I2C_CHANNEL_OPERATION_ENGINE_BUSY);
	}

	return operation_succeeded;
}