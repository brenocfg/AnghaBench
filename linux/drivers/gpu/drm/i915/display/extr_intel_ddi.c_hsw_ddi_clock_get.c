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
typedef  int u32 ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct intel_encoder {TYPE_1__ base; } ;
struct intel_crtc_state {int port_clock; int /*<<< orphan*/  shared_dpll; } ;
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
 int I915_READ (int /*<<< orphan*/ ) ; 
#define  PORT_CLK_SEL_LCPLL_1350 133 
#define  PORT_CLK_SEL_LCPLL_2700 132 
#define  PORT_CLK_SEL_LCPLL_810 131 
 int PORT_CLK_SEL_MASK ; 
#define  PORT_CLK_SEL_SPLL 130 
#define  PORT_CLK_SEL_WRPLL1 129 
#define  PORT_CLK_SEL_WRPLL2 128 
 int /*<<< orphan*/  SPLL_CTL ; 
 int SPLL_FREQ_1350MHz ; 
 int SPLL_FREQ_2700MHz ; 
 int SPLL_FREQ_810MHz ; 
 int SPLL_FREQ_MASK ; 
 int /*<<< orphan*/  WARN (int,char*) ; 
 int /*<<< orphan*/  WRPLL_CTL (int) ; 
 int /*<<< orphan*/  ddi_dotclock_get (struct intel_crtc_state*) ; 
 int hsw_ddi_calc_wrpll_link (struct drm_i915_private*,int /*<<< orphan*/ ) ; 
 int hsw_pll_to_ddi_pll_sel (int /*<<< orphan*/ ) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hsw_ddi_clock_get(struct intel_encoder *encoder,
			      struct intel_crtc_state *pipe_config)
{
	struct drm_i915_private *dev_priv = to_i915(encoder->base.dev);
	int link_clock = 0;
	u32 val, pll;

	val = hsw_pll_to_ddi_pll_sel(pipe_config->shared_dpll);
	switch (val & PORT_CLK_SEL_MASK) {
	case PORT_CLK_SEL_LCPLL_810:
		link_clock = 81000;
		break;
	case PORT_CLK_SEL_LCPLL_1350:
		link_clock = 135000;
		break;
	case PORT_CLK_SEL_LCPLL_2700:
		link_clock = 270000;
		break;
	case PORT_CLK_SEL_WRPLL1:
		link_clock = hsw_ddi_calc_wrpll_link(dev_priv, WRPLL_CTL(0));
		break;
	case PORT_CLK_SEL_WRPLL2:
		link_clock = hsw_ddi_calc_wrpll_link(dev_priv, WRPLL_CTL(1));
		break;
	case PORT_CLK_SEL_SPLL:
		pll = I915_READ(SPLL_CTL) & SPLL_FREQ_MASK;
		if (pll == SPLL_FREQ_810MHz)
			link_clock = 81000;
		else if (pll == SPLL_FREQ_1350MHz)
			link_clock = 135000;
		else if (pll == SPLL_FREQ_2700MHz)
			link_clock = 270000;
		else {
			WARN(1, "bad spll freq\n");
			return;
		}
		break;
	default:
		WARN(1, "bad port clock sel\n");
		return;
	}

	pipe_config->port_clock = link_clock * 2;

	ddi_dotclock_get(pipe_config);
}