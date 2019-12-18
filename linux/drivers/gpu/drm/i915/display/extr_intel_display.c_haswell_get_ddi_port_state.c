#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct intel_shared_dpll {TYPE_3__* info; } ;
struct intel_crtc_state {int has_pch_encoder; int fdi_lanes; int /*<<< orphan*/  dpll_hw_state; struct intel_shared_dpll* shared_dpll; int /*<<< orphan*/  cpu_transcoder; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct intel_crtc {TYPE_1__ base; } ;
struct drm_i915_private {int dummy; } ;
typedef  enum port { ____Placeholder_port } port ;
struct TYPE_6__ {TYPE_2__* funcs; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* get_hw_state ) (struct drm_i915_private*,struct intel_shared_dpll*,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int FDI_DP_PORT_WIDTH_MASK ; 
 int FDI_DP_PORT_WIDTH_SHIFT ; 
 int /*<<< orphan*/  FDI_RX_CTL (int /*<<< orphan*/ ) ; 
 int I915_READ (int /*<<< orphan*/ ) ; 
 int INTEL_GEN (struct drm_i915_private*) ; 
 scalar_t__ IS_CANNONLAKE (struct drm_i915_private*) ; 
 scalar_t__ IS_GEN9_BC (struct drm_i915_private*) ; 
 scalar_t__ IS_GEN9_LP (struct drm_i915_private*) ; 
 int /*<<< orphan*/  LPT_TRANSCONF ; 
 int /*<<< orphan*/  PIPE_A ; 
 int PORT_E ; 
 int TGL_TRANS_DDI_FUNC_CTL_VAL_TO_PORT (int) ; 
 int /*<<< orphan*/  TRANS_DDI_FUNC_CTL (int /*<<< orphan*/ ) ; 
 int TRANS_DDI_FUNC_CTL_VAL_TO_PORT (int) ; 
 int TRANS_ENABLE ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  bxt_get_ddi_pll (struct drm_i915_private*,int,struct intel_crtc_state*) ; 
 int /*<<< orphan*/  cannonlake_get_ddi_pll (struct drm_i915_private*,int,struct intel_crtc_state*) ; 
 int /*<<< orphan*/  haswell_get_ddi_pll (struct drm_i915_private*,int,struct intel_crtc_state*) ; 
 int /*<<< orphan*/  icelake_get_ddi_pll (struct drm_i915_private*,int,struct intel_crtc_state*) ; 
 int /*<<< orphan*/  ironlake_get_fdi_m_n_config (struct intel_crtc*,struct intel_crtc_state*) ; 
 int /*<<< orphan*/  skylake_get_ddi_pll (struct drm_i915_private*,int,struct intel_crtc_state*) ; 
 int /*<<< orphan*/  stub1 (struct drm_i915_private*,struct intel_shared_dpll*,int /*<<< orphan*/ *) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void haswell_get_ddi_port_state(struct intel_crtc *crtc,
				       struct intel_crtc_state *pipe_config)
{
	struct drm_i915_private *dev_priv = to_i915(crtc->base.dev);
	struct intel_shared_dpll *pll;
	enum port port;
	u32 tmp;

	tmp = I915_READ(TRANS_DDI_FUNC_CTL(pipe_config->cpu_transcoder));

	if (INTEL_GEN(dev_priv) >= 12)
		port = TGL_TRANS_DDI_FUNC_CTL_VAL_TO_PORT(tmp);
	else
		port = TRANS_DDI_FUNC_CTL_VAL_TO_PORT(tmp);

	if (INTEL_GEN(dev_priv) >= 11)
		icelake_get_ddi_pll(dev_priv, port, pipe_config);
	else if (IS_CANNONLAKE(dev_priv))
		cannonlake_get_ddi_pll(dev_priv, port, pipe_config);
	else if (IS_GEN9_BC(dev_priv))
		skylake_get_ddi_pll(dev_priv, port, pipe_config);
	else if (IS_GEN9_LP(dev_priv))
		bxt_get_ddi_pll(dev_priv, port, pipe_config);
	else
		haswell_get_ddi_pll(dev_priv, port, pipe_config);

	pll = pipe_config->shared_dpll;
	if (pll) {
		WARN_ON(!pll->info->funcs->get_hw_state(dev_priv, pll,
						&pipe_config->dpll_hw_state));
	}

	/*
	 * Haswell has only FDI/PCH transcoder A. It is which is connected to
	 * DDI E. So just check whether this pipe is wired to DDI E and whether
	 * the PCH transcoder is on.
	 */
	if (INTEL_GEN(dev_priv) < 9 &&
	    (port == PORT_E) && I915_READ(LPT_TRANSCONF) & TRANS_ENABLE) {
		pipe_config->has_pch_encoder = true;

		tmp = I915_READ(FDI_RX_CTL(PIPE_A));
		pipe_config->fdi_lanes = ((FDI_DP_PORT_WIDTH_MASK & tmp) >>
					  FDI_DP_PORT_WIDTH_SHIFT) + 1;

		ironlake_get_fdi_m_n_config(crtc, pipe_config);
	}
}