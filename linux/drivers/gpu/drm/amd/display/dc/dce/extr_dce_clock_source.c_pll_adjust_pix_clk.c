#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct pll_settings {int actual_pix_clk_100hz; int adjusted_pix_clk_100hz; int /*<<< orphan*/  pix_clk_post_divider; int /*<<< orphan*/  reference_divider; } ;
struct TYPE_4__ {int /*<<< orphan*/  ENABLE_SS; } ;
struct pixel_clk_params {int signal_type; int requested_pix_clk_100hz; int requested_sym_clk; TYPE_1__ flags; int /*<<< orphan*/  encoder_object_id; int /*<<< orphan*/  color_depth; int /*<<< orphan*/  pixel_encoding; } ;
struct dce110_clk_src {TYPE_3__* bios; } ;
struct bp_adjust_pixel_clock_parameters {int pixel_clock; int signal_type; int adjusted_pixel_clock; int /*<<< orphan*/  pixel_clock_post_divider; int /*<<< orphan*/  reference_divider; int /*<<< orphan*/  ss_enable; int /*<<< orphan*/  encoder_object_id; int /*<<< orphan*/  member_0; } ;
typedef  enum bp_result { ____Placeholder_bp_result } bp_result ;
struct TYPE_6__ {TYPE_2__* funcs; } ;
struct TYPE_5__ {int (* adjust_pixel_clock ) (TYPE_3__*,struct bp_adjust_pixel_clock_parameters*) ;} ;

/* Variables and functions */
 int BP_RESULT_OK ; 
#define  COLOR_DEPTH_101010 134 
#define  COLOR_DEPTH_121212 133 
#define  COLOR_DEPTH_161616 132 
 int /*<<< orphan*/  PIXEL_ENCODING_YCBCR422 ; 
#define  SIGNAL_TYPE_DISPLAY_PORT 131 
#define  SIGNAL_TYPE_DISPLAY_PORT_MST 130 
#define  SIGNAL_TYPE_EDP 129 
#define  SIGNAL_TYPE_HDMI_TYPE_A 128 
 int stub1 (TYPE_3__*,struct bp_adjust_pixel_clock_parameters*) ; 

__attribute__((used)) static bool pll_adjust_pix_clk(
		struct dce110_clk_src *clk_src,
		struct pixel_clk_params *pix_clk_params,
		struct pll_settings *pll_settings)
{
	uint32_t actual_pix_clk_100hz = 0;
	uint32_t requested_clk_100hz = 0;
	struct bp_adjust_pixel_clock_parameters bp_adjust_pixel_clock_params = {
							0 };
	enum bp_result bp_result;
	switch (pix_clk_params->signal_type) {
	case SIGNAL_TYPE_HDMI_TYPE_A: {
		requested_clk_100hz = pix_clk_params->requested_pix_clk_100hz;
		if (pix_clk_params->pixel_encoding != PIXEL_ENCODING_YCBCR422) {
			switch (pix_clk_params->color_depth) {
			case COLOR_DEPTH_101010:
				requested_clk_100hz = (requested_clk_100hz * 5) >> 2;
				break; /* x1.25*/
			case COLOR_DEPTH_121212:
				requested_clk_100hz = (requested_clk_100hz * 6) >> 2;
				break; /* x1.5*/
			case COLOR_DEPTH_161616:
				requested_clk_100hz = requested_clk_100hz * 2;
				break; /* x2.0*/
			default:
				break;
			}
		}
		actual_pix_clk_100hz = requested_clk_100hz;
	}
		break;

	case SIGNAL_TYPE_DISPLAY_PORT:
	case SIGNAL_TYPE_DISPLAY_PORT_MST:
	case SIGNAL_TYPE_EDP:
		requested_clk_100hz = pix_clk_params->requested_sym_clk * 10;
		actual_pix_clk_100hz = pix_clk_params->requested_pix_clk_100hz;
		break;

	default:
		requested_clk_100hz = pix_clk_params->requested_pix_clk_100hz;
		actual_pix_clk_100hz = pix_clk_params->requested_pix_clk_100hz;
		break;
	}

	bp_adjust_pixel_clock_params.pixel_clock = requested_clk_100hz / 10;
	bp_adjust_pixel_clock_params.
		encoder_object_id = pix_clk_params->encoder_object_id;
	bp_adjust_pixel_clock_params.signal_type = pix_clk_params->signal_type;
	bp_adjust_pixel_clock_params.
		ss_enable = pix_clk_params->flags.ENABLE_SS;
	bp_result = clk_src->bios->funcs->adjust_pixel_clock(
			clk_src->bios, &bp_adjust_pixel_clock_params);
	if (bp_result == BP_RESULT_OK) {
		pll_settings->actual_pix_clk_100hz = actual_pix_clk_100hz;
		pll_settings->adjusted_pix_clk_100hz =
			bp_adjust_pixel_clock_params.adjusted_pixel_clock * 10;
		pll_settings->reference_divider =
			bp_adjust_pixel_clock_params.reference_divider;
		pll_settings->pix_clk_post_divider =
			bp_adjust_pixel_clock_params.pixel_clock_post_divider;

		return true;
	}

	return false;
}