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
 int DPLL_ID_LCPLL_1350 ; 
 int DPLL_ID_LCPLL_2700 ; 
 int DPLL_ID_LCPLL_810 ; 
 int DPLL_ID_SPLL ; 
 int DPLL_ID_WRPLL1 ; 
 int DPLL_ID_WRPLL2 ; 
 int I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MISSING_CASE (int) ; 
 int /*<<< orphan*/  PORT_CLK_SEL (int) ; 
#define  PORT_CLK_SEL_LCPLL_1350 134 
#define  PORT_CLK_SEL_LCPLL_2700 133 
#define  PORT_CLK_SEL_LCPLL_810 132 
#define  PORT_CLK_SEL_NONE 131 
#define  PORT_CLK_SEL_SPLL 130 
#define  PORT_CLK_SEL_WRPLL1 129 
#define  PORT_CLK_SEL_WRPLL2 128 
 int /*<<< orphan*/  intel_get_shared_dpll_by_id (struct drm_i915_private*,int) ; 

__attribute__((used)) static void haswell_get_ddi_pll(struct drm_i915_private *dev_priv,
				enum port port,
				struct intel_crtc_state *pipe_config)
{
	enum intel_dpll_id id;
	u32 ddi_pll_sel = I915_READ(PORT_CLK_SEL(port));

	switch (ddi_pll_sel) {
	case PORT_CLK_SEL_WRPLL1:
		id = DPLL_ID_WRPLL1;
		break;
	case PORT_CLK_SEL_WRPLL2:
		id = DPLL_ID_WRPLL2;
		break;
	case PORT_CLK_SEL_SPLL:
		id = DPLL_ID_SPLL;
		break;
	case PORT_CLK_SEL_LCPLL_810:
		id = DPLL_ID_LCPLL_810;
		break;
	case PORT_CLK_SEL_LCPLL_1350:
		id = DPLL_ID_LCPLL_1350;
		break;
	case PORT_CLK_SEL_LCPLL_2700:
		id = DPLL_ID_LCPLL_2700;
		break;
	default:
		MISSING_CASE(ddi_pll_sel);
		/* fall through */
	case PORT_CLK_SEL_NONE:
		return;
	}

	pipe_config->shared_dpll = intel_get_shared_dpll_by_id(dev_priv, id);
}