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
struct pipe_ctx {struct dc_stream_state* stream; } ;
struct dc_stream_state {TYPE_1__* sink; } ;
struct dc_state {int dummy; } ;
struct dc_link {TYPE_3__* dc; } ;
typedef  enum dc_status { ____Placeholder_dc_status } dc_status ;
struct TYPE_5__ {int /*<<< orphan*/  (* edp_wait_for_hpd_ready ) (struct dc_link*,int) ;int /*<<< orphan*/  (* edp_power_control ) (struct dc_link*,int) ;} ;
struct TYPE_6__ {TYPE_2__ hwss; } ;
struct TYPE_4__ {struct dc_link* link; } ;

/* Variables and functions */
 int enable_link_dp (struct dc_state*,struct pipe_ctx*) ; 
 int /*<<< orphan*/  stub1 (struct dc_link*,int) ; 
 int /*<<< orphan*/  stub2 (struct dc_link*,int) ; 

__attribute__((used)) static enum dc_status enable_link_edp(
		struct dc_state *state,
		struct pipe_ctx *pipe_ctx)
{
	enum dc_status status;
	struct dc_stream_state *stream = pipe_ctx->stream;
	struct dc_link *link = stream->sink->link;
	/*in case it is not on*/
	link->dc->hwss.edp_power_control(link, true);
	link->dc->hwss.edp_wait_for_hpd_ready(link, true);

	status = enable_link_dp(state, pipe_ctx);


	return status;
}