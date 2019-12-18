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
struct i2c_request_transaction_data {scalar_t__ status; int /*<<< orphan*/  data; int /*<<< orphan*/  length; scalar_t__ address; int /*<<< orphan*/  action; } ;
struct i2c_payload {int address; int /*<<< orphan*/  data; int /*<<< orphan*/  length; int /*<<< orphan*/  write; } ;
struct dce_i2c_sw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DCE_I2C_TRANSACTION_ACTION_I2C_READ ; 
 int /*<<< orphan*/  DCE_I2C_TRANSACTION_ACTION_I2C_READ_MOT ; 
 int /*<<< orphan*/  DCE_I2C_TRANSACTION_ACTION_I2C_WRITE ; 
 int /*<<< orphan*/  DCE_I2C_TRANSACTION_ACTION_I2C_WRITE_MOT ; 
 scalar_t__ I2C_CHANNEL_OPERATION_ENGINE_BUSY ; 
 scalar_t__ I2C_CHANNEL_OPERATION_FAILED ; 
 int /*<<< orphan*/  dce_i2c_sw_engine_submit_channel_request (struct dce_i2c_sw*,struct i2c_request_transaction_data*) ; 

bool dce_i2c_sw_engine_submit_payload(
	struct dce_i2c_sw *engine,
	struct i2c_payload *payload,
	bool middle_of_transaction)
{
	struct i2c_request_transaction_data request;

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

	dce_i2c_sw_engine_submit_channel_request(engine, &request);

	if ((request.status == I2C_CHANNEL_OPERATION_ENGINE_BUSY) ||
		(request.status == I2C_CHANNEL_OPERATION_FAILED))
		return false;

	return true;
}