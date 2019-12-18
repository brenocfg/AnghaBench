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
typedef  int /*<<< orphan*/  u32 ;
struct intel_hdmi {int /*<<< orphan*/  hdmi_reg; } ;
struct TYPE_2__ {struct drm_device* dev; } ;
struct intel_encoder {TYPE_1__ base; } ;
struct intel_crtc_state {scalar_t__ has_audio; } ;
struct drm_i915_private {int dummy; } ;
struct drm_device {int dummy; } ;
struct drm_connector_state {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HDMI_AUDIO_ENABLE ; 
 int /*<<< orphan*/  I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  POSTING_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SDVO_ENABLE ; 
 struct intel_hdmi* enc_to_intel_hdmi (TYPE_1__*) ; 
 int /*<<< orphan*/  intel_enable_hdmi_audio (struct intel_encoder*,struct intel_crtc_state const*,struct drm_connector_state const*) ; 
 struct drm_i915_private* to_i915 (struct drm_device*) ; 

__attribute__((used)) static void g4x_enable_hdmi(struct intel_encoder *encoder,
			    const struct intel_crtc_state *pipe_config,
			    const struct drm_connector_state *conn_state)
{
	struct drm_device *dev = encoder->base.dev;
	struct drm_i915_private *dev_priv = to_i915(dev);
	struct intel_hdmi *intel_hdmi = enc_to_intel_hdmi(&encoder->base);
	u32 temp;

	temp = I915_READ(intel_hdmi->hdmi_reg);

	temp |= SDVO_ENABLE;
	if (pipe_config->has_audio)
		temp |= HDMI_AUDIO_ENABLE;

	I915_WRITE(intel_hdmi->hdmi_reg, temp);
	POSTING_READ(intel_hdmi->hdmi_reg);

	if (pipe_config->has_audio)
		intel_enable_hdmi_audio(encoder, pipe_config, conn_state);
}