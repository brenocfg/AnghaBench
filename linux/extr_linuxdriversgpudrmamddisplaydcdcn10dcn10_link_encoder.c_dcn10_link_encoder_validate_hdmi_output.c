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
struct TYPE_8__ {int /*<<< orphan*/  HDMI_6GB_EN; } ;
struct TYPE_9__ {TYPE_1__ bits; } ;
struct TYPE_10__ {int max_hdmi_deep_color; int max_hdmi_pixel_clock; TYPE_2__ flags; int /*<<< orphan*/  ycbcr420_supported; } ;
struct TYPE_14__ {TYPE_6__* ctx; TYPE_3__ features; } ;
struct dcn10_link_encoder {TYPE_7__ base; } ;
struct dc_crtc_timing {int display_color_depth; scalar_t__ pixel_encoding; } ;
typedef  enum dc_color_depth { ____Placeholder_dc_color_depth } dc_color_depth ;
struct TYPE_13__ {TYPE_5__* dc; } ;
struct TYPE_11__ {scalar_t__ hdmi20_disable; } ;
struct TYPE_12__ {TYPE_4__ debug; } ;

/* Variables and functions */
 scalar_t__ COLOR_DEPTH_888 ; 
 scalar_t__ PIXEL_ENCODING_YCBCR420 ; 
 int TMDS_MIN_PIXEL_CLOCK ; 

__attribute__((used)) static bool dcn10_link_encoder_validate_hdmi_output(
	const struct dcn10_link_encoder *enc10,
	const struct dc_crtc_timing *crtc_timing,
	int adjusted_pix_clk_khz)
{
	enum dc_color_depth max_deep_color =
			enc10->base.features.max_hdmi_deep_color;

	if (max_deep_color < crtc_timing->display_color_depth)
		return false;

	if (crtc_timing->display_color_depth < COLOR_DEPTH_888)
		return false;
	if (adjusted_pix_clk_khz < TMDS_MIN_PIXEL_CLOCK)
		return false;

	if ((adjusted_pix_clk_khz == 0) ||
		(adjusted_pix_clk_khz > enc10->base.features.max_hdmi_pixel_clock))
		return false;

	/* DCE11 HW does not support 420 */
	if (!enc10->base.features.ycbcr420_supported &&
			crtc_timing->pixel_encoding == PIXEL_ENCODING_YCBCR420)
		return false;

	if (!enc10->base.features.flags.bits.HDMI_6GB_EN &&
		adjusted_pix_clk_khz >= 300000)
		return false;
	if (enc10->base.ctx->dc->debug.hdmi20_disable &&
		crtc_timing->pixel_encoding == PIXEL_ENCODING_YCBCR420)
		return false;
	return true;
}