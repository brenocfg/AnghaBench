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
struct intel_fbc {int flip_pending; int active; int /*<<< orphan*/  busy_bits; int /*<<< orphan*/  params; struct intel_crtc* crtc; int /*<<< orphan*/  enabled; int /*<<< orphan*/  lock; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;
struct intel_crtc {TYPE_1__ base; } ;
struct drm_i915_private {struct intel_fbc fbc; } ;
struct TYPE_4__ {int /*<<< orphan*/  enable_fbc; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  __intel_fbc_disable (struct drm_i915_private*) ; 
 TYPE_2__ i915_modparams ; 
 int /*<<< orphan*/  intel_fbc_can_activate (struct intel_crtc*) ; 
 int /*<<< orphan*/  intel_fbc_deactivate (struct drm_i915_private*,char*) ; 
 int /*<<< orphan*/  intel_fbc_get_reg_params (struct intel_crtc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  intel_fbc_hw_activate (struct drm_i915_private*) ; 
 int /*<<< orphan*/  mutex_is_locked (int /*<<< orphan*/ *) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __intel_fbc_post_update(struct intel_crtc *crtc)
{
	struct drm_i915_private *dev_priv = to_i915(crtc->base.dev);
	struct intel_fbc *fbc = &dev_priv->fbc;

	WARN_ON(!mutex_is_locked(&fbc->lock));

	if (!fbc->enabled || fbc->crtc != crtc)
		return;

	fbc->flip_pending = false;
	WARN_ON(fbc->active);

	if (!i915_modparams.enable_fbc) {
		intel_fbc_deactivate(dev_priv, "disabled at runtime per module param");
		__intel_fbc_disable(dev_priv);

		return;
	}

	intel_fbc_get_reg_params(crtc, &fbc->params);

	if (!intel_fbc_can_activate(crtc))
		return;

	if (!fbc->busy_bits) {
		intel_fbc_deactivate(dev_priv, "FBC enabled (active or scheduled)");
		intel_fbc_hw_activate(dev_priv);
	} else
		intel_fbc_deactivate(dev_priv, "frontbuffer write");
}