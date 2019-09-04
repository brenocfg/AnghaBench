#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u32 ;
struct intel_crtc_state {int /*<<< orphan*/  shared_dpll; } ;
struct drm_i915_private {int dummy; } ;
typedef  enum port { ____Placeholder_port } port ;
typedef  enum intel_dpll_id { ____Placeholder_intel_dpll_id } intel_dpll_id ;

/* Variables and functions */
 int DPCLKA_CFGCR0_DDI_CLK_SEL_MASK (int) ; 
 int DPCLKA_CFGCR0_DDI_CLK_SEL_SHIFT (int) ; 
 int /*<<< orphan*/  DPCLKA_CFGCR0_ICL ; 
 int DPLL_ID_ICL_DPLL0 ; 
 int DPLL_ID_ICL_DPLL1 ; 
 int DPLL_ID_ICL_MGPLL1 ; 
 int DPLL_ID_ICL_MGPLL2 ; 
 int DPLL_ID_ICL_MGPLL3 ; 
 int DPLL_ID_ICL_MGPLL4 ; 
 int I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MISSING_CASE (int) ; 
#define  PORT_A 133 
#define  PORT_B 132 
#define  PORT_C 131 
#define  PORT_D 130 
#define  PORT_E 129 
#define  PORT_F 128 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  intel_get_shared_dpll_by_id (struct drm_i915_private*,int) ; 

__attribute__((used)) static void icelake_get_ddi_pll(struct drm_i915_private *dev_priv,
				enum port port,
				struct intel_crtc_state *pipe_config)
{
	enum intel_dpll_id id;
	u32 temp;

	/* TODO: TBT pll not implemented. */
	switch (port) {
	case PORT_A:
	case PORT_B:
		temp = I915_READ(DPCLKA_CFGCR0_ICL) &
		       DPCLKA_CFGCR0_DDI_CLK_SEL_MASK(port);
		id = temp >> DPCLKA_CFGCR0_DDI_CLK_SEL_SHIFT(port);

		if (WARN_ON(id != DPLL_ID_ICL_DPLL0 && id != DPLL_ID_ICL_DPLL1))
			return;
		break;
	case PORT_C:
		id = DPLL_ID_ICL_MGPLL1;
		break;
	case PORT_D:
		id = DPLL_ID_ICL_MGPLL2;
		break;
	case PORT_E:
		id = DPLL_ID_ICL_MGPLL3;
		break;
	case PORT_F:
		id = DPLL_ID_ICL_MGPLL4;
		break;
	default:
		MISSING_CASE(port);
		return;
	}

	pipe_config->shared_dpll = intel_get_shared_dpll_by_id(dev_priv, id);
}