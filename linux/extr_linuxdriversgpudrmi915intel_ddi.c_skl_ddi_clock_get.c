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
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct intel_encoder {TYPE_1__ base; } ;
struct intel_crtc_state {int port_clock; int /*<<< orphan*/  shared_dpll; } ;
struct drm_i915_private {int dummy; } ;
typedef  enum intel_dpll_id { ____Placeholder_intel_dpll_id } intel_dpll_id ;

/* Variables and functions */
 int /*<<< orphan*/  DPLL_CTRL1 ; 
 int DPLL_CTRL1_HDMI_MODE (int) ; 
#define  DPLL_CTRL1_LINK_RATE_1080 133 
#define  DPLL_CTRL1_LINK_RATE_1350 132 
#define  DPLL_CTRL1_LINK_RATE_1620 131 
#define  DPLL_CTRL1_LINK_RATE_2160 130 
#define  DPLL_CTRL1_LINK_RATE_2700 129 
#define  DPLL_CTRL1_LINK_RATE_810 128 
 int DPLL_CTRL1_LINK_RATE_MASK (int) ; 
 int DPLL_CTRL1_LINK_RATE_SHIFT (int) ; 
 int I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARN (int,char*) ; 
 int /*<<< orphan*/  ddi_dotclock_get (struct intel_crtc_state*) ; 
 int intel_get_shared_dpll_id (struct drm_i915_private*,int /*<<< orphan*/ ) ; 
 int skl_calc_wrpll_link (struct drm_i915_private*,int) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void skl_ddi_clock_get(struct intel_encoder *encoder,
				struct intel_crtc_state *pipe_config)
{
	struct drm_i915_private *dev_priv = to_i915(encoder->base.dev);
	int link_clock = 0;
	uint32_t dpll_ctl1;
	enum intel_dpll_id pll_id;

	pll_id = intel_get_shared_dpll_id(dev_priv, pipe_config->shared_dpll);

	dpll_ctl1 = I915_READ(DPLL_CTRL1);

	if (dpll_ctl1 & DPLL_CTRL1_HDMI_MODE(pll_id)) {
		link_clock = skl_calc_wrpll_link(dev_priv, pll_id);
	} else {
		link_clock = dpll_ctl1 & DPLL_CTRL1_LINK_RATE_MASK(pll_id);
		link_clock >>= DPLL_CTRL1_LINK_RATE_SHIFT(pll_id);

		switch (link_clock) {
		case DPLL_CTRL1_LINK_RATE_810:
			link_clock = 81000;
			break;
		case DPLL_CTRL1_LINK_RATE_1080:
			link_clock = 108000;
			break;
		case DPLL_CTRL1_LINK_RATE_1350:
			link_clock = 135000;
			break;
		case DPLL_CTRL1_LINK_RATE_1620:
			link_clock = 162000;
			break;
		case DPLL_CTRL1_LINK_RATE_2160:
			link_clock = 216000;
			break;
		case DPLL_CTRL1_LINK_RATE_2700:
			link_clock = 270000;
			break;
		default:
			WARN(1, "Unsupported link rate\n");
			break;
		}
		link_clock *= 2;
	}

	pipe_config->port_clock = link_clock;

	ddi_dotclock_get(pipe_config);
}