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
struct drm_display_mode {int dummy; } ;
typedef  enum hdmi_quantization_range { ____Placeholder_hdmi_quantization_range } hdmi_quantization_range ;

/* Variables and functions */
 int HDMI_QUANTIZATION_RANGE_FULL ; 
 int HDMI_QUANTIZATION_RANGE_LIMITED ; 
 int drm_match_cea_mode (struct drm_display_mode const*) ; 

enum hdmi_quantization_range
drm_default_rgb_quant_range(const struct drm_display_mode *mode)
{
	/* All CEA modes other than VIC 1 use limited quantization range. */
	return drm_match_cea_mode(mode) > 1 ?
		HDMI_QUANTIZATION_RANGE_LIMITED :
		HDMI_QUANTIZATION_RANGE_FULL;
}