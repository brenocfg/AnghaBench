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
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct intel_encoder {TYPE_1__ base; } ;
struct intel_crtc_state {scalar_t__ port_clock; int clock_set; int /*<<< orphan*/  dpll; } ;
struct drm_i915_private {int dummy; } ;
struct dp_link_dpll {scalar_t__ clock; int /*<<< orphan*/  dpll; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct dp_link_dpll*) ; 
 scalar_t__ HAS_PCH_SPLIT (struct drm_i915_private*) ; 
 scalar_t__ IS_CHERRYVIEW (struct drm_i915_private*) ; 
 scalar_t__ IS_G4X (struct drm_i915_private*) ; 
 scalar_t__ IS_VALLEYVIEW (struct drm_i915_private*) ; 
 struct dp_link_dpll* chv_dpll ; 
 struct dp_link_dpll* g4x_dpll ; 
 struct dp_link_dpll* pch_dpll ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 
 struct dp_link_dpll* vlv_dpll ; 

__attribute__((used)) static void
intel_dp_set_clock(struct intel_encoder *encoder,
		   struct intel_crtc_state *pipe_config)
{
	struct drm_i915_private *dev_priv = to_i915(encoder->base.dev);
	const struct dp_link_dpll *divisor = NULL;
	int i, count = 0;

	if (IS_G4X(dev_priv)) {
		divisor = g4x_dpll;
		count = ARRAY_SIZE(g4x_dpll);
	} else if (HAS_PCH_SPLIT(dev_priv)) {
		divisor = pch_dpll;
		count = ARRAY_SIZE(pch_dpll);
	} else if (IS_CHERRYVIEW(dev_priv)) {
		divisor = chv_dpll;
		count = ARRAY_SIZE(chv_dpll);
	} else if (IS_VALLEYVIEW(dev_priv)) {
		divisor = vlv_dpll;
		count = ARRAY_SIZE(vlv_dpll);
	}

	if (divisor && count) {
		for (i = 0; i < count; i++) {
			if (pipe_config->port_clock == divisor[i].clock) {
				pipe_config->dpll = divisor[i].dpll;
				pipe_config->clock_set = true;
				break;
			}
		}
	}
}