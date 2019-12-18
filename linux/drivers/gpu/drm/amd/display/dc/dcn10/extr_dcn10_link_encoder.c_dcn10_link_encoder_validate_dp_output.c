#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  dp_ycbcr420_supported; } ;
struct TYPE_4__ {TYPE_1__ features; } ;
struct dcn10_link_encoder {TYPE_2__ base; } ;
struct dc_crtc_timing {scalar_t__ pixel_encoding; } ;

/* Variables and functions */
 scalar_t__ PIXEL_ENCODING_YCBCR420 ; 

bool dcn10_link_encoder_validate_dp_output(
	const struct dcn10_link_encoder *enc10,
	const struct dc_crtc_timing *crtc_timing)
{
	if (crtc_timing->pixel_encoding == PIXEL_ENCODING_YCBCR420) {
		if (!enc10->base.features.dp_ycbcr420_supported)
			return false;
	}

	return true;
}