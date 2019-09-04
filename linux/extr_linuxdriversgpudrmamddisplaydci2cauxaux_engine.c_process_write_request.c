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
struct TYPE_4__ {int /*<<< orphan*/  data; int /*<<< orphan*/  length; } ;
struct write_command_context {int operation_succeeded; int /*<<< orphan*/  status; int /*<<< orphan*/  timed_out_retry_aux; int /*<<< orphan*/  invalid_reply_retry_aux; int /*<<< orphan*/  reply_data; TYPE_2__ reply; int /*<<< orphan*/  returned_byte; int /*<<< orphan*/  request; } ;
struct aux_engine {TYPE_1__* funcs; } ;
typedef  enum aux_channel_operation_result { ____Placeholder_aux_channel_operation_result } aux_channel_operation_result ;
struct TYPE_3__ {int (* get_channel_status ) (struct aux_engine*,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* submit_channel_request ) (struct aux_engine*,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
#define  AUX_CHANNEL_OPERATION_FAILED_HPD_DISCON 131 
#define  AUX_CHANNEL_OPERATION_FAILED_INVALID_REPLY 130 
#define  AUX_CHANNEL_OPERATION_FAILED_TIMEOUT 129 
#define  AUX_CHANNEL_OPERATION_SUCCEEDED 128 
 int /*<<< orphan*/  AUX_INVALID_REPLY_RETRY_COUNTER ; 
 int /*<<< orphan*/  AUX_TIMED_OUT_RETRY_COUNTER ; 
 int /*<<< orphan*/  I2CAUX_TRANSACTION_STATUS_FAILED_HPD_DISCON ; 
 int /*<<< orphan*/  I2CAUX_TRANSACTION_STATUS_FAILED_PROTOCOL_ERROR ; 
 int /*<<< orphan*/  I2CAUX_TRANSACTION_STATUS_FAILED_TIMEOUT ; 
 int /*<<< orphan*/  I2CAUX_TRANSACTION_STATUS_UNKNOWN ; 
 int /*<<< orphan*/  process_write_reply (struct aux_engine*,struct write_command_context*) ; 
 int /*<<< orphan*/  stub1 (struct aux_engine*,int /*<<< orphan*/ *) ; 
 int stub2 (struct aux_engine*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void process_write_request(
	struct aux_engine *engine,
	struct write_command_context *ctx)
{
	enum aux_channel_operation_result operation_result;

	engine->funcs->submit_channel_request(engine, &ctx->request);

	operation_result = engine->funcs->get_channel_status(
		engine, &ctx->returned_byte);

	switch (operation_result) {
	case AUX_CHANNEL_OPERATION_SUCCEEDED:
		ctx->timed_out_retry_aux = 0;
		ctx->invalid_reply_retry_aux = 0;

		ctx->reply.length = ctx->returned_byte;
		ctx->reply.data = ctx->reply_data;

		process_write_reply(engine, ctx);
	break;
	case AUX_CHANNEL_OPERATION_FAILED_INVALID_REPLY:
		++ctx->invalid_reply_retry_aux;

		if (ctx->invalid_reply_retry_aux >
			AUX_INVALID_REPLY_RETRY_COUNTER) {
			ctx->status =
				I2CAUX_TRANSACTION_STATUS_FAILED_PROTOCOL_ERROR;
			ctx->operation_succeeded = false;
		} else
			udelay(400);
	break;
	case AUX_CHANNEL_OPERATION_FAILED_TIMEOUT:
		++ctx->timed_out_retry_aux;

		if (ctx->timed_out_retry_aux > AUX_TIMED_OUT_RETRY_COUNTER) {
			ctx->status = I2CAUX_TRANSACTION_STATUS_FAILED_TIMEOUT;
			ctx->operation_succeeded = false;
		} else {
			/* DP 1.2a, table 2-58:
			 * "S3: AUX Request CMD PENDING:
			 * retry 3 times, with 400usec wait on each"
			 * The HW timeout is set to 550usec,
			 * so we should not wait here */
		}
	break;
	case AUX_CHANNEL_OPERATION_FAILED_HPD_DISCON:
		ctx->status = I2CAUX_TRANSACTION_STATUS_FAILED_HPD_DISCON;
		ctx->operation_succeeded = false;
	break;
	default:
		ctx->status = I2CAUX_TRANSACTION_STATUS_UNKNOWN;
		ctx->operation_succeeded = false;
	}
}