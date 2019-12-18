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
typedef  int uint16_t ;
struct i2c_request_transaction_data {int action; int /*<<< orphan*/  status; int /*<<< orphan*/  data; int /*<<< orphan*/  length; int /*<<< orphan*/  address; } ;
struct ddc {int dummy; } ;
struct dce_i2c_sw {int clock_delay; int /*<<< orphan*/  ctx; struct ddc* ddc; } ;

/* Variables and functions */
#define  DCE_I2C_TRANSACTION_ACTION_I2C_READ 131 
#define  DCE_I2C_TRANSACTION_ACTION_I2C_READ_MOT 130 
#define  DCE_I2C_TRANSACTION_ACTION_I2C_WRITE 129 
#define  DCE_I2C_TRANSACTION_ACTION_I2C_WRITE_MOT 128 
 int /*<<< orphan*/  I2C_CHANNEL_OPERATION_FAILED ; 
 int /*<<< orphan*/  I2C_CHANNEL_OPERATION_SUCCEEDED ; 
 int i2c_read_sw (int /*<<< orphan*/ ,struct ddc*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int i2c_write_sw (int /*<<< orphan*/ ,struct ddc*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int start_sync_sw (int /*<<< orphan*/ ,struct ddc*,int) ; 
 int /*<<< orphan*/  stop_sync_sw (int /*<<< orphan*/ ,struct ddc*,int) ; 

void dce_i2c_sw_engine_submit_channel_request(
	struct dce_i2c_sw *engine,
	struct i2c_request_transaction_data *req)
{
	struct ddc *ddc = engine->ddc;
	uint16_t clock_delay_div_4 = engine->clock_delay >> 2;

	/* send sync (start / repeated start) */

	bool result = start_sync_sw(engine->ctx, ddc, clock_delay_div_4);

	/* process payload */

	if (result) {
		switch (req->action) {
		case DCE_I2C_TRANSACTION_ACTION_I2C_WRITE:
		case DCE_I2C_TRANSACTION_ACTION_I2C_WRITE_MOT:
			result = i2c_write_sw(engine->ctx, ddc, clock_delay_div_4,
				req->address, req->length, req->data);
		break;
		case DCE_I2C_TRANSACTION_ACTION_I2C_READ:
		case DCE_I2C_TRANSACTION_ACTION_I2C_READ_MOT:
			result = i2c_read_sw(engine->ctx, ddc, clock_delay_div_4,
				req->address, req->length, req->data);
		break;
		default:
			result = false;
		break;
		}
	}

	/* send stop if not 'mot' or operation failed */

	if (!result ||
		(req->action == DCE_I2C_TRANSACTION_ACTION_I2C_WRITE) ||
		(req->action == DCE_I2C_TRANSACTION_ACTION_I2C_READ))
		if (!stop_sync_sw(engine->ctx, ddc, clock_delay_div_4))
			result = false;

	req->status = result ?
		I2C_CHANNEL_OPERATION_SUCCEEDED :
		I2C_CHANNEL_OPERATION_FAILED;
}