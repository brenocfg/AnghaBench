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
typedef  int /*<<< orphan*/  u32 ;
struct intel_sdvo {int /*<<< orphan*/  attached_output; int /*<<< orphan*/  sdvo_reg; } ;
struct TYPE_3__ {struct drm_device* dev; } ;
struct intel_encoder {TYPE_1__ base; } ;
struct TYPE_4__ {int /*<<< orphan*/  crtc; } ;
struct intel_crtc_state {scalar_t__ has_audio; TYPE_2__ base; } ;
struct intel_crtc {int /*<<< orphan*/  pipe; } ;
struct drm_i915_private {int dummy; } ;
struct drm_device {int dummy; } ;
struct drm_connector_state {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DRM_MODE_DPMS_ON ; 
 int /*<<< orphan*/  I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SDVO_ENABLE ; 
 int /*<<< orphan*/  SDVO_NAME (struct intel_sdvo*) ; 
 int /*<<< orphan*/  intel_sdvo_enable_audio (struct intel_sdvo*,struct intel_crtc_state const*,struct drm_connector_state const*) ; 
 int intel_sdvo_get_trained_inputs (struct intel_sdvo*,int*,int*) ; 
 int /*<<< orphan*/  intel_sdvo_set_active_outputs (struct intel_sdvo*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_sdvo_set_encoder_power_state (struct intel_sdvo*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_sdvo_write_sdvox (struct intel_sdvo*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_wait_for_vblank (struct drm_i915_private*,int /*<<< orphan*/ ) ; 
 struct drm_i915_private* to_i915 (struct drm_device*) ; 
 struct intel_crtc* to_intel_crtc (int /*<<< orphan*/ ) ; 
 struct intel_sdvo* to_sdvo (struct intel_encoder*) ; 

__attribute__((used)) static void intel_enable_sdvo(struct intel_encoder *encoder,
			      const struct intel_crtc_state *pipe_config,
			      const struct drm_connector_state *conn_state)
{
	struct drm_device *dev = encoder->base.dev;
	struct drm_i915_private *dev_priv = to_i915(dev);
	struct intel_sdvo *intel_sdvo = to_sdvo(encoder);
	struct intel_crtc *intel_crtc = to_intel_crtc(pipe_config->base.crtc);
	u32 temp;
	bool input1, input2;
	int i;
	bool success;

	temp = I915_READ(intel_sdvo->sdvo_reg);
	temp |= SDVO_ENABLE;
	intel_sdvo_write_sdvox(intel_sdvo, temp);

	for (i = 0; i < 2; i++)
		intel_wait_for_vblank(dev_priv, intel_crtc->pipe);

	success = intel_sdvo_get_trained_inputs(intel_sdvo, &input1, &input2);
	/*
	 * Warn if the device reported failure to sync.
	 *
	 * A lot of SDVO devices fail to notify of sync, but it's
	 * a given it the status is a success, we succeeded.
	 */
	if (success && !input1) {
		DRM_DEBUG_KMS("First %s output reported failure to "
				"sync\n", SDVO_NAME(intel_sdvo));
	}

	if (0)
		intel_sdvo_set_encoder_power_state(intel_sdvo,
						   DRM_MODE_DPMS_ON);
	intel_sdvo_set_active_outputs(intel_sdvo, intel_sdvo->attached_output);

	if (pipe_config->has_audio)
		intel_sdvo_enable_audio(intel_sdvo, pipe_config, conn_state);
}