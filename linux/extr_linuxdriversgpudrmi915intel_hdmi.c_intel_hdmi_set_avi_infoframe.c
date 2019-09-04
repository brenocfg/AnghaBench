#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int /*<<< orphan*/  colorspace; } ;
union hdmi_infoframe {TYPE_6__ avi; } ;
struct intel_hdmi {int /*<<< orphan*/  rgb_quant_range_selectable; TYPE_2__* attached_connector; } ;
struct drm_display_mode {int dummy; } ;
struct TYPE_9__ {struct drm_display_mode adjusted_mode; } ;
struct intel_crtc_state {scalar_t__ limited_color_range; scalar_t__ ycbcr420; TYPE_1__ base; } ;
struct drm_encoder {int dummy; } ;
struct drm_connector_state {int dummy; } ;
struct TYPE_11__ {int supported; } ;
struct TYPE_12__ {TYPE_3__ scdc; } ;
struct TYPE_13__ {TYPE_4__ hdmi; } ;
struct drm_connector {TYPE_5__ display_info; } ;
struct TYPE_10__ {struct drm_connector base; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int /*<<< orphan*/  HDMI_COLORSPACE_RGB ; 
 int /*<<< orphan*/  HDMI_COLORSPACE_YUV420 ; 
 int /*<<< orphan*/  HDMI_QUANTIZATION_RANGE_FULL ; 
 int /*<<< orphan*/  HDMI_QUANTIZATION_RANGE_LIMITED ; 
 int /*<<< orphan*/  drm_hdmi_avi_infoframe_content_type (TYPE_6__*,struct drm_connector_state const*) ; 
 int drm_hdmi_avi_infoframe_from_display_mode (TYPE_6__*,struct drm_display_mode const*,int) ; 
 int /*<<< orphan*/  drm_hdmi_avi_infoframe_quant_range (TYPE_6__*,struct drm_display_mode const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct intel_hdmi* enc_to_intel_hdmi (struct drm_encoder*) ; 
 int /*<<< orphan*/  intel_write_infoframe (struct drm_encoder*,struct intel_crtc_state const*,union hdmi_infoframe*) ; 

__attribute__((used)) static void intel_hdmi_set_avi_infoframe(struct drm_encoder *encoder,
					 const struct intel_crtc_state *crtc_state,
					 const struct drm_connector_state *conn_state)
{
	struct intel_hdmi *intel_hdmi = enc_to_intel_hdmi(encoder);
	const struct drm_display_mode *adjusted_mode =
		&crtc_state->base.adjusted_mode;
	struct drm_connector *connector = &intel_hdmi->attached_connector->base;
	bool is_hdmi2_sink = connector->display_info.hdmi.scdc.supported;
	union hdmi_infoframe frame;
	int ret;

	ret = drm_hdmi_avi_infoframe_from_display_mode(&frame.avi,
						       adjusted_mode,
						       is_hdmi2_sink);
	if (ret < 0) {
		DRM_ERROR("couldn't fill AVI infoframe\n");
		return;
	}

	if (crtc_state->ycbcr420)
		frame.avi.colorspace = HDMI_COLORSPACE_YUV420;
	else
		frame.avi.colorspace = HDMI_COLORSPACE_RGB;

	drm_hdmi_avi_infoframe_quant_range(&frame.avi, adjusted_mode,
					   crtc_state->limited_color_range ?
					   HDMI_QUANTIZATION_RANGE_LIMITED :
					   HDMI_QUANTIZATION_RANGE_FULL,
					   intel_hdmi->rgb_quant_range_selectable,
					   is_hdmi2_sink);

	drm_hdmi_avi_infoframe_content_type(&frame.avi,
					    conn_state);

	/* TODO: handle pixel repetition for YCBCR420 outputs */
	intel_write_infoframe(encoder, crtc_state, &frame);
}