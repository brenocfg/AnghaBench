#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {TYPE_3__* stream_enc; } ;
struct pipe_ctx {struct dc_stream_state* stream; TYPE_4__ stream_res; } ;
struct ext_hdmi_settings {int /*<<< orphan*/  member_0; } ;
struct TYPE_13__ {scalar_t__ DSC; } ;
struct TYPE_14__ {TYPE_6__ flags; } ;
struct dc_stream_state {scalar_t__ signal; TYPE_7__ timing; int /*<<< orphan*/  link; TYPE_2__* sink; TYPE_1__* ctx; } ;
struct dc_link {unsigned short chip_caps; int /*<<< orphan*/  ddc; } ;
struct TYPE_12__ {int /*<<< orphan*/  (* disable_stream ) (struct pipe_ctx*) ;int /*<<< orphan*/  (* blank_stream ) (struct pipe_ctx*) ;} ;
struct dc {TYPE_5__ hwss; } ;
typedef  enum engine_id { ____Placeholder_engine_id } engine_id ;
struct TYPE_10__ {int id; } ;
struct TYPE_9__ {struct dc_link* link; } ;
struct TYPE_8__ {struct dc* dc; } ;

/* Variables and functions */
 unsigned short EXT_DISPLAY_PATH_CAPS__EXT_CHIP_MASK ; 
 unsigned short EXT_DISPLAY_PATH_CAPS__HDMI20_PI3EQX1204 ; 
 unsigned short EXT_DISPLAY_PATH_CAPS__HDMI20_TISN65DP159RSBT ; 
 scalar_t__ SIGNAL_TYPE_DISPLAY_PORT_MST ; 
 int /*<<< orphan*/  dal_ddc_service_write_scdc_data (int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ dc_is_dp_signal (scalar_t__) ; 
 scalar_t__ dc_is_hdmi_signal (scalar_t__) ; 
 int /*<<< orphan*/  deallocate_mst_payload (struct pipe_ctx*) ; 
 int /*<<< orphan*/  disable_link (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  dp_set_dsc_enable (struct pipe_ctx*,int) ; 
 scalar_t__ get_ext_hdmi_settings (struct pipe_ctx*,int,struct ext_hdmi_settings*) ; 
 int /*<<< orphan*/  stub1 (struct pipe_ctx*) ; 
 int /*<<< orphan*/  stub2 (struct pipe_ctx*) ; 
 int /*<<< orphan*/  write_i2c_default_retimer_setting (struct pipe_ctx*,int,int) ; 
 int /*<<< orphan*/  write_i2c_redriver_setting (struct pipe_ctx*,int) ; 
 int /*<<< orphan*/  write_i2c_retimer_setting (struct pipe_ctx*,int,int,struct ext_hdmi_settings*) ; 

void core_link_disable_stream(struct pipe_ctx *pipe_ctx)
{
	struct dc  *core_dc = pipe_ctx->stream->ctx->dc;
	struct dc_stream_state *stream = pipe_ctx->stream;
	struct dc_link *link = stream->sink->link;

	core_dc->hwss.blank_stream(pipe_ctx);

	if (pipe_ctx->stream->signal == SIGNAL_TYPE_DISPLAY_PORT_MST)
		deallocate_mst_payload(pipe_ctx);

	if (dc_is_hdmi_signal(pipe_ctx->stream->signal)) {
		struct ext_hdmi_settings settings = {0};
		enum engine_id eng_id = pipe_ctx->stream_res.stream_enc->id;

		unsigned short masked_chip_caps = link->chip_caps &
				EXT_DISPLAY_PATH_CAPS__EXT_CHIP_MASK;
		//Need to inform that sink is going to use legacy HDMI mode.
		dal_ddc_service_write_scdc_data(
			link->ddc,
			165000,//vbios only handles 165Mhz.
			false);
		if (masked_chip_caps == EXT_DISPLAY_PATH_CAPS__HDMI20_TISN65DP159RSBT) {
			/* DP159, Retimer settings */
			if (get_ext_hdmi_settings(pipe_ctx, eng_id, &settings))
				write_i2c_retimer_setting(pipe_ctx,
						false, false, &settings);
			else
				write_i2c_default_retimer_setting(pipe_ctx,
						false, false);
		} else if (masked_chip_caps == EXT_DISPLAY_PATH_CAPS__HDMI20_PI3EQX1204) {
			/* PI3EQX1204, Redriver settings */
			write_i2c_redriver_setting(pipe_ctx, false);
		}
	}
	core_dc->hwss.disable_stream(pipe_ctx);

	disable_link(pipe_ctx->stream->link, pipe_ctx->stream->signal);
#ifdef CONFIG_DRM_AMD_DC_DSC_SUPPORT
	if (pipe_ctx->stream->timing.flags.DSC) {
		if (dc_is_dp_signal(pipe_ctx->stream->signal))
			dp_set_dsc_enable(pipe_ctx, false);
	}
#endif
}