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
struct intel_shared_dpll {int dummy; } ;
struct TYPE_4__ {TYPE_1__* crtc; } ;
struct intel_crtc_state {int port_clock; TYPE_2__ base; } ;
struct drm_i915_private {int dummy; } ;
typedef  enum intel_dpll_id { ____Placeholder_intel_dpll_id } intel_dpll_id ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int DPLL_ID_LCPLL_1350 ; 
 int DPLL_ID_LCPLL_2700 ; 
 int DPLL_ID_LCPLL_810 ; 
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,int) ; 
 struct intel_shared_dpll* intel_get_shared_dpll_by_id (struct drm_i915_private*,int) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct intel_shared_dpll *
hsw_ddi_dp_get_dpll(struct intel_crtc_state *crtc_state)
{
	struct drm_i915_private *dev_priv = to_i915(crtc_state->base.crtc->dev);
	struct intel_shared_dpll *pll;
	enum intel_dpll_id pll_id;
	int clock = crtc_state->port_clock;

	switch (clock / 2) {
	case 81000:
		pll_id = DPLL_ID_LCPLL_810;
		break;
	case 135000:
		pll_id = DPLL_ID_LCPLL_1350;
		break;
	case 270000:
		pll_id = DPLL_ID_LCPLL_2700;
		break;
	default:
		DRM_DEBUG_KMS("Invalid clock for DP: %d\n", clock);
		return NULL;
	}

	pll = intel_get_shared_dpll_by_id(dev_priv, pll_id);

	if (!pll)
		return NULL;

	return pll;
}