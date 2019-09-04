#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {void* action; } ;
struct TYPE_6__ {int status; } ;
struct write_command_context {int operation_succeeded; int transaction_complete; void* status; int /*<<< orphan*/  max_defer_retry; int /*<<< orphan*/  defer_retry_i2c; int /*<<< orphan*/  mot; TYPE_2__ request; int /*<<< orphan*/  current_write_length; int /*<<< orphan*/  defer_retry_aux; int /*<<< orphan*/  ack_m_retry; int /*<<< orphan*/  returned_byte; TYPE_3__ reply; } ;
struct aux_engine {TYPE_1__* funcs; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* process_channel_reply ) (struct aux_engine*,TYPE_3__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  AUX_DEFER_RETRY_COUNTER ; 
#define  AUX_TRANSACTION_REPLY_AUX_ACK 132 
#define  AUX_TRANSACTION_REPLY_AUX_DEFER 131 
#define  AUX_TRANSACTION_REPLY_AUX_NACK 130 
#define  AUX_TRANSACTION_REPLY_HPD_DISCON 129 
#define  AUX_TRANSACTION_REPLY_I2C_DEFER 128 
 void* I2CAUX_TRANSACTION_ACTION_I2C_STATUS_REQUEST ; 
 void* I2CAUX_TRANSACTION_ACTION_I2C_STATUS_REQUEST_MOT ; 
 void* I2CAUX_TRANSACTION_STATUS_FAILED_HPD_DISCON ; 
 void* I2CAUX_TRANSACTION_STATUS_FAILED_NACK ; 
 void* I2CAUX_TRANSACTION_STATUS_FAILED_TIMEOUT ; 
 void* I2CAUX_TRANSACTION_STATUS_SUCCEEDED ; 
 void* I2CAUX_TRANSACTION_STATUS_UNKNOWN ; 
 int /*<<< orphan*/  stub1 (struct aux_engine*,TYPE_3__*) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void process_write_reply(
	struct aux_engine *engine,
	struct write_command_context *ctx)
{
	engine->funcs->process_channel_reply(engine, &ctx->reply);

	switch (ctx->reply.status) {
	case AUX_TRANSACTION_REPLY_AUX_ACK:
		ctx->operation_succeeded = true;

		if (ctx->returned_byte) {
			ctx->request.action = ctx->mot ?
			I2CAUX_TRANSACTION_ACTION_I2C_STATUS_REQUEST_MOT :
			I2CAUX_TRANSACTION_ACTION_I2C_STATUS_REQUEST;

			ctx->current_write_length = 0;

			++ctx->ack_m_retry;

			if (ctx->ack_m_retry > AUX_DEFER_RETRY_COUNTER) {
				ctx->status =
				I2CAUX_TRANSACTION_STATUS_FAILED_TIMEOUT;
				ctx->operation_succeeded = false;
			} else
				udelay(300);
		} else {
			ctx->status = I2CAUX_TRANSACTION_STATUS_SUCCEEDED;
			ctx->defer_retry_aux = 0;
			ctx->ack_m_retry = 0;
			ctx->transaction_complete = true;
		}
	break;
	case AUX_TRANSACTION_REPLY_AUX_NACK:
		ctx->status = I2CAUX_TRANSACTION_STATUS_FAILED_NACK;
		ctx->operation_succeeded = false;
	break;
	case AUX_TRANSACTION_REPLY_AUX_DEFER:
		++ctx->defer_retry_aux;

		if (ctx->defer_retry_aux > ctx->max_defer_retry) {
			ctx->status = I2CAUX_TRANSACTION_STATUS_FAILED_TIMEOUT;
			ctx->operation_succeeded = false;
		}
	break;
	case AUX_TRANSACTION_REPLY_I2C_DEFER:
		ctx->defer_retry_aux = 0;
		ctx->current_write_length = 0;

		ctx->request.action = ctx->mot ?
			I2CAUX_TRANSACTION_ACTION_I2C_STATUS_REQUEST_MOT :
			I2CAUX_TRANSACTION_ACTION_I2C_STATUS_REQUEST;

		++ctx->defer_retry_i2c;

		if (ctx->defer_retry_i2c > ctx->max_defer_retry) {
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