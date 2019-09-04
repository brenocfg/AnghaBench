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
typedef  int uint32_t ;
struct intel_crtc {TYPE_1__* config; } ;
struct drm_i915_private {int dummy; } ;
typedef  int /*<<< orphan*/  i915_reg_t ;
typedef  enum pipe { ____Placeholder_pipe } pipe ;
struct TYPE_2__ {int /*<<< orphan*/  shared_dpll; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ HAS_PCH_CPT (struct drm_i915_private*) ; 
 scalar_t__ HAS_PCH_IBX (struct drm_i915_private*) ; 
 int I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  INTEL_OUTPUT_HDMI ; 
 int /*<<< orphan*/  INTEL_OUTPUT_SDVO ; 
 int /*<<< orphan*/  PCH_TRANSCONF (int) ; 
 int /*<<< orphan*/  PIPECONF (int) ; 
 int PIPECONF_8BPC ; 
 int PIPECONF_BPC_MASK ; 
 int PIPECONF_INTERLACED_ILK ; 
 int PIPECONF_INTERLACE_MASK ; 
 int /*<<< orphan*/  TRANS_CHICKEN2 (int) ; 
 int TRANS_CHICKEN2_TIMING_OVERRIDE ; 
 int TRANS_ENABLE ; 
 int TRANS_INTERLACED ; 
 int TRANS_INTERLACE_MASK ; 
 int TRANS_LEGACY_INTERLACED_ILK ; 
 int TRANS_PROGRESSIVE ; 
 int /*<<< orphan*/  TRANS_STATE_ENABLE ; 
 int /*<<< orphan*/  assert_fdi_rx_enabled (struct drm_i915_private*,int) ; 
 int /*<<< orphan*/  assert_fdi_tx_enabled (struct drm_i915_private*,int) ; 
 int /*<<< orphan*/  assert_shared_dpll_enabled (struct drm_i915_private*,int /*<<< orphan*/ ) ; 
 scalar_t__ intel_crtc_has_type (TYPE_1__*,int /*<<< orphan*/ ) ; 
 struct intel_crtc* intel_get_crtc_for_pipe (struct drm_i915_private*,int) ; 
 scalar_t__ intel_wait_for_register (struct drm_i915_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pipe_name (int) ; 

__attribute__((used)) static void ironlake_enable_pch_transcoder(struct drm_i915_private *dev_priv,
					   enum pipe pipe)
{
	struct intel_crtc *intel_crtc = intel_get_crtc_for_pipe(dev_priv,
								pipe);
	i915_reg_t reg;
	uint32_t val, pipeconf_val;

	/* Make sure PCH DPLL is enabled */
	assert_shared_dpll_enabled(dev_priv, intel_crtc->config->shared_dpll);

	/* FDI must be feeding us bits for PCH ports */
	assert_fdi_tx_enabled(dev_priv, pipe);
	assert_fdi_rx_enabled(dev_priv, pipe);

	if (HAS_PCH_CPT(dev_priv)) {
		/* Workaround: Set the timing override bit before enabling the
		 * pch transcoder. */
		reg = TRANS_CHICKEN2(pipe);
		val = I915_READ(reg);
		val |= TRANS_CHICKEN2_TIMING_OVERRIDE;
		I915_WRITE(reg, val);
	}

	reg = PCH_TRANSCONF(pipe);
	val = I915_READ(reg);
	pipeconf_val = I915_READ(PIPECONF(pipe));

	if (HAS_PCH_IBX(dev_priv)) {
		/*
		 * Make the BPC in transcoder be consistent with
		 * that in pipeconf reg. For HDMI we must use 8bpc
		 * here for both 8bpc and 12bpc.
		 */
		val &= ~PIPECONF_BPC_MASK;
		if (intel_crtc_has_type(intel_crtc->config, INTEL_OUTPUT_HDMI))
			val |= PIPECONF_8BPC;
		else
			val |= pipeconf_val & PIPECONF_BPC_MASK;
	}

	val &= ~TRANS_INTERLACE_MASK;
	if ((pipeconf_val & PIPECONF_INTERLACE_MASK) == PIPECONF_INTERLACED_ILK)
		if (HAS_PCH_IBX(dev_priv) &&
		    intel_crtc_has_type(intel_crtc->config, INTEL_OUTPUT_SDVO))
			val |= TRANS_LEGACY_INTERLACED_ILK;
		else
			val |= TRANS_INTERLACED;
	else
		val |= TRANS_PROGRESSIVE;

	I915_WRITE(reg, val | TRANS_ENABLE);
	if (intel_wait_for_register(dev_priv,
				    reg, TRANS_STATE_ENABLE, TRANS_STATE_ENABLE,
				    100))
		DRM_ERROR("failed to enable transcoder %c\n", pipe_name(pipe));
}