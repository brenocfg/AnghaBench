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
struct TYPE_4__ {int /*<<< orphan*/  quantization_range; } ;
union hdmi_infoframe {TYPE_2__ avi; } ;
typedef  int /*<<< orphan*/  uint8_t ;
struct intel_sdvo {scalar_t__ rgb_quant_range_selectable; } ;
struct TYPE_3__ {int /*<<< orphan*/  adjusted_mode; } ;
struct intel_crtc_state {scalar_t__ limited_color_range; TYPE_1__ base; } ;
typedef  scalar_t__ ssize_t ;
typedef  int /*<<< orphan*/  sdvo_data ;

/* Variables and functions */
 int /*<<< orphan*/  AVI ; 
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int HDMI_INFOFRAME_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HDMI_QUANTIZATION_RANGE_FULL ; 
 int /*<<< orphan*/  HDMI_QUANTIZATION_RANGE_LIMITED ; 
 int /*<<< orphan*/  SDVO_HBUF_INDEX_AVI_IF ; 
 int /*<<< orphan*/  SDVO_HBUF_TX_VSYNC ; 
 int drm_hdmi_avi_infoframe_from_display_mode (TYPE_2__*,int /*<<< orphan*/ *,int) ; 
 scalar_t__ hdmi_infoframe_pack (union hdmi_infoframe*,int /*<<< orphan*/ *,int) ; 
 int intel_sdvo_write_infoframe (struct intel_sdvo*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static bool intel_sdvo_set_avi_infoframe(struct intel_sdvo *intel_sdvo,
					 const struct intel_crtc_state *pipe_config)
{
	uint8_t sdvo_data[HDMI_INFOFRAME_SIZE(AVI)];
	union hdmi_infoframe frame;
	int ret;
	ssize_t len;

	ret = drm_hdmi_avi_infoframe_from_display_mode(&frame.avi,
						       &pipe_config->base.adjusted_mode,
						       false);
	if (ret < 0) {
		DRM_ERROR("couldn't fill AVI infoframe\n");
		return false;
	}

	if (intel_sdvo->rgb_quant_range_selectable) {
		if (pipe_config->limited_color_range)
			frame.avi.quantization_range =
				HDMI_QUANTIZATION_RANGE_LIMITED;
		else
			frame.avi.quantization_range =
				HDMI_QUANTIZATION_RANGE_FULL;
	}

	len = hdmi_infoframe_pack(&frame, sdvo_data, sizeof(sdvo_data));
	if (len < 0)
		return false;

	return intel_sdvo_write_infoframe(intel_sdvo, SDVO_HBUF_INDEX_AVI_IF,
					  SDVO_HBUF_TX_VSYNC,
					  sdvo_data, sizeof(sdvo_data));
}