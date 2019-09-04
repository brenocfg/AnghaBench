#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct intel_shared_dpll_state {scalar_t__ crtc_mask; int /*<<< orphan*/  hw_state; } ;
struct intel_shared_dpll {TYPE_4__* info; int /*<<< orphan*/  active_mask; } ;
struct TYPE_5__ {int /*<<< orphan*/  state; } ;
struct intel_crtc_state {int /*<<< orphan*/  dpll_hw_state; TYPE_1__ base; } ;
struct TYPE_6__ {int /*<<< orphan*/  id; } ;
struct TYPE_7__ {int /*<<< orphan*/  name; TYPE_2__ base; int /*<<< orphan*/  dev; } ;
struct intel_crtc {TYPE_3__ base; } ;
struct drm_i915_private {struct intel_shared_dpll* shared_dplls; } ;
typedef  enum intel_dpll_id { ____Placeholder_intel_dpll_id } intel_dpll_id ;
struct TYPE_8__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 struct intel_shared_dpll_state* intel_atomic_get_shared_dpll_state (int /*<<< orphan*/ ) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct intel_shared_dpll *
intel_find_shared_dpll(struct intel_crtc *crtc,
		       struct intel_crtc_state *crtc_state,
		       enum intel_dpll_id range_min,
		       enum intel_dpll_id range_max)
{
	struct drm_i915_private *dev_priv = to_i915(crtc->base.dev);
	struct intel_shared_dpll *pll;
	struct intel_shared_dpll_state *shared_dpll;
	enum intel_dpll_id i;

	shared_dpll = intel_atomic_get_shared_dpll_state(crtc_state->base.state);

	for (i = range_min; i <= range_max; i++) {
		pll = &dev_priv->shared_dplls[i];

		/* Only want to check enabled timings first */
		if (shared_dpll[i].crtc_mask == 0)
			continue;

		if (memcmp(&crtc_state->dpll_hw_state,
			   &shared_dpll[i].hw_state,
			   sizeof(crtc_state->dpll_hw_state)) == 0) {
			DRM_DEBUG_KMS("[CRTC:%d:%s] sharing existing %s (crtc mask 0x%08x, active %x)\n",
				      crtc->base.base.id, crtc->base.name,
				      pll->info->name,
				      shared_dpll[i].crtc_mask,
				      pll->active_mask);
			return pll;
		}
	}

	/* Ok no matching timings, maybe there's a free one? */
	for (i = range_min; i <= range_max; i++) {
		pll = &dev_priv->shared_dplls[i];
		if (shared_dpll[i].crtc_mask == 0) {
			DRM_DEBUG_KMS("[CRTC:%d:%s] allocated %s\n",
				      crtc->base.base.id, crtc->base.name,
				      pll->info->name);
			return pll;
		}
	}

	return NULL;
}