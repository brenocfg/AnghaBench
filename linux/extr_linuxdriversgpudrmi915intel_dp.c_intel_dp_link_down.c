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
typedef  int uint32_t ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct intel_encoder {int port; TYPE_2__ base; } ;
struct intel_dp {int DP; int /*<<< orphan*/  active_pipe; int /*<<< orphan*/  panel_power_down_delay; int /*<<< orphan*/  output_reg; } ;
struct TYPE_3__ {int /*<<< orphan*/  crtc; } ;
struct intel_crtc_state {TYPE_1__ base; } ;
struct intel_crtc {scalar_t__ pipe; } ;
struct drm_i915_private {int dummy; } ;
typedef  enum port { ____Placeholder_port } port ;

/* Variables and functions */
 int DP_AUDIO_OUTPUT_ENABLE ; 
 int DP_LINK_TRAIN_MASK ; 
 int DP_LINK_TRAIN_MASK_CPT ; 
 int DP_LINK_TRAIN_PAT_1 ; 
 int DP_LINK_TRAIN_PAT_IDLE ; 
 int DP_LINK_TRAIN_PAT_IDLE_CPT ; 
 int DP_PIPE_SEL (int /*<<< orphan*/ ) ; 
 int DP_PIPE_SEL_MASK ; 
 int DP_PORT_EN ; 
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*) ; 
 int HAS_DDI (struct drm_i915_private*) ; 
 scalar_t__ HAS_PCH_CPT (struct drm_i915_private*) ; 
 scalar_t__ HAS_PCH_IBX (struct drm_i915_private*) ; 
 int I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  INVALID_PIPE ; 
 scalar_t__ IS_CHERRYVIEW (struct drm_i915_private*) ; 
 scalar_t__ IS_IVYBRIDGE (struct drm_i915_private*) ; 
 scalar_t__ IS_VALLEYVIEW (struct drm_i915_private*) ; 
 int /*<<< orphan*/  PIPE_A ; 
 scalar_t__ PIPE_B ; 
 int PORT_A ; 
 int /*<<< orphan*/  POSTING_READ (int /*<<< orphan*/ ) ; 
 scalar_t__ WARN_ON (int) ; 
 struct intel_dp* enc_to_intel_dp (TYPE_2__*) ; 
 int /*<<< orphan*/  intel_set_cpu_fifo_underrun_reporting (struct drm_i915_private*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  intel_set_pch_fifo_underrun_reporting (struct drm_i915_private*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  intel_wait_for_vblank_if_active (struct drm_i915_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pps_lock (struct intel_dp*) ; 
 int /*<<< orphan*/  pps_unlock (struct intel_dp*) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 
 struct intel_crtc* to_intel_crtc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
intel_dp_link_down(struct intel_encoder *encoder,
		   const struct intel_crtc_state *old_crtc_state)
{
	struct drm_i915_private *dev_priv = to_i915(encoder->base.dev);
	struct intel_dp *intel_dp = enc_to_intel_dp(&encoder->base);
	struct intel_crtc *crtc = to_intel_crtc(old_crtc_state->base.crtc);
	enum port port = encoder->port;
	uint32_t DP = intel_dp->DP;

	if (WARN_ON(HAS_DDI(dev_priv)))
		return;

	if (WARN_ON((I915_READ(intel_dp->output_reg) & DP_PORT_EN) == 0))
		return;

	DRM_DEBUG_KMS("\n");

	if ((IS_IVYBRIDGE(dev_priv) && port == PORT_A) ||
	    (HAS_PCH_CPT(dev_priv) && port != PORT_A)) {
		DP &= ~DP_LINK_TRAIN_MASK_CPT;
		DP |= DP_LINK_TRAIN_PAT_IDLE_CPT;
	} else {
		DP &= ~DP_LINK_TRAIN_MASK;
		DP |= DP_LINK_TRAIN_PAT_IDLE;
	}
	I915_WRITE(intel_dp->output_reg, DP);
	POSTING_READ(intel_dp->output_reg);

	DP &= ~(DP_PORT_EN | DP_AUDIO_OUTPUT_ENABLE);
	I915_WRITE(intel_dp->output_reg, DP);
	POSTING_READ(intel_dp->output_reg);

	/*
	 * HW workaround for IBX, we need to move the port
	 * to transcoder A after disabling it to allow the
	 * matching HDMI port to be enabled on transcoder A.
	 */
	if (HAS_PCH_IBX(dev_priv) && crtc->pipe == PIPE_B && port != PORT_A) {
		/*
		 * We get CPU/PCH FIFO underruns on the other pipe when
		 * doing the workaround. Sweep them under the rug.
		 */
		intel_set_cpu_fifo_underrun_reporting(dev_priv, PIPE_A, false);
		intel_set_pch_fifo_underrun_reporting(dev_priv, PIPE_A, false);

		/* always enable with pattern 1 (as per spec) */
		DP &= ~(DP_PIPE_SEL_MASK | DP_LINK_TRAIN_MASK);
		DP |= DP_PORT_EN | DP_PIPE_SEL(PIPE_A) |
			DP_LINK_TRAIN_PAT_1;
		I915_WRITE(intel_dp->output_reg, DP);
		POSTING_READ(intel_dp->output_reg);

		DP &= ~DP_PORT_EN;
		I915_WRITE(intel_dp->output_reg, DP);
		POSTING_READ(intel_dp->output_reg);

		intel_wait_for_vblank_if_active(dev_priv, PIPE_A);
		intel_set_cpu_fifo_underrun_reporting(dev_priv, PIPE_A, true);
		intel_set_pch_fifo_underrun_reporting(dev_priv, PIPE_A, true);
	}

	msleep(intel_dp->panel_power_down_delay);

	intel_dp->DP = DP;

	if (IS_VALLEYVIEW(dev_priv) || IS_CHERRYVIEW(dev_priv)) {
		pps_lock(intel_dp);
		intel_dp->active_pipe = INVALID_PIPE;
		pps_unlock(intel_dp);
	}
}