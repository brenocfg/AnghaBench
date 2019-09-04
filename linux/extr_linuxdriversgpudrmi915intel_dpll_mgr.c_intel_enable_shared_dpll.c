#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {unsigned int crtc_mask; } ;
struct intel_shared_dpll {unsigned int active_mask; int on; TYPE_5__* info; TYPE_2__ state; } ;
struct TYPE_9__ {int /*<<< orphan*/  id; } ;
struct TYPE_12__ {TYPE_3__ base; struct drm_device* dev; } ;
struct intel_crtc {TYPE_6__ base; TYPE_1__* config; } ;
struct drm_i915_private {int /*<<< orphan*/  dpll_lock; } ;
struct drm_device {int dummy; } ;
struct TYPE_11__ {TYPE_4__* funcs; int /*<<< orphan*/  name; } ;
struct TYPE_10__ {int /*<<< orphan*/  (* enable ) (struct drm_i915_private*,struct intel_shared_dpll*) ;} ;
struct TYPE_7__ {struct intel_shared_dpll* shared_dpll; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,int /*<<< orphan*/ ,...) ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  assert_shared_dpll_enabled (struct drm_i915_private*,struct intel_shared_dpll*) ; 
 unsigned int drm_crtc_mask (TYPE_6__*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct drm_i915_private*,struct intel_shared_dpll*) ; 
 struct drm_i915_private* to_i915 (struct drm_device*) ; 

void intel_enable_shared_dpll(struct intel_crtc *crtc)
{
	struct drm_device *dev = crtc->base.dev;
	struct drm_i915_private *dev_priv = to_i915(dev);
	struct intel_shared_dpll *pll = crtc->config->shared_dpll;
	unsigned int crtc_mask = drm_crtc_mask(&crtc->base);
	unsigned int old_mask;

	if (WARN_ON(pll == NULL))
		return;

	mutex_lock(&dev_priv->dpll_lock);
	old_mask = pll->active_mask;

	if (WARN_ON(!(pll->state.crtc_mask & crtc_mask)) ||
	    WARN_ON(pll->active_mask & crtc_mask))
		goto out;

	pll->active_mask |= crtc_mask;

	DRM_DEBUG_KMS("enable %s (active %x, on? %d) for crtc %d\n",
		      pll->info->name, pll->active_mask, pll->on,
		      crtc->base.base.id);

	if (old_mask) {
		WARN_ON(!pll->on);
		assert_shared_dpll_enabled(dev_priv, pll);
		goto out;
	}
	WARN_ON(pll->on);

	DRM_DEBUG_KMS("enabling %s\n", pll->info->name);
	pll->info->funcs->enable(dev_priv, pll);
	pll->on = true;

out:
	mutex_unlock(&dev_priv->dpll_lock);
}