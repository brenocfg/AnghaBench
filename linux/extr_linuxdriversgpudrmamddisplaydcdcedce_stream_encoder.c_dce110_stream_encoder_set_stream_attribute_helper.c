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
struct dce110_stream_encoder {TYPE_1__* regs; } ;
struct dc_crtc_timing {int pixel_encoding; } ;
struct TYPE_2__ {scalar_t__ DIG_FE_CNTL; scalar_t__ TMDS_CNTL; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIG_FE_CNTL ; 
#define  PIXEL_ENCODING_YCBCR422 128 
 int /*<<< orphan*/  REG_UPDATE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TMDS_CNTL ; 
 int /*<<< orphan*/  TMDS_COLOR_FORMAT ; 
 int /*<<< orphan*/  TMDS_PIXEL_ENCODING ; 

__attribute__((used)) static void dce110_stream_encoder_set_stream_attribute_helper(
		struct dce110_stream_encoder *enc110,
		struct dc_crtc_timing *crtc_timing)
{
	if (enc110->regs->TMDS_CNTL) {
		switch (crtc_timing->pixel_encoding) {
		case PIXEL_ENCODING_YCBCR422:
			REG_UPDATE(TMDS_CNTL, TMDS_PIXEL_ENCODING, 1);
			break;
		default:
			REG_UPDATE(TMDS_CNTL, TMDS_PIXEL_ENCODING, 0);
			break;
		}
		REG_UPDATE(TMDS_CNTL, TMDS_COLOR_FORMAT, 0);
	} else if (enc110->regs->DIG_FE_CNTL) {
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

}