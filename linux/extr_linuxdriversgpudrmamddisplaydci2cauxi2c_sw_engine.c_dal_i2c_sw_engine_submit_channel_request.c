#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int uint16_t ;
struct i2c_sw_engine {int clock_delay; } ;
struct i2c_request_transaction_data {int action; int /*<<< orphan*/  status; int /*<<< orphan*/  data; int /*<<< orphan*/  length; int /*<<< orphan*/  address; } ;
struct TYPE_2__ {int /*<<< orphan*/  ctx; struct ddc* ddc; } ;
struct i2c_engine {TYPE_1__ base; } ;
struct ddc {int dummy; } ;

/* Variables and functions */
 struct i2c_sw_engine* FROM_I2C_ENGINE (struct i2c_engine*) ; 
#define  I2CAUX_TRANSACTION_ACTION_I2C_READ 131 
#define  I2CAUX_TRANSACTION_ACTION_I2C_READ_MOT 130 
#define  I2CAUX_TRANSACTION_ACTION_I2C_WRITE 129 
#define  I2CAUX_TRANSACTION_ACTION_I2C_WRITE_MOT 128 
 int /*<<< orphan*/  I2C_CHANNEL_OPERATION_FAILED ; 
 int /*<<< orphan*/  I2C_CHANNEL_OPERATION_SUCCEEDED ; 
 int i2c_read (int /*<<< orphan*/ ,struct ddc*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int i2c_write (int /*<<< orphan*/ ,struct ddc*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int start_sync (int /*<<< orphan*/ ,struct ddc*,int) ; 
 int /*<<< orphan*/  stop_sync (int /*<<< orphan*/ ,struct ddc*,int) ; 

void dal_i2c_sw_engine_submit_channel_request(
	struct i2c_engine *engine,
	struct i2c_request_transaction_data *req)
{
	struct i2c_sw_engine *sw_engine = FROM_I2C_ENGINE(engine);

	struct ddc *ddc = engine->base.ddc;
	uint16_t clock_delay_div_4 = sw_engine->clock_delay >> 2;

	/* send sync (start / repeated start) */

	bool result = start_sync(engine->base.ctx, ddc, clock_delay_div_4);

	/* process payload */

	if (result) {
		switch (req->action) {
		case I2CAUX_TRANSACTION_ACTION_I2C_WRITE:
		case I2CAUX_TRANSACTION_ACTION_I2C_WRITE_MOT:
			result = i2c_write(engine->base.ctx, ddc, clock_delay_div_4,
				req->address, req->length, req->data);
		break;
		case I2CAUX_TRANSACTION_ACTION_I2C_READ:
		case I2CAUX_TRANSACTION_ACTION_I2C_READ_MOT:
			result = i2c_read(engine->base.ctx, ddc, clock_delay_div_4,
				req->address, req->length, req->data);
		break;
		default:
			result = false;
		break;
		}
	}

	/* send stop if not 'mot' or operation failed */

	if (!result ||
		(req->action == I2CAUX_TRANSACTION_ACTION_I2C_WRITE) ||
		(req->action == I2CAUX_TRANSACTION_ACTION_I2C_READ))
		if (!stop_sync(engine->base.ctx, ddc, clock_delay_div_4))
			result = false;

	req->status = result ?
		I2C_CHANNEL_OPERATION_SUCCEEDED :
		I2C_CHANNEL_OPERATION_FAILED;
}