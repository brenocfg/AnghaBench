#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct intel_shared_dpll {unsigned int active_mask; int on; TYPE_4__* info; } ;
struct TYPE_6__ {int /*<<< orphan*/  crtc; } ;
struct intel_crtc_state {struct intel_shared_dpll* shared_dpll; TYPE_1__ base; } ;
struct TYPE_7__ {int /*<<< orphan*/  id; } ;
struct TYPE_10__ {TYPE_2__ base; int /*<<< orphan*/  dev; } ;
struct intel_crtc {TYPE_5__ base; } ;
struct drm_i915_private {int /*<<< orphan*/  dpll_lock; } ;
struct TYPE_9__ {TYPE_3__* funcs; int /*<<< orphan*/  name; } ;
struct TYPE_8__ {int /*<<< orphan*/  (* disable ) (struct drm_i915_private*,struct intel_shared_dpll*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,int /*<<< orphan*/ ,...) ; 
 int INTEL_GEN (struct drm_i915_private*) ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  assert_shared_dpll_enabled (struct drm_i915_private*,struct intel_shared_dpll*) ; 
 unsigned int drm_crtc_mask (TYPE_5__*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct drm_i915_private*,struct intel_shared_dpll*) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 
 struct intel_crtc* to_intel_crtc (int /*<<< orphan*/ ) ; 

void intel_disable_shared_dpll(const struct intel_crtc_state *crtc_state)
{
	struct intel_crtc *crtc = to_intel_crtc(crtc_state->base.crtc);
	struct drm_i915_private *dev_priv = to_i915(crtc->base.dev);
	struct intel_shared_dpll *pll = crtc_state->shared_dpll;
	unsigned int crtc_mask = drm_crtc_mask(&crtc->base);

	/* PCH only available on ILK+ */
	if (INTEL_GEN(dev_priv) < 5)
		return;

	if (pll == NULL)
		return;

	mutex_lock(&dev_priv->dpll_lock);
	if (WARN_ON(!(pll->active_mask & crtc_mask)))
		goto out;

	DRM_DEBUG_KMS("disable %s (active %x, on? %d) for crtc %d\n",
		      pll->info->name, pll->active_mask, pll->on,
		      crtc->base.base.id);

	assert_shared_dpll_enabled(dev_priv, pll);
	WARN_ON(!pll->on);

	pll->active_mask &= ~crtc_mask;
	if (pll->active_mask)
		goto out;

	DRM_DEBUG_KMS("disabling %s\n", pll->info->name);
	pll->info->funcs->disable(dev_priv, pll);
	pll->on = false;

out:
	mutex_unlock(&dev_priv->dpll_lock);
}