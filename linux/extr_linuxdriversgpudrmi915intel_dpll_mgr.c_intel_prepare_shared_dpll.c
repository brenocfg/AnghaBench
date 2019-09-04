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
struct TYPE_7__ {int /*<<< orphan*/  crtc_mask; } ;
struct intel_shared_dpll {int on; TYPE_4__* info; int /*<<< orphan*/  active_mask; TYPE_2__ state; } ;
struct TYPE_10__ {struct drm_device* dev; } ;
struct intel_crtc {TYPE_1__* config; TYPE_5__ base; } ;
struct drm_i915_private {int /*<<< orphan*/  dpll_lock; } ;
struct drm_device {int dummy; } ;
struct TYPE_9__ {TYPE_3__* funcs; int /*<<< orphan*/  name; } ;
struct TYPE_8__ {int /*<<< orphan*/  (* prepare ) (struct drm_i915_private*,struct intel_shared_dpll*) ;} ;
struct TYPE_6__ {struct intel_shared_dpll* shared_dpll; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  assert_shared_dpll_disabled (struct drm_i915_private*,struct intel_shared_dpll*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct drm_i915_private*,struct intel_shared_dpll*) ; 
 struct drm_i915_private* to_i915 (struct drm_device*) ; 

void intel_prepare_shared_dpll(struct intel_crtc *crtc)
{
	struct drm_device *dev = crtc->base.dev;
	struct drm_i915_private *dev_priv = to_i915(dev);
	struct intel_shared_dpll *pll = crtc->config->shared_dpll;

	if (WARN_ON(pll == NULL))
		return;

	mutex_lock(&dev_priv->dpll_lock);
	WARN_ON(!pll->state.crtc_mask);
	if (!pll->active_mask) {
		DRM_DEBUG_DRIVER("setting up %s\n", pll->info->name);
		WARN_ON(pll->on);
		assert_shared_dpll_disabled(dev_priv, pll);

		pll->info->funcs->prepare(dev_priv, pll);
	}
	mutex_unlock(&dev_priv->dpll_lock);
}