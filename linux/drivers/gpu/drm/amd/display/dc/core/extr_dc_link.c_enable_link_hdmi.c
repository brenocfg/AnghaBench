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
struct TYPE_9__ {TYPE_1__* stream_enc; } ;
struct pipe_ctx {struct dc_stream_state* stream; TYPE_6__* clock_source; TYPE_2__ stream_res; } ;
struct ext_hdmi_settings {int /*<<< orphan*/  member_0; } ;
struct TYPE_10__ {int /*<<< orphan*/  LTE_340MCSC_SCRAMBLE; } ;
struct TYPE_11__ {int h_addressable; int v_addressable; int pix_clk_100hz; int display_color_depth; scalar_t__ pixel_encoding; TYPE_3__ flags; } ;
struct dc_stream_state {int phy_pix_clk; int /*<<< orphan*/  signal; TYPE_4__ timing; struct dc_link* link; } ;
struct dc_link_settings {int dummy; } ;
struct dc_link {unsigned short chip_caps; int /*<<< orphan*/  ddc; TYPE_7__* link_enc; int /*<<< orphan*/  cur_link_settings; } ;
typedef  enum engine_id { ____Placeholder_engine_id } engine_id ;
typedef  enum dc_color_depth { ____Placeholder_dc_color_depth } dc_color_depth ;
struct TYPE_14__ {TYPE_5__* funcs; } ;
struct TYPE_13__ {int /*<<< orphan*/  id; } ;
struct TYPE_12__ {int /*<<< orphan*/  (* enable_tmds_output ) (TYPE_7__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ;} ;
struct TYPE_8__ {int id; } ;

/* Variables and functions */
 int COLOR_DEPTH_888 ; 
 unsigned short EXT_DISPLAY_PATH_CAPS__EXT_CHIP_MASK ; 
 unsigned short EXT_DISPLAY_PATH_CAPS__HDMI20_PI3EQX1204 ; 
 unsigned short EXT_DISPLAY_PATH_CAPS__HDMI20_TISN65DP159RSBT ; 
 scalar_t__ PIXEL_ENCODING_YCBCR422 ; 
 int /*<<< orphan*/  dal_ddc_service_read_scdc_data (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dal_ddc_service_write_scdc_data (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ dc_is_hdmi_signal (int /*<<< orphan*/ ) ; 
 scalar_t__ get_ext_hdmi_settings (struct pipe_ctx*,int,struct ext_hdmi_settings*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (TYPE_7__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  write_i2c_default_retimer_setting (struct pipe_ctx*,int,int) ; 
 int /*<<< orphan*/  write_i2c_redriver_setting (struct pipe_ctx*,int) ; 
 int /*<<< orphan*/  write_i2c_retimer_setting (struct pipe_ctx*,int,int,struct ext_hdmi_settings*) ; 

__attribute__((used)) static void enable_link_hdmi(struct pipe_ctx *pipe_ctx)
{
	struct dc_stream_state *stream = pipe_ctx->stream;
	struct dc_link *link = stream->link;
	enum dc_color_depth display_color_depth;
	enum engine_id eng_id;
	struct ext_hdmi_settings settings = {0};
	bool is_over_340mhz = false;
	bool is_vga_mode = (stream->timing.h_addressable == 640)
			&& (stream->timing.v_addressable == 480);

	if (stream->phy_pix_clk == 0)
		stream->phy_pix_clk = stream->timing.pix_clk_100hz / 10;
	if (stream->phy_pix_clk > 340000)
		is_over_340mhz = true;

	if (dc_is_hdmi_signal(pipe_ctx->stream->signal)) {
		unsigned short masked_chip_caps = pipe_ctx->stream->link->chip_caps &
				EXT_DISPLAY_PATH_CAPS__EXT_CHIP_MASK;
		if (masked_chip_caps == EXT_DISPLAY_PATH_CAPS__HDMI20_TISN65DP159RSBT) {
			/* DP159, Retimer settings */
			eng_id = pipe_ctx->stream_res.stream_enc->id;

			if (get_ext_hdmi_settings(pipe_ctx, eng_id, &settings)) {
				write_i2c_retimer_setting(pipe_ctx,
						is_vga_mode, is_over_340mhz, &settings);
			} else {
				write_i2c_default_retimer_setting(pipe_ctx,
						is_vga_mode, is_over_340mhz);
			}
		} else if (masked_chip_caps == EXT_DISPLAY_PATH_CAPS__HDMI20_PI3EQX1204) {
			/* PI3EQX1204, Redriver settings */
			write_i2c_redriver_setting(pipe_ctx, is_over_340mhz);
		}
	}

	if (dc_is_hdmi_signal(pipe_ctx->stream->signal))
		dal_ddc_service_write_scdc_data(
			stream->link->ddc,
			stream->phy_pix_clk,
			stream->timing.flags.LTE_340MCSC_SCRAMBLE);

	memset(&stream->link->cur_link_settings, 0,
			sizeof(struct dc_link_settings));

	display_color_depth = stream->timing.display_color_depth;
	if (stream->timing.pixel_encoding == PIXEL_ENCODING_YCBCR422)
		display_color_depth = COLOR_DEPTH_888;

	link->link_enc->funcs->enable_tmds_output(
			link->link_enc,
			pipe_ctx->clock_source->id,
			display_color_depth,
			pipe_ctx->stream->signal,
			stream->phy_pix_clk);

	if (dc_is_hdmi_signal(pipe_ctx->stream->signal))
		dal_ddc_service_read_scdc_data(link->ddc);
}