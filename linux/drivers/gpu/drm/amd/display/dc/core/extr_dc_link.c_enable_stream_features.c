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
struct TYPE_2__ {int IGNORE_MSA_TIMING_PARAM; } ;
union down_spread_ctrl {scalar_t__ raw; TYPE_1__ bits; } ;
struct pipe_ctx {struct dc_stream_state* stream; } ;
struct dc_stream_state {scalar_t__ ignore_msa_timing_param; struct dc_link* link; } ;
struct dc_link {int dummy; } ;
typedef  int /*<<< orphan*/  old_downspread ;
typedef  int /*<<< orphan*/  new_downspread ;

/* Variables and functions */
 int /*<<< orphan*/  DP_DOWNSPREAD_CTRL ; 
 int /*<<< orphan*/  core_link_read_dpcd (struct dc_link*,int /*<<< orphan*/ ,scalar_t__*,int) ; 
 int /*<<< orphan*/  core_link_write_dpcd (struct dc_link*,int /*<<< orphan*/ ,scalar_t__*,int) ; 

__attribute__((used)) static void enable_stream_features(struct pipe_ctx *pipe_ctx)
{
	struct dc_stream_state *stream = pipe_ctx->stream;
	struct dc_link *link = stream->link;
	union down_spread_ctrl old_downspread;
	union down_spread_ctrl new_downspread;

	core_link_read_dpcd(link, DP_DOWNSPREAD_CTRL,
			&old_downspread.raw, sizeof(old_downspread));

	new_downspread.raw = old_downspread.raw;

	new_downspread.bits.IGNORE_MSA_TIMING_PARAM =
			(stream->ignore_msa_timing_param) ? 1 : 0;

	if (new_downspread.raw != old_downspread.raw) {
		core_link_write_dpcd(link, DP_DOWNSPREAD_CTRL,
			&new_downspread.raw, sizeof(new_downspread));
	}
}