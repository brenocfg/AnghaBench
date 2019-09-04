#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_9__ ;
typedef  struct TYPE_21__   TYPE_8__ ;
typedef  struct TYPE_20__   TYPE_7__ ;
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;
typedef  struct TYPE_13__   TYPE_11__ ;
typedef  struct TYPE_12__   TYPE_10__ ;

/* Type definitions */
struct TYPE_13__ {int /*<<< orphan*/  requested_pix_clk; } ;
struct TYPE_22__ {TYPE_11__ pix_clk_params; } ;
struct pipe_ctx {int /*<<< orphan*/  pll_settings; TYPE_9__ stream_res; struct clock_source* clock_source; TYPE_7__* stream; } ;
struct link_encoder {TYPE_10__* funcs; } ;
struct dc_link_settings {int dummy; } ;
struct dc_link {TYPE_4__* dc; struct link_encoder* link_enc; } ;
struct clock_source {scalar_t__ id; TYPE_8__* funcs; } ;
typedef  enum signal_type { ____Placeholder_signal_type } signal_type ;
typedef  enum clock_source_id { ____Placeholder_clock_source_id } clock_source_id ;
struct TYPE_21__ {int /*<<< orphan*/  (* program_pix_clk ) (struct clock_source*,TYPE_11__*,int /*<<< orphan*/ *) ;} ;
struct TYPE_19__ {int /*<<< orphan*/  pix_clk_khz; } ;
struct TYPE_20__ {TYPE_6__ timing; TYPE_5__* sink; } ;
struct TYPE_18__ {struct dc_link* link; } ;
struct TYPE_17__ {TYPE_3__* res_pool; TYPE_2__* current_state; } ;
struct TYPE_16__ {struct clock_source* dp_clock_source; } ;
struct TYPE_14__ {struct pipe_ctx* pipe_ctx; } ;
struct TYPE_15__ {TYPE_1__ res_ctx; } ;
struct TYPE_12__ {int /*<<< orphan*/  (* enable_dp_mst_output ) (struct link_encoder*,struct dc_link_settings const*,int) ;int /*<<< orphan*/  (* enable_dp_output ) (struct link_encoder*,struct dc_link_settings const*,int) ;} ;

/* Variables and functions */
 scalar_t__ CLOCK_SOURCE_ID_DP_DTO ; 
 unsigned int MAX_PIPES ; 
 scalar_t__ dc_is_dp_sst_signal (int) ; 
 int /*<<< orphan*/  dp_receiver_power_ctrl (struct dc_link*,int) ; 
 int /*<<< orphan*/  stub1 (struct clock_source*,TYPE_11__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (struct link_encoder*,struct dc_link_settings const*,int) ; 
 int /*<<< orphan*/  stub3 (struct link_encoder*,struct dc_link_settings const*,int) ; 

void dp_enable_link_phy(
	struct dc_link *link,
	enum signal_type signal,
	enum clock_source_id clock_source,
	const struct dc_link_settings *link_settings)
{
	struct link_encoder *link_enc = link->link_enc;

	struct pipe_ctx *pipes =
			link->dc->current_state->res_ctx.pipe_ctx;
	struct clock_source *dp_cs =
			link->dc->res_pool->dp_clock_source;
	unsigned int i;
	/* If the current pixel clock source is not DTO(happens after
	 * switching from HDMI passive dongle to DP on the same connector),
	 * switch the pixel clock source to DTO.
	 */
	for (i = 0; i < MAX_PIPES; i++) {
		if (pipes[i].stream != NULL &&
			pipes[i].stream->sink != NULL &&
			pipes[i].stream->sink->link == link) {
			if (pipes[i].clock_source != NULL &&
					pipes[i].clock_source->id != CLOCK_SOURCE_ID_DP_DTO) {
				pipes[i].clock_source = dp_cs;
				pipes[i].stream_res.pix_clk_params.requested_pix_clk =
						pipes[i].stream->timing.pix_clk_khz;
				pipes[i].clock_source->funcs->program_pix_clk(
							pipes[i].clock_source,
							&pipes[i].stream_res.pix_clk_params,
							&pipes[i].pll_settings);
			}
		}
	}

	if (dc_is_dp_sst_signal(signal)) {
		link_enc->funcs->enable_dp_output(
						link_enc,
						link_settings,
						clock_source);
	} else {
		link_enc->funcs->enable_dp_mst_output(
						link_enc,
						link_settings,
						clock_source);
	}

	dp_receiver_power_ctrl(link, true);
}