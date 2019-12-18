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
struct hdmi_avi_infoframe {int quantization_range; int /*<<< orphan*/  ycc_quantization_range; } ;
struct drm_display_mode {int dummy; } ;
struct drm_display_info {scalar_t__ rgb_quant_range_selectable; } ;
struct drm_connector {struct drm_display_info display_info; } ;
typedef  enum hdmi_quantization_range { ____Placeholder_hdmi_quantization_range } hdmi_quantization_range ;

/* Variables and functions */
 int HDMI_QUANTIZATION_RANGE_DEFAULT ; 
 int HDMI_QUANTIZATION_RANGE_LIMITED ; 
 int /*<<< orphan*/  HDMI_YCC_QUANTIZATION_RANGE_FULL ; 
 int /*<<< orphan*/  HDMI_YCC_QUANTIZATION_RANGE_LIMITED ; 
 int drm_default_rgb_quant_range (struct drm_display_mode const*) ; 
 int /*<<< orphan*/  is_hdmi2_sink (struct drm_connector*) ; 

void
drm_hdmi_avi_infoframe_quant_range(struct hdmi_avi_infoframe *frame,
				   struct drm_connector *connector,
				   const struct drm_display_mode *mode,
				   enum hdmi_quantization_range rgb_quant_range)
{
	const struct drm_display_info *info = &connector->display_info;

	/*
	 * CEA-861:
	 * "A Source shall not send a non-zero Q value that does not correspond
	 *  to the default RGB Quantization Range for the transmitted Picture
	 *  unless the Sink indicates support for the Q bit in a Video
	 *  Capabilities Data Block."
	 *
	 * HDMI 2.0 recommends sending non-zero Q when it does match the
	 * default RGB quantization range for the mode, even when QS=0.
	 */
	if (info->rgb_quant_range_selectable ||
	    rgb_quant_range == drm_default_rgb_quant_range(mode))
		frame->quantization_range = rgb_quant_range;
	else
		frame->quantization_range = HDMI_QUANTIZATION_RANGE_DEFAULT;

	/*
	 * CEA-861-F:
	 * "When transmitting any RGB colorimetry, the Source should set the
	 *  YQ-field to match the RGB Quantization Range being transmitted
	 *  (e.g., when Limited Range RGB, set YQ=0 or when Full Range RGB,
	 *  set YQ=1) and the Sink shall ignore the YQ-field."
	 *
	 * Unfortunate certain sinks (eg. VIZ Model 67/E261VA) get confused
	 * by non-zero YQ when receiving RGB. There doesn't seem to be any
	 * good way to tell which version of CEA-861 the sink supports, so
	 * we limit non-zero YQ to HDMI 2.0 sinks only as HDMI 2.0 is based
	 * on on CEA-861-F.
	 */
	if (!is_hdmi2_sink(connector) ||
	    rgb_quant_range == HDMI_QUANTIZATION_RANGE_LIMITED)
		frame->ycc_quantization_range =
			HDMI_YCC_QUANTIZATION_RANGE_LIMITED;
	else
		frame->ycc_quantization_range =
			HDMI_YCC_QUANTIZATION_RANGE_FULL;
}