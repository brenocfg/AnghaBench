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
struct pipe_ctx {TYPE_1__* stream; } ;
struct dc_state {int dummy; } ;
struct TYPE_4__ {scalar_t__ lane_count; } ;
struct dc_link {int /*<<< orphan*/  ctx; TYPE_2__ cur_link_settings; } ;
typedef  enum dc_status { ____Placeholder_dc_status } dc_status ;
struct TYPE_3__ {struct dc_link* link; } ;

/* Variables and functions */
 int DC_OK ; 
 scalar_t__ LANE_COUNT_UNKNOWN ; 
 int /*<<< orphan*/  dm_helpers_dp_mst_clear_payload_allocation_table (int /*<<< orphan*/ ,struct dc_link*) ; 
 int /*<<< orphan*/  dm_helpers_dp_mst_poll_pending_down_reply (int /*<<< orphan*/ ,struct dc_link*) ; 
 int /*<<< orphan*/  dp_enable_mst_on_sink (struct dc_link*,int) ; 
 int enable_link_dp (struct dc_state*,struct pipe_ctx*) ; 

__attribute__((used)) static enum dc_status enable_link_dp_mst(
		struct dc_state *state,
		struct pipe_ctx *pipe_ctx)
{
	struct dc_link *link = pipe_ctx->stream->link;

	/* sink signal type after MST branch is MST. Multiple MST sinks
	 * share one link. Link DP PHY is enable or training only once.
	 */
	if (link->cur_link_settings.lane_count != LANE_COUNT_UNKNOWN)
		return DC_OK;

	/* clear payload table */
	dm_helpers_dp_mst_clear_payload_allocation_table(link->ctx, link);

	/* to make sure the pending down rep can be processed
	 * before enabling the link
	 */
	dm_helpers_dp_mst_poll_pending_down_reply(link->ctx, link);

	/* set the sink to MST mode before enabling the link */
	dp_enable_mst_on_sink(link, true);

	return enable_link_dp(state, pipe_ctx);
}