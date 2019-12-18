#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_9__ ;
typedef  struct TYPE_19__   TYPE_8__ ;
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;
typedef  struct TYPE_11__   TYPE_10__ ;

/* Type definitions */
struct TYPE_14__ {TYPE_2__* tg; } ;
struct pipe_ctx {TYPE_3__ stream_res; struct dc_stream_state const* stream; } ;
struct TYPE_18__ {int /*<<< orphan*/  link_spread; int /*<<< orphan*/  link_rate; int /*<<< orphan*/  lane_count; } ;
struct dm_pp_single_disp_config {int v_refresh; int /*<<< orphan*/  sym_clock; TYPE_7__ link_settings; int /*<<< orphan*/  transmitter; int /*<<< orphan*/  ddi_channel_mapping; int /*<<< orphan*/  src_width; int /*<<< orphan*/  src_height; int /*<<< orphan*/  pipe_idx; int /*<<< orphan*/  signal; } ;
struct dm_pp_display_configuration {int display_count; struct dm_pp_single_disp_config* disp_configs; } ;
struct TYPE_11__ {int pix_clk_100hz; int h_total; int v_total; } ;
struct TYPE_15__ {int /*<<< orphan*/  width; int /*<<< orphan*/  height; } ;
struct dc_stream_state {TYPE_10__ timing; int /*<<< orphan*/  phy_pix_clk; TYPE_9__* link; TYPE_4__ src; int /*<<< orphan*/  signal; scalar_t__ dpms_off; } ;
struct TYPE_12__ {struct pipe_ctx* pipe_ctx; } ;
struct dc_state {int stream_count; TYPE_1__ res_ctx; struct dc_stream_state** streams; } ;
struct TYPE_19__ {int /*<<< orphan*/  link_spread; int /*<<< orphan*/  link_rate; int /*<<< orphan*/  lane_count; } ;
struct TYPE_16__ {int /*<<< orphan*/  raw; } ;
struct TYPE_20__ {TYPE_8__ cur_link_settings; TYPE_6__* link_enc; TYPE_5__ ddi_channel_mapping; } ;
struct TYPE_17__ {int /*<<< orphan*/  transmitter; } ;
struct TYPE_13__ {int /*<<< orphan*/  inst; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int MAX_PIPES ; 

void dce110_fill_display_configs(
	const struct dc_state *context,
	struct dm_pp_display_configuration *pp_display_cfg)
{
	int j;
	int num_cfgs = 0;

	for (j = 0; j < context->stream_count; j++) {
		int k;

		const struct dc_stream_state *stream = context->streams[j];
		struct dm_pp_single_disp_config *cfg =
			&pp_display_cfg->disp_configs[num_cfgs];
		const struct pipe_ctx *pipe_ctx = NULL;

		for (k = 0; k < MAX_PIPES; k++)
			if (stream == context->res_ctx.pipe_ctx[k].stream) {
				pipe_ctx = &context->res_ctx.pipe_ctx[k];
				break;
			}

		ASSERT(pipe_ctx != NULL);

		/* only notify active stream */
		if (stream->dpms_off)
			continue;

		num_cfgs++;
		cfg->signal = pipe_ctx->stream->signal;
		cfg->pipe_idx = pipe_ctx->stream_res.tg->inst;
		cfg->src_height = stream->src.height;
		cfg->src_width = stream->src.width;
		cfg->ddi_channel_mapping =
			stream->link->ddi_channel_mapping.raw;
		cfg->transmitter =
			stream->link->link_enc->transmitter;
		cfg->link_settings.lane_count =
			stream->link->cur_link_settings.lane_count;
		cfg->link_settings.link_rate =
			stream->link->cur_link_settings.link_rate;
		cfg->link_settings.link_spread =
			stream->link->cur_link_settings.link_spread;
		cfg->sym_clock = stream->phy_pix_clk;
		/* Round v_refresh*/
		cfg->v_refresh = stream->timing.pix_clk_100hz * 100;
		cfg->v_refresh /= stream->timing.h_total;
		cfg->v_refresh = (cfg->v_refresh + stream->timing.v_total / 2)
							/ stream->timing.v_total;
	}

	pp_display_cfg->display_count = num_cfgs;
}