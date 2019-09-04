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
struct TYPE_4__ {int status; } ;
struct read_command_context {int operation_succeeded; int transaction_complete; void* status; int /*<<< orphan*/  defer_retry_i2c; int /*<<< orphan*/  defer_retry_aux; int /*<<< orphan*/  invalid_reply_retry_aux_on_ack; int /*<<< orphan*/  returned_byte; int /*<<< orphan*/  offset; int /*<<< orphan*/  current_read_length; TYPE_2__ reply; } ;
struct aux_engine {TYPE_1__* funcs; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* process_channel_reply ) (struct aux_engine*,TYPE_2__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  AUX_DEFER_RETRY_COUNTER ; 
 int /*<<< orphan*/  AUX_INVALID_REPLY_RETRY_COUNTER ; 
#define  AUX_TRANSACTION_REPLY_AUX_ACK 132 
#define  AUX_TRANSACTION_REPLY_AUX_DEFER 131 
#define  AUX_TRANSACTION_REPLY_AUX_NACK 130 
#define  AUX_TRANSACTION_REPLY_HPD_DISCON 129 
#define  AUX_TRANSACTION_REPLY_I2C_DEFER 128 
 void* I2CAUX_TRANSACTION_STATUS_FAILED_HPD_DISCON ; 
 void* I2CAUX_TRANSACTION_STATUS_FAILED_NACK ; 
 void* I2CAUX_TRANSACTION_STATUS_FAILED_PROTOCOL_ERROR ; 
 void* I2CAUX_TRANSACTION_STATUS_FAILED_TIMEOUT ; 
 void* I2CAUX_TRANSACTION_STATUS_SUCCEEDED ; 
 void* I2CAUX_TRANSACTION_STATUS_UNKNOWN ; 
 int /*<<< orphan*/  stub1 (struct aux_engine*,TYPE_2__*) ; 

__attribute__((used)) static void process_read_reply(
	struct aux_engine *engine,
	struct read_command_context *ctx)
{
	engine->funcs->process_channel_reply(engine, &ctx->reply);

	switch (ctx->reply.status) {
	case AUX_TRANSACTION_REPLY_AUX_ACK:
		ctx->defer_retry_aux = 0;
		if (ctx->returned_byte > ctx->current_read_length) {
			ctx->status =
				I2CAUX_TRANSACTION_STATUS_FAILED_PROTOCOL_ERROR;
			ctx->operation_succeeded = false;
		} else if (ctx->returned_byte < ctx->current_read_length) {
			ctx->current_read_length -= ctx->returned_byte;

			ctx->offset += ctx->returned_byte;

			++ctx->invalid_reply_retry_aux_on_ack;

			if (ctx->invalid_reply_retry_aux_on_ack >
				AUX_INVALID_REPLY_RETRY_COUNTER) {
				ctx->status =
				I2CAUX_TRANSACTION_STATUS_FAILED_PROTOCOL_ERROR;
				ctx->operation_succeeded = false;
			}
		} else {
			ctx->status = I2CAUX_TRANSACTION_STATUS_SUCCEEDED;
			ctx->transaction_complete = true;
			ctx->operation_succeeded = true;
		}
	break;
	case AUX_TRANSACTION_REPLY_AUX_NACK:
		ctx->status = I2CAUX_TRANSACTION_STATUS_FAILED_NACK;
		ctx->operation_succeeded = false;
	break;
	case AUX_TRANSACTION_REPLY_AUX_DEFER:
		++ctx->defer_retry_aux;

		if (ctx->defer_retry_aux > AUX_DEFER_RETRY_COUNTER) {
			ctx->status = I2CAUX_TRANSACTION_STATUS_FAILED_TIMEOUT;
			ctx->operation_succeeded = false;
		}
	break;
	case AUX_TRANSACTION_REPLY_I2C_DEFER:
		ctx->defer_retry_aux = 0;

		++ctx->defer_retry_i2c;

		if (ctx->defer_retry_i2c > AUX_DEFER_RETRY_COUNTER) {
			ctx->status = I2CAUX_TRANSACTION_STATUS_FAILED_TIMEOUT;
			ctx->operation_succeeded = false;
		}
	break;
	case AUX_TRANSACTION_REPLY_HPD_DISCON:
		ctx->status = I2CAUX_TRANSACTION_STATUS_FAILED_HPD_DISCON;
		ctx->operation_succeeded = false;
	break;
	default:
		ctx->status = I2CAUX_TRANSACTION_STATUS_UNKNOWN;
		ctx->operation_succeeded = false;
	}
}