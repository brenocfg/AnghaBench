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
typedef  int u32 ;
struct intel_hdmi {int /*<<< orphan*/  hdmi_reg; } ;
struct TYPE_4__ {struct drm_device* dev; } ;
struct intel_encoder {TYPE_2__ base; } ;
struct intel_digital_port {int /*<<< orphan*/  (* set_infoframes ) (struct intel_encoder*,int,struct intel_crtc_state const*,struct drm_connector_state const*) ;} ;
struct TYPE_3__ {int /*<<< orphan*/  crtc; } ;
struct intel_crtc_state {TYPE_1__ base; } ;
struct intel_crtc {scalar_t__ pipe; } ;
struct drm_i915_private {int dummy; } ;
struct drm_device {int dummy; } ;
struct drm_connector_state {int dummy; } ;

/* Variables and functions */
 scalar_t__ HAS_PCH_IBX (struct drm_i915_private*) ; 
 int HDMI_AUDIO_ENABLE ; 
 int I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  PIPE_A ; 
 scalar_t__ PIPE_B ; 
 int /*<<< orphan*/  POSTING_READ (int /*<<< orphan*/ ) ; 
 int SDVO_ENABLE ; 
 int SDVO_PIPE_SEL (int /*<<< orphan*/ ) ; 
 int SDVO_PIPE_SEL_MASK ; 
 struct intel_hdmi* enc_to_intel_hdmi (TYPE_2__*) ; 
 struct intel_digital_port* hdmi_to_dig_port (struct intel_hdmi*) ; 
 int /*<<< orphan*/  intel_dp_dual_mode_set_tmds_output (struct intel_hdmi*,int) ; 
 int /*<<< orphan*/  intel_set_cpu_fifo_underrun_reporting (struct drm_i915_private*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  intel_set_pch_fifo_underrun_reporting (struct drm_i915_private*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  intel_wait_for_vblank_if_active (struct drm_i915_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct intel_encoder*,int,struct intel_crtc_state const*,struct drm_connector_state const*) ; 
 struct drm_i915_private* to_i915 (struct drm_device*) ; 
 struct intel_crtc* to_intel_crtc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void intel_disable_hdmi(struct intel_encoder *encoder,
			       const struct intel_crtc_state *old_crtc_state,
			       const struct drm_connector_state *old_conn_state)
{
	struct drm_device *dev = encoder->base.dev;
	struct drm_i915_private *dev_priv = to_i915(dev);
	struct intel_hdmi *intel_hdmi = enc_to_intel_hdmi(&encoder->base);
	struct intel_digital_port *intel_dig_port =
		hdmi_to_dig_port(intel_hdmi);
	struct intel_crtc *crtc = to_intel_crtc(old_crtc_state->base.crtc);
	u32 temp;

	temp = I915_READ(intel_hdmi->hdmi_reg);

	temp &= ~(SDVO_ENABLE | HDMI_AUDIO_ENABLE);
	I915_WRITE(intel_hdmi->hdmi_reg, temp);
	POSTING_READ(intel_hdmi->hdmi_reg);

	/*
	 * HW workaround for IBX, we need to move the port
	 * to transcoder A after disabling it to allow the
	 * matching DP port to be enabled on transcoder A.
	 */
	if (HAS_PCH_IBX(dev_priv) && crtc->pipe == PIPE_B) {
		/*
		 * We get CPU/PCH FIFO underruns on the other pipe when
		 * doing the workaround. Sweep them under the rug.
		 */
		intel_set_cpu_fifo_underrun_reporting(dev_priv, PIPE_A, false);
		intel_set_pch_fifo_underrun_reporting(dev_priv, PIPE_A, false);

		temp &= ~SDVO_PIPE_SEL_MASK;
		temp |= SDVO_ENABLE | SDVO_PIPE_SEL(PIPE_A);
		/*
		 * HW workaround, need to write this twice for issue
		 * that may result in first write getting masked.
		 */
		I915_WRITE(intel_hdmi->hdmi_reg, temp);
		POSTING_READ(intel_hdmi->hdmi_reg);
		I915_WRITE(intel_hdmi->hdmi_reg, temp);
		POSTING_READ(intel_hdmi->hdmi_reg);

		temp &= ~SDVO_ENABLE;
		I915_WRITE(intel_hdmi->hdmi_reg, temp);
		POSTING_READ(intel_hdmi->hdmi_reg);

		intel_wait_for_vblank_if_active(dev_priv, PIPE_A);
		intel_set_cpu_fifo_underrun_reporting(dev_priv, PIPE_A, true);
		intel_set_pch_fifo_underrun_reporting(dev_priv, PIPE_A, true);
	}

	intel_dig_port->set_infoframes(encoder,
				       false,
				       old_crtc_state, old_conn_state);

	intel_dp_dual_mode_set_tmds_output(intel_hdmi, false);
}