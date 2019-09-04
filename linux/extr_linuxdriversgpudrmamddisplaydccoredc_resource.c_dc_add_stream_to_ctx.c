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
struct dc_stream_state {int dummy; } ;
struct dc_state {size_t stream_count; struct dc_stream_state** streams; } ;
struct dc_context {int dummy; } ;
struct dc {TYPE_2__* res_pool; struct dc_context* ctx; } ;
typedef  enum dc_status { ____Placeholder_dc_status } dc_status ;
struct TYPE_4__ {size_t timing_generator_count; TYPE_1__* funcs; } ;
struct TYPE_3__ {int (* add_stream_to_ctx ) (struct dc*,struct dc_state*,struct dc_stream_state*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DC_ERROR (char*,struct dc_stream_state*,...) ; 
 int DC_ERROR_UNEXPECTED ; 
 int DC_OK ; 
 int /*<<< orphan*/  dc_stream_retain (struct dc_stream_state*) ; 
 int stub1 (struct dc*,struct dc_state*,struct dc_stream_state*) ; 

enum dc_status dc_add_stream_to_ctx(
		struct dc *dc,
		struct dc_state *new_ctx,
		struct dc_stream_state *stream)
{
	struct dc_context *dc_ctx = dc->ctx;
	enum dc_status res;

	if (new_ctx->stream_count >= dc->res_pool->timing_generator_count) {
		DC_ERROR("Max streams reached, can't add stream %p !\n", stream);
		return DC_ERROR_UNEXPECTED;
	}

	new_ctx->streams[new_ctx->stream_count] = stream;
	dc_stream_retain(stream);
	new_ctx->stream_count++;

	res = dc->res_pool->funcs->add_stream_to_ctx(dc, new_ctx, stream);
	if (res != DC_OK)
		DC_ERROR("Adding stream %p to context failed with err %d!\n", stream, res);

	return res;
}