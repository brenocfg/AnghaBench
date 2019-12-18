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
typedef  scalar_t__ u32 ;
struct intel_crtc_state {TYPE_1__* icl_port_dplls; } ;
struct drm_i915_private {int dummy; } ;
typedef  enum port { ____Placeholder_port } port ;
typedef  enum phy { ____Placeholder_phy } phy ;
typedef  enum intel_dpll_id { ____Placeholder_intel_dpll_id } intel_dpll_id ;
typedef  enum icl_port_dpll_id { ____Placeholder_icl_port_dpll_id } icl_port_dpll_id ;
struct TYPE_2__ {int /*<<< orphan*/  pll; } ;

/* Variables and functions */
 int /*<<< orphan*/  DDI_CLK_SEL (int) ; 
 scalar_t__ DDI_CLK_SEL_MASK ; 
 scalar_t__ DDI_CLK_SEL_MG ; 
 scalar_t__ DDI_CLK_SEL_TBT_162 ; 
 int DPLL_ID_ICL_TBTPLL ; 
 scalar_t__ I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ICL_DPCLKA_CFGCR0 ; 
 scalar_t__ ICL_DPCLKA_CFGCR0_DDI_CLK_SEL_MASK (int) ; 
 scalar_t__ ICL_DPCLKA_CFGCR0_DDI_CLK_SEL_SHIFT (int) ; 
 int ICL_PORT_DPLL_DEFAULT ; 
 int ICL_PORT_DPLL_MG_PHY ; 
 int /*<<< orphan*/  WARN (int,char*,int) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  icl_set_active_port_dpll (struct intel_crtc_state*,int) ; 
 int icl_tc_port_to_pll_id (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_get_shared_dpll_by_id (struct drm_i915_private*,int) ; 
 scalar_t__ intel_phy_is_combo (struct drm_i915_private*,int) ; 
 scalar_t__ intel_phy_is_tc (struct drm_i915_private*,int) ; 
 int intel_port_to_phy (struct drm_i915_private*,int) ; 
 int /*<<< orphan*/  intel_port_to_tc (struct drm_i915_private*,int) ; 

__attribute__((used)) static void icelake_get_ddi_pll(struct drm_i915_private *dev_priv,
				enum port port,
				struct intel_crtc_state *pipe_config)
{
	enum phy phy = intel_port_to_phy(dev_priv, port);
	enum icl_port_dpll_id port_dpll_id;
	enum intel_dpll_id id;
	u32 temp;

	if (intel_phy_is_combo(dev_priv, phy)) {
		temp = I915_READ(ICL_DPCLKA_CFGCR0) &
			ICL_DPCLKA_CFGCR0_DDI_CLK_SEL_MASK(phy);
		id = temp >> ICL_DPCLKA_CFGCR0_DDI_CLK_SEL_SHIFT(phy);
		port_dpll_id = ICL_PORT_DPLL_DEFAULT;
	} else if (intel_phy_is_tc(dev_priv, phy)) {
		u32 clk_sel = I915_READ(DDI_CLK_SEL(port)) & DDI_CLK_SEL_MASK;

		if (clk_sel == DDI_CLK_SEL_MG) {
			id = icl_tc_port_to_pll_id(intel_port_to_tc(dev_priv,
								    port));
			port_dpll_id = ICL_PORT_DPLL_MG_PHY;
		} else {
			WARN_ON(clk_sel < DDI_CLK_SEL_TBT_162);
			id = DPLL_ID_ICL_TBTPLL;
			port_dpll_id = ICL_PORT_DPLL_DEFAULT;
		}
	} else {
		WARN(1, "Invalid port %x\n", port);
		return;
	}

	pipe_config->icl_port_dplls[port_dpll_id].pll =
		intel_get_shared_dpll_by_id(dev_priv, id);

	icl_set_active_port_dpll(pipe_config, port_dpll_id);
}