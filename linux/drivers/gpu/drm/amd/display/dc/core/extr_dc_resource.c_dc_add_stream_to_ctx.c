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
struct dc_stream_state {int dummy; } ;
struct dc_state {size_t stream_count; struct dc_stream_state** streams; } ;
struct dc {TYPE_3__* res_pool; TYPE_2__* ctx; } ;
typedef  enum dc_status { ____Placeholder_dc_status } dc_status ;
struct TYPE_6__ {size_t timing_generator_count; TYPE_1__* funcs; } ;
struct TYPE_5__ {int /*<<< orphan*/  logger; } ;
struct TYPE_4__ {int (* add_stream_to_ctx ) (struct dc*,struct dc_state*,struct dc_stream_state*) ;} ;

/* Variables and functions */
 int DC_ERROR_UNEXPECTED ; 
 int /*<<< orphan*/  DC_LOGGER_INIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DC_LOG_WARNING (char*,struct dc_stream_state*,...) ; 
 int DC_OK ; 
 int /*<<< orphan*/  dc_stream_retain (struct dc_stream_state*) ; 
 int stub1 (struct dc*,struct dc_state*,struct dc_stream_state*) ; 

enum dc_status dc_add_stream_to_ctx(
		struct dc *dc,
		struct dc_state *new_ctx,
		struct dc_stream_state *stream)
{
	enum dc_status res;
	DC_LOGGER_INIT(dc->ctx->logger);

	if (new_ctx->stream_count >= dc->res_pool->timing_generator_count) {
		DC_LOG_WARNING("Max streams reached, can't add stream %p !\n", stream);
		return DC_ERROR_UNEXPECTED;
	}

	new_ctx->streams[new_ctx->stream_count] = stream;
	dc_stream_retain(stream);
	new_ctx->stream_count++;

	res = dc->res_pool->funcs->add_stream_to_ctx(dc, new_ctx, stream);
	if (res != DC_OK)
		DC_LOG_WARNING("Adding stream %p to context failed with err %d!\n", stream, res);

	return res;
}