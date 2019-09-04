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
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct intel_encoder {int port; TYPE_1__ base; } ;
struct intel_crtc_state {int port_clock; int /*<<< orphan*/  shared_dpll; } ;
struct drm_i915_private {int dummy; } ;
typedef  enum port { ____Placeholder_port } port ;

/* Variables and functions */
 int /*<<< orphan*/  INTEL_OUTPUT_HDMI ; 
 int PORT_A ; 
 int PORT_B ; 
 int /*<<< orphan*/  WARN (int,char*) ; 
 int cnl_calc_wrpll_link (struct drm_i915_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ddi_dotclock_get (struct intel_crtc_state*) ; 
 int icl_calc_dp_combo_pll_link (struct drm_i915_private*,int /*<<< orphan*/ ) ; 
 scalar_t__ intel_crtc_has_type (struct intel_crtc_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_get_shared_dpll_id (struct drm_i915_private*,int /*<<< orphan*/ ) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void icl_ddi_clock_get(struct intel_encoder *encoder,
			      struct intel_crtc_state *pipe_config)
{
	struct drm_i915_private *dev_priv = to_i915(encoder->base.dev);
	enum port port = encoder->port;
	int link_clock = 0;
	uint32_t pll_id;

	pll_id = intel_get_shared_dpll_id(dev_priv, pipe_config->shared_dpll);
	if (port == PORT_A || port == PORT_B) {
		if (intel_crtc_has_type(pipe_config, INTEL_OUTPUT_HDMI))
			link_clock = cnl_calc_wrpll_link(dev_priv, pll_id);
		else
			link_clock = icl_calc_dp_combo_pll_link(dev_priv,
								pll_id);
	} else {
		/* FIXME - Add for MG PLL */
		WARN(1, "MG PLL clock_get code not implemented yet\n");
	}

	pipe_config->port_clock = link_clock;
	ddi_dotclock_get(pipe_config);
}