#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct intel_hdmi {int /*<<< orphan*/  hdmi_reg; } ;
struct TYPE_8__ {struct drm_device* dev; } ;
struct intel_encoder {TYPE_4__ base; } ;
struct TYPE_7__ {int enable; int /*<<< orphan*/  hdmi; int /*<<< orphan*/  spd; int /*<<< orphan*/  avi; } ;
struct TYPE_5__ {int flags; int crtc_clock; } ;
struct TYPE_6__ {TYPE_1__ adjusted_mode; } ;
struct intel_crtc_state {int has_hdmi_sink; int has_infoframe; int has_audio; int limited_color_range; int port_clock; int pixel_multiplier; int lane_count; TYPE_3__ infoframes; TYPE_2__ base; int /*<<< orphan*/  output_types; } ;
struct drm_i915_private {int dummy; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int /*<<< orphan*/ ) ; 
 int DRM_MODE_FLAG_NHSYNC ; 
 int DRM_MODE_FLAG_NVSYNC ; 
 int DRM_MODE_FLAG_PHSYNC ; 
 int DRM_MODE_FLAG_PVSYNC ; 
 int /*<<< orphan*/  HAS_PCH_SPLIT (struct drm_i915_private*) ; 
 int HDMI_AUDIO_ENABLE ; 
 int HDMI_COLOR_FORMAT_12bpc ; 
 int HDMI_COLOR_RANGE_16_235 ; 
 int /*<<< orphan*/  HDMI_INFOFRAME_TYPE_AVI ; 
 int /*<<< orphan*/  HDMI_INFOFRAME_TYPE_SPD ; 
 int /*<<< orphan*/  HDMI_INFOFRAME_TYPE_VENDOR ; 
 int HDMI_MODE_SELECT_HDMI ; 
 int I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INTEL_OUTPUT_HDMI ; 
 int SDVO_COLOR_FORMAT_MASK ; 
 int SDVO_HSYNC_ACTIVE_HIGH ; 
 int SDVO_VSYNC_ACTIVE_HIGH ; 
 struct intel_hdmi* enc_to_intel_hdmi (TYPE_4__*) ; 
 int intel_hdmi_infoframes_enabled (struct intel_encoder*,struct intel_crtc_state*) ; 
 int /*<<< orphan*/  intel_hdmi_read_gcp_infoframe (struct intel_encoder*,struct intel_crtc_state*) ; 
 int /*<<< orphan*/  intel_read_infoframe (struct intel_encoder*,struct intel_crtc_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct drm_i915_private* to_i915 (struct drm_device*) ; 

__attribute__((used)) static void intel_hdmi_get_config(struct intel_encoder *encoder,
				  struct intel_crtc_state *pipe_config)
{
	struct intel_hdmi *intel_hdmi = enc_to_intel_hdmi(&encoder->base);
	struct drm_device *dev = encoder->base.dev;
	struct drm_i915_private *dev_priv = to_i915(dev);
	u32 tmp, flags = 0;
	int dotclock;

	pipe_config->output_types |= BIT(INTEL_OUTPUT_HDMI);

	tmp = I915_READ(intel_hdmi->hdmi_reg);

	if (tmp & SDVO_HSYNC_ACTIVE_HIGH)
		flags |= DRM_MODE_FLAG_PHSYNC;
	else
		flags |= DRM_MODE_FLAG_NHSYNC;

	if (tmp & SDVO_VSYNC_ACTIVE_HIGH)
		flags |= DRM_MODE_FLAG_PVSYNC;
	else
		flags |= DRM_MODE_FLAG_NVSYNC;

	if (tmp & HDMI_MODE_SELECT_HDMI)
		pipe_config->has_hdmi_sink = true;

	pipe_config->infoframes.enable |=
		intel_hdmi_infoframes_enabled(encoder, pipe_config);

	if (pipe_config->infoframes.enable)
		pipe_config->has_infoframe = true;

	if (tmp & HDMI_AUDIO_ENABLE)
		pipe_config->has_audio = true;

	if (!HAS_PCH_SPLIT(dev_priv) &&
	    tmp & HDMI_COLOR_RANGE_16_235)
		pipe_config->limited_color_range = true;

	pipe_config->base.adjusted_mode.flags |= flags;

	if ((tmp & SDVO_COLOR_FORMAT_MASK) == HDMI_COLOR_FORMAT_12bpc)
		dotclock = pipe_config->port_clock * 2 / 3;
	else
		dotclock = pipe_config->port_clock;

	if (pipe_config->pixel_multiplier)
		dotclock /= pipe_config->pixel_multiplier;

	pipe_config->base.adjusted_mode.crtc_clock = dotclock;

	pipe_config->lane_count = 4;

	intel_hdmi_read_gcp_infoframe(encoder, pipe_config);

	intel_read_infoframe(encoder, pipe_config,
			     HDMI_INFOFRAME_TYPE_AVI,
			     &pipe_config->infoframes.avi);
	intel_read_infoframe(encoder, pipe_config,
			     HDMI_INFOFRAME_TYPE_SPD,
			     &pipe_config->infoframes.spd);
	intel_read_infoframe(encoder, pipe_config,
			     HDMI_INFOFRAME_TYPE_VENDOR,
			     &pipe_config->infoframes.hdmi);
}