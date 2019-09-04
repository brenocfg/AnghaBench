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
struct intel_plane_state {int dummy; } ;
struct intel_fbc {int flip_pending; int /*<<< orphan*/  lock; struct intel_crtc* crtc; int /*<<< orphan*/  enabled; } ;
struct intel_crtc_state {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct intel_crtc {TYPE_1__ base; } ;
struct drm_i915_private {struct intel_fbc fbc; } ;

/* Variables and functions */
 int /*<<< orphan*/  fbc_supported (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_fbc_deactivate (struct drm_i915_private*,char const*) ; 
 int /*<<< orphan*/  intel_fbc_update_state_cache (struct intel_crtc*,struct intel_crtc_state*,struct intel_plane_state*) ; 
 int /*<<< orphan*/  multiple_pipes_ok (struct intel_crtc*,struct intel_plane_state*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 

void intel_fbc_pre_update(struct intel_crtc *crtc,
			  struct intel_crtc_state *crtc_state,
			  struct intel_plane_state *plane_state)
{
	struct drm_i915_private *dev_priv = to_i915(crtc->base.dev);
	struct intel_fbc *fbc = &dev_priv->fbc;
	const char *reason = "update pending";

	if (!fbc_supported(dev_priv))
		return;

	mutex_lock(&fbc->lock);

	if (!multiple_pipes_ok(crtc, plane_state)) {
		reason = "more than one pipe active";
		goto deactivate;
	}

	if (!fbc->enabled || fbc->crtc != crtc)
		goto unlock;

	intel_fbc_update_state_cache(crtc, crtc_state, plane_state);
	fbc->flip_pending = true;

deactivate:
	intel_fbc_deactivate(dev_priv, reason);
unlock:
	mutex_unlock(&fbc->lock);
}