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
union hdmi_infoframe {int /*<<< orphan*/  avi; } ;
struct vc4_hdmi_encoder {int /*<<< orphan*/  rgb_range_selectable; scalar_t__ limited_rgb_range; } ;
struct drm_encoder {struct drm_crtc* crtc; } ;
struct drm_display_mode {int dummy; } ;
struct drm_crtc {TYPE_1__* state; } ;
struct TYPE_2__ {struct drm_display_mode adjusted_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int /*<<< orphan*/  HDMI_QUANTIZATION_RANGE_FULL ; 
 int /*<<< orphan*/  HDMI_QUANTIZATION_RANGE_LIMITED ; 
 int drm_hdmi_avi_infoframe_from_display_mode (int /*<<< orphan*/ *,struct drm_display_mode const*,int) ; 
 int /*<<< orphan*/  drm_hdmi_avi_infoframe_quant_range (int /*<<< orphan*/ *,struct drm_display_mode const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct vc4_hdmi_encoder* to_vc4_hdmi_encoder (struct drm_encoder*) ; 
 int /*<<< orphan*/  vc4_hdmi_write_infoframe (struct drm_encoder*,union hdmi_infoframe*) ; 

__attribute__((used)) static void vc4_hdmi_set_avi_infoframe(struct drm_encoder *encoder)
{
	struct vc4_hdmi_encoder *vc4_encoder = to_vc4_hdmi_encoder(encoder);
	struct drm_crtc *crtc = encoder->crtc;
	const struct drm_display_mode *mode = &crtc->state->adjusted_mode;
	union hdmi_infoframe frame;
	int ret;

	ret = drm_hdmi_avi_infoframe_from_display_mode(&frame.avi, mode, false);
	if (ret < 0) {
		DRM_ERROR("couldn't fill AVI infoframe\n");
		return;
	}

	drm_hdmi_avi_infoframe_quant_range(&frame.avi, mode,
					   vc4_encoder->limited_rgb_range ?
					   HDMI_QUANTIZATION_RANGE_LIMITED :
					   HDMI_QUANTIZATION_RANGE_FULL,
					   vc4_encoder->rgb_range_selectable,
					   false);

	vc4_hdmi_write_infoframe(encoder, &frame);
}