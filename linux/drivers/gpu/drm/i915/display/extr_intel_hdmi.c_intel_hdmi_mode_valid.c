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
struct intel_hdmi {scalar_t__ has_hdmi_sink; } ;
struct drm_i915_private {int max_dotclk_freq; } ;
struct drm_display_mode {int flags; int clock; } ;
struct drm_device {int dummy; } ;
struct drm_connector {int /*<<< orphan*/  display_info; int /*<<< orphan*/  state; struct drm_device* dev; } ;
typedef  enum drm_mode_status { ____Placeholder_drm_mode_status } drm_mode_status ;
struct TYPE_2__ {int /*<<< orphan*/  force_audio; } ;

/* Variables and functions */
 int DRM_MODE_FLAG_3D_FRAME_PACKING ; 
 int DRM_MODE_FLAG_3D_MASK ; 
 int DRM_MODE_FLAG_DBLCLK ; 
 int DRM_MODE_FLAG_DBLSCAN ; 
 int /*<<< orphan*/  HAS_GMCH (struct drm_i915_private*) ; 
 scalar_t__ HDMI_AUDIO_OFF_DVI ; 
 int INTEL_GEN (struct drm_i915_private*) ; 
 int MODE_CLOCK_HIGH ; 
 int MODE_NO_DBLESCAN ; 
 int MODE_OK ; 
 scalar_t__ READ_ONCE (int /*<<< orphan*/ ) ; 
 scalar_t__ drm_mode_is_420_only (int /*<<< orphan*/ *,struct drm_display_mode*) ; 
 int hdmi_port_clock_valid (struct intel_hdmi*,int,int,int) ; 
 struct intel_hdmi* intel_attached_hdmi (struct drm_connector*) ; 
 struct drm_device* intel_hdmi_to_dev (struct intel_hdmi*) ; 
 struct drm_i915_private* to_i915 (struct drm_device*) ; 
 TYPE_1__* to_intel_digital_connector_state (int /*<<< orphan*/ ) ; 

__attribute__((used)) static enum drm_mode_status
intel_hdmi_mode_valid(struct drm_connector *connector,
		      struct drm_display_mode *mode)
{
	struct intel_hdmi *hdmi = intel_attached_hdmi(connector);
	struct drm_device *dev = intel_hdmi_to_dev(hdmi);
	struct drm_i915_private *dev_priv = to_i915(dev);
	enum drm_mode_status status;
	int clock;
	int max_dotclk = to_i915(connector->dev)->max_dotclk_freq;
	bool force_dvi =
		READ_ONCE(to_intel_digital_connector_state(connector->state)->force_audio) == HDMI_AUDIO_OFF_DVI;

	if (mode->flags & DRM_MODE_FLAG_DBLSCAN)
		return MODE_NO_DBLESCAN;

	clock = mode->clock;

	if ((mode->flags & DRM_MODE_FLAG_3D_MASK) == DRM_MODE_FLAG_3D_FRAME_PACKING)
		clock *= 2;

	if (clock > max_dotclk)
		return MODE_CLOCK_HIGH;

	if (mode->flags & DRM_MODE_FLAG_DBLCLK)
		clock *= 2;

	if (drm_mode_is_420_only(&connector->display_info, mode))
		clock /= 2;

	/* check if we can do 8bpc */
	status = hdmi_port_clock_valid(hdmi, clock, true, force_dvi);

	if (hdmi->has_hdmi_sink && !force_dvi) {
		/* if we can't do 8bpc we may still be able to do 12bpc */
		if (status != MODE_OK && !HAS_GMCH(dev_priv))
			status = hdmi_port_clock_valid(hdmi, clock * 3 / 2,
						       true, force_dvi);

		/* if we can't do 8,12bpc we may still be able to do 10bpc */
		if (status != MODE_OK && INTEL_GEN(dev_priv) >= 11)
			status = hdmi_port_clock_valid(hdmi, clock * 5 / 4,
						       true, force_dvi);
	}

	return status;
}