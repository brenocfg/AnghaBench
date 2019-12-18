#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct stream_encoder {int dummy; } ;
struct TYPE_8__ {TYPE_6__* bp; int /*<<< orphan*/  id; } ;
struct dce110_stream_encoder {TYPE_4__* se_mask; TYPE_3__* regs; TYPE_2__ base; } ;
struct TYPE_11__ {scalar_t__ LTE_340MCSC_SCRAMBLE; } ;
struct dc_crtc_timing {int display_color_depth; TYPE_5__ flags; int /*<<< orphan*/  pixel_encoding; } ;
struct bp_encoder_control {int enable_dp_audio; int pixel_clock; int /*<<< orphan*/  lanes_number; int /*<<< orphan*/  signal; int /*<<< orphan*/  engine_id; int /*<<< orphan*/  action; int /*<<< orphan*/  member_0; } ;
struct TYPE_12__ {TYPE_1__* funcs; } ;
struct TYPE_10__ {scalar_t__ HDMI_DATA_SCRAMBLE_EN; } ;
struct TYPE_9__ {scalar_t__ DIG_FE_CNTL; } ;
struct TYPE_7__ {scalar_t__ (* encoder_control ) (TYPE_6__*,struct bp_encoder_control*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  AFMT_AUDIO_INFO_UPDATE ; 
 int /*<<< orphan*/  AFMT_INFOFRAME_CONTROL0 ; 
 scalar_t__ BP_RESULT_OK ; 
#define  COLOR_DEPTH_101010 131 
#define  COLOR_DEPTH_121212 130 
#define  COLOR_DEPTH_161616 129 
#define  COLOR_DEPTH_888 128 
 struct dce110_stream_encoder* DCE110STRENC_FROM_STRENC (struct stream_encoder*) ; 
 int /*<<< orphan*/  ENCODER_CONTROL_SETUP ; 
 int /*<<< orphan*/  HDMI_AUDIO_INFO_LINE ; 
 int /*<<< orphan*/  HDMI_AUDIO_INFO_SEND ; 
 int /*<<< orphan*/  HDMI_CLOCK_CHANNEL_RATE ; 
 int HDMI_CLOCK_CHANNEL_RATE_MORE_340M ; 
 int /*<<< orphan*/  HDMI_CONTROL ; 
 int /*<<< orphan*/  HDMI_DATA_SCRAMBLE_EN ; 
 int /*<<< orphan*/  HDMI_DEEP_COLOR_DEPTH ; 
 int /*<<< orphan*/  HDMI_DEEP_COLOR_ENABLE ; 
 int /*<<< orphan*/  HDMI_GC ; 
 int /*<<< orphan*/  HDMI_GC_AVMUTE ; 
 int /*<<< orphan*/  HDMI_GC_CONT ; 
 int /*<<< orphan*/  HDMI_GC_SEND ; 
 int /*<<< orphan*/  HDMI_INFOFRAME_CONTROL0 ; 
 int /*<<< orphan*/  HDMI_INFOFRAME_CONTROL1 ; 
 int /*<<< orphan*/  HDMI_KEEPOUT_MODE ; 
 int /*<<< orphan*/  HDMI_NULL_SEND ; 
 int /*<<< orphan*/  HDMI_PACKET_GEN_VERSION ; 
 int /*<<< orphan*/  HDMI_VBI_PACKET_CONTROL ; 
 int /*<<< orphan*/  LANE_COUNT_FOUR ; 
 int /*<<< orphan*/  PIXEL_ENCODING_YCBCR422 ; 
 int /*<<< orphan*/  REG_UPDATE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  REG_UPDATE_2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  REG_UPDATE_3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  REG_UPDATE_5 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SIGNAL_TYPE_HDMI_TYPE_A ; 
 int VBI_LINE_0 ; 
 int /*<<< orphan*/  dce110_stream_encoder_set_stream_attribute_helper (struct dce110_stream_encoder*,struct dc_crtc_timing*) ; 
 scalar_t__ stub1 (TYPE_6__*,struct bp_encoder_control*) ; 

__attribute__((used)) static void dce110_stream_encoder_hdmi_set_stream_attribute(
	struct stream_encoder *enc,
	struct dc_crtc_timing *crtc_timing,
	int actual_pix_clk_khz,
	bool enable_audio)
{
	struct dce110_stream_encoder *enc110 = DCE110STRENC_FROM_STRENC(enc);
	struct bp_encoder_control cntl = {0};

	cntl.action = ENCODER_CONTROL_SETUP;
	cntl.engine_id = enc110->base.id;
	cntl.signal = SIGNAL_TYPE_HDMI_TYPE_A;
	cntl.enable_dp_audio = enable_audio;
	cntl.pixel_clock = actual_pix_clk_khz;
	cntl.lanes_number = LANE_COUNT_FOUR;

	if (enc110->base.bp->funcs->encoder_control(
			enc110->base.bp, &cntl) != BP_RESULT_OK)
		return;

	dce110_stream_encoder_set_stream_attribute_helper(enc110, crtc_timing);

	/* setup HDMI engine */
	if (!enc110->se_mask->HDMI_DATA_SCRAMBLE_EN) {
		REG_UPDATE_3(HDMI_CONTROL,
			HDMI_PACKET_GEN_VERSION, 1,
			HDMI_KEEPOUT_MODE, 1,
			HDMI_DEEP_COLOR_ENABLE, 0);
	} else if (enc110->regs->DIG_FE_CNTL) {
		REG_UPDATE_5(HDMI_CONTROL,
			HDMI_PACKET_GEN_VERSION, 1,
			HDMI_KEEPOUT_MODE, 1,
			HDMI_DEEP_COLOR_ENABLE, 0,
			HDMI_DATA_SCRAMBLE_EN, 0,
			HDMI_CLOCK_CHANNEL_RATE, 0);
	}

	switch (crtc_timing->display_color_depth) {
	case COLOR_DEPTH_888:
		REG_UPDATE(HDMI_CONTROL, HDMI_DEEP_COLOR_DEPTH, 0);
		break;
	case COLOR_DEPTH_101010:
		if (crtc_timing->pixel_encoding == PIXEL_ENCODING_YCBCR422) {
			REG_UPDATE_2(HDMI_CONTROL,
					HDMI_DEEP_COLOR_DEPTH, 1,
					HDMI_DEEP_COLOR_ENABLE, 0);
		} else {
			REG_UPDATE_2(HDMI_CONTROL,
					HDMI_DEEP_COLOR_DEPTH, 1,
					HDMI_DEEP_COLOR_ENABLE, 1);
			}
		break;
	case COLOR_DEPTH_121212:
		if (crtc_timing->pixel_encoding == PIXEL_ENCODING_YCBCR422) {
			REG_UPDATE_2(HDMI_CONTROL,
					HDMI_DEEP_COLOR_DEPTH, 2,
					HDMI_DEEP_COLOR_ENABLE, 0);
		} else {
			REG_UPDATE_2(HDMI_CONTROL,
					HDMI_DEEP_COLOR_DEPTH, 2,
					HDMI_DEEP_COLOR_ENABLE, 1);
			}
		break;
	case COLOR_DEPTH_161616:
		REG_UPDATE_2(HDMI_CONTROL,
				HDMI_DEEP_COLOR_DEPTH, 3,
				HDMI_DEEP_COLOR_ENABLE, 1);
		break;
	default:
		break;
	}

	if (enc110->se_mask->HDMI_DATA_SCRAMBLE_EN) {
		if (actual_pix_clk_khz >= HDMI_CLOCK_CHANNEL_RATE_MORE_340M) {
			/* enable HDMI data scrambler
			 * HDMI_CLOCK_CHANNEL_RATE_MORE_340M
			 * Clock channel frequency is 1/4 of character rate.
			 */
			REG_UPDATE_2(HDMI_CONTROL,
				HDMI_DATA_SCRAMBLE_EN, 1,
				HDMI_CLOCK_CHANNEL_RATE, 1);
		} else if (crtc_timing->flags.LTE_340MCSC_SCRAMBLE) {

			/* TODO: New feature for DCE11, still need to implement */

			/* enable HDMI data scrambler
			 * HDMI_CLOCK_CHANNEL_FREQ_EQUAL_TO_CHAR_RATE
			 * Clock channel frequency is the same
			 * as character rate
			 */
			REG_UPDATE_2(HDMI_CONTROL,
				HDMI_DATA_SCRAMBLE_EN, 1,
				HDMI_CLOCK_CHANNEL_RATE, 0);
		}
	}

	REG_UPDATE_3(HDMI_VBI_PACKET_CONTROL,
		HDMI_GC_CONT, 1,
		HDMI_GC_SEND, 1,
		HDMI_NULL_SEND, 1);

	/* following belongs to audio */
	REG_UPDATE(HDMI_INFOFRAME_CONTROL0, HDMI_AUDIO_INFO_SEND, 1);

	REG_UPDATE(AFMT_INFOFRAME_CONTROL0, AFMT_AUDIO_INFO_UPDATE, 1);

	REG_UPDATE(HDMI_INFOFRAME_CONTROL1, HDMI_AUDIO_INFO_LINE,
				VBI_LINE_0 + 2);

	REG_UPDATE(HDMI_GC, HDMI_GC_AVMUTE, 0);

}