#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ IS_YCBCR_CAPABLE; } ;
struct TYPE_8__ {TYPE_2__ bits; } ;
struct TYPE_9__ {TYPE_3__ flags; } ;
struct TYPE_10__ {TYPE_4__ features; } ;
struct dcn10_link_encoder {TYPE_5__ base; } ;
struct TYPE_6__ {scalar_t__ Y_ONLY; } ;
struct dc_crtc_timing {scalar_t__ pixel_encoding; scalar_t__ display_color_depth; TYPE_1__ flags; } ;

/* Variables and functions */
 scalar_t__ COLOR_DEPTH_666 ; 
 scalar_t__ PIXEL_ENCODING_RGB ; 

bool dcn10_link_encoder_validate_dp_output(
	const struct dcn10_link_encoder *enc10,
	const struct dc_crtc_timing *crtc_timing)
{
	/* default RGB only */
	if (crtc_timing->pixel_encoding == PIXEL_ENCODING_RGB)
		return true;

	if (enc10->base.features.flags.bits.IS_YCBCR_CAPABLE)
		return true;

	/* for DCE 8.x or later DP Y-only feature,
	 * we need ASIC cap + FeatureSupportDPYonly, not support 666
	 */
	if (crtc_timing->flags.Y_ONLY &&
		enc10->base.features.flags.bits.IS_YCBCR_CAPABLE &&
		crtc_timing->display_color_depth != COLOR_DEPTH_666)
		return true;

	return false;
}