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
struct TYPE_3__ {scalar_t__ type; int address; int /*<<< orphan*/  length; int /*<<< orphan*/ * data; scalar_t__ delay; int /*<<< orphan*/  action; } ;
struct write_command_context {int mot; int transaction_complete; int operation_succeeded; TYPE_1__ request; int /*<<< orphan*/  status; int /*<<< orphan*/  current_write_length; int /*<<< orphan*/ * buffer; scalar_t__ max_defer_retry; scalar_t__ ack_m_retry; scalar_t__ defer_retry_i2c; scalar_t__ defer_retry_aux; scalar_t__ invalid_reply_retry_aux; scalar_t__ timed_out_retry_aux; } ;
struct TYPE_4__ {scalar_t__ address_space; int address; int /*<<< orphan*/ * data; int /*<<< orphan*/  length; } ;
struct i2caux_transaction_request {TYPE_2__ payload; int /*<<< orphan*/  status; } ;
struct aux_engine {scalar_t__ max_defer_write_retry; int /*<<< orphan*/  delay; } ;

/* Variables and functions */
 scalar_t__ AUX_DEFER_RETRY_COUNTER ; 
 scalar_t__ AUX_TRANSACTION_TYPE_DP ; 
 scalar_t__ AUX_TRANSACTION_TYPE_I2C ; 
 int /*<<< orphan*/  BREAK_TO_DEBUGGER () ; 
 int /*<<< orphan*/  DC_LOG_I2C_AUX (char*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  I2CAUX_TRANSACTION_ACTION_DP_WRITE ; 
 int /*<<< orphan*/  I2CAUX_TRANSACTION_ACTION_I2C_WRITE ; 
 int /*<<< orphan*/  I2CAUX_TRANSACTION_ACTION_I2C_WRITE_MOT ; 
 scalar_t__ I2CAUX_TRANSACTION_ADDRESS_SPACE_DPCD ; 
 scalar_t__ I2CAUX_TRANSACTION_ADDRESS_SPACE_I2C ; 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  process_write_request (struct aux_engine*,struct write_command_context*) ; 

__attribute__((used)) static bool write_command(
	struct aux_engine *engine,
	struct i2caux_transaction_request *request,
	bool middle_of_transaction)
{
	struct write_command_context ctx;

	ctx.mot = middle_of_transaction;
	ctx.buffer = request->payload.data;
	ctx.current_write_length = request->payload.length;
	ctx.timed_out_retry_aux = 0;
	ctx.invalid_reply_retry_aux = 0;
	ctx.defer_retry_aux = 0;
	ctx.defer_retry_i2c = 0;
	ctx.ack_m_retry = 0;
	ctx.transaction_complete = false;
	ctx.operation_succeeded = true;

	if (request->payload.address_space ==
		I2CAUX_TRANSACTION_ADDRESS_SPACE_DPCD) {
		ctx.request.type = AUX_TRANSACTION_TYPE_DP;
		ctx.request.action = I2CAUX_TRANSACTION_ACTION_DP_WRITE;
		ctx.request.address = request->payload.address;
	} else if (request->payload.address_space ==
		I2CAUX_TRANSACTION_ADDRESS_SPACE_I2C) {
		ctx.request.type = AUX_TRANSACTION_TYPE_I2C;
		ctx.request.action = middle_of_transaction ?
			I2CAUX_TRANSACTION_ACTION_I2C_WRITE_MOT :
			I2CAUX_TRANSACTION_ACTION_I2C_WRITE;
		ctx.request.address = request->payload.address >> 1;
	} else {
		/* in DAL2, there was no return in such case */
		BREAK_TO_DEBUGGER();
		return false;
	}

	ctx.request.delay = 0;

	ctx.max_defer_retry =
		(engine->max_defer_write_retry > AUX_DEFER_RETRY_COUNTER) ?
			engine->max_defer_write_retry : AUX_DEFER_RETRY_COUNTER;

	do {
		ctx.request.data = ctx.buffer;
		ctx.request.length = ctx.current_write_length;

		process_write_request(engine, &ctx);

		request->status = ctx.status;

		if (ctx.operation_succeeded && !ctx.transaction_complete)
			if (ctx.request.type == AUX_TRANSACTION_TYPE_I2C)
				msleep(engine->delay);
	} while (ctx.operation_succeeded && !ctx.transaction_complete);

	if (request->payload.address_space ==
		I2CAUX_TRANSACTION_ADDRESS_SPACE_DPCD) {
		DC_LOG_I2C_AUX("WRITE: addr:0x%x  value:0x%x Result:%d",
				request->payload.address,
				request->payload.data[0],
				ctx.operation_succeeded);
	}

	return ctx.operation_succeeded;
}