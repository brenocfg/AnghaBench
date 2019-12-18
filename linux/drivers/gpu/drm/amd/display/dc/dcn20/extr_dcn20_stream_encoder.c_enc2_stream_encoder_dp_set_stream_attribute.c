#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct stream_encoder {int dummy; } ;
struct dcn10_stream_encoder {int dummy; } ;
struct dc_crtc_timing {int dummy; } ;
typedef  enum dc_color_space { ____Placeholder_dc_color_space } dc_color_space ;

/* Variables and functions */
 struct dcn10_stream_encoder* DCN10STRENC_FROM_STRENC (struct stream_encoder*) ; 
 int /*<<< orphan*/  DP_SEC_FRAMING4 ; 
 int /*<<< orphan*/  DP_SST_SDP_SPLITTING ; 
 int /*<<< orphan*/  REG_UPDATE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enc1_stream_encoder_dp_set_stream_attribute (struct stream_encoder*,struct dc_crtc_timing*,int,int /*<<< orphan*/ ) ; 

void enc2_stream_encoder_dp_set_stream_attribute(
	struct stream_encoder *enc,
	struct dc_crtc_timing *crtc_timing,
	enum dc_color_space output_color_space,
	uint32_t enable_sdp_splitting)
{
	struct dcn10_stream_encoder *enc1 = DCN10STRENC_FROM_STRENC(enc);

	enc1_stream_encoder_dp_set_stream_attribute(enc, crtc_timing, output_color_space, enable_sdp_splitting);

	REG_UPDATE(DP_SEC_FRAMING4,
		DP_SST_SDP_SPLITTING, enable_sdp_splitting);
}