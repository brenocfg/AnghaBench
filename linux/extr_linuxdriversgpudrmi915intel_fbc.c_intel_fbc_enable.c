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
struct intel_fbc {int enabled; int active; char* no_fbc_reason; int /*<<< orphan*/  lock; struct intel_crtc* crtc; } ;
struct intel_crtc_state {int /*<<< orphan*/  enable_fbc; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct intel_crtc {int /*<<< orphan*/  pipe; TYPE_1__ base; } ;
struct drm_i915_private {struct intel_fbc fbc; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  fbc_supported (struct drm_i915_private*) ; 
 scalar_t__ intel_fbc_alloc_cfb (struct intel_crtc*) ; 
 int /*<<< orphan*/  intel_fbc_update_state_cache (struct intel_crtc*,struct intel_crtc_state*,struct intel_plane_state*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pipe_name (int /*<<< orphan*/ ) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 

void intel_fbc_enable(struct intel_crtc *crtc,
		      struct intel_crtc_state *crtc_state,
		      struct intel_plane_state *plane_state)
{
	struct drm_i915_private *dev_priv = to_i915(crtc->base.dev);
	struct intel_fbc *fbc = &dev_priv->fbc;

	if (!fbc_supported(dev_priv))
		return;

	mutex_lock(&fbc->lock);

	if (fbc->enabled) {
		WARN_ON(fbc->crtc == NULL);
		if (fbc->crtc == crtc) {
			WARN_ON(!crtc_state->enable_fbc);
			WARN_ON(fbc->active);
		}
		goto out;
	}

	if (!crtc_state->enable_fbc)
		goto out;

	WARN_ON(fbc->active);
	WARN_ON(fbc->crtc != NULL);

	intel_fbc_update_state_cache(crtc, crtc_state, plane_state);
	if (intel_fbc_alloc_cfb(crtc)) {
		fbc->no_fbc_reason = "not enough stolen memory";
		goto out;
	}

	DRM_DEBUG_KMS("Enabling FBC on pipe %c\n", pipe_name(crtc->pipe));
	fbc->no_fbc_reason = "FBC enabled but not active yet\n";

	fbc->enabled = true;
	fbc->crtc = crtc;
out:
	mutex_unlock(&fbc->lock);
}