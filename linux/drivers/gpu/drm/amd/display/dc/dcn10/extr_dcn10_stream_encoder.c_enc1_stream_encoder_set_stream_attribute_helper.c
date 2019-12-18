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
struct dcn10_stream_encoder {int dummy; } ;
struct dc_crtc_timing {int pixel_encoding; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIG_FE_CNTL ; 
#define  PIXEL_ENCODING_YCBCR422 128 
 int /*<<< orphan*/  REG_UPDATE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TMDS_COLOR_FORMAT ; 
 int /*<<< orphan*/  TMDS_PIXEL_ENCODING ; 

void enc1_stream_encoder_set_stream_attribute_helper(
		struct dcn10_stream_encoder *enc1,
		struct dc_crtc_timing *crtc_timing)
{
	switch (crtc_timing->pixel_encoding) {
	case PIXEL_ENCODING_YCBCR422:
		REG_UPDATE(DIG_FE_CNTL, TMDS_PIXEL_ENCODING, 1);
		break;
	default:
		REG_UPDATE(DIG_FE_CNTL, TMDS_PIXEL_ENCODING, 0);
		break;
	}
	REG_UPDATE(DIG_FE_CNTL, TMDS_COLOR_FORMAT, 0);
}