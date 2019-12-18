#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct intel_fbc {int enabled; int active; struct intel_crtc* crtc; int /*<<< orphan*/  lock; } ;
struct intel_crtc {int /*<<< orphan*/  pipe; } ;
struct drm_i915_private {struct intel_fbc fbc; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  __intel_fbc_cleanup_cfb (struct drm_i915_private*) ; 
 int /*<<< orphan*/  mutex_is_locked (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pipe_name (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __intel_fbc_disable(struct drm_i915_private *dev_priv)
{
	struct intel_fbc *fbc = &dev_priv->fbc;
	struct intel_crtc *crtc = fbc->crtc;

	WARN_ON(!mutex_is_locked(&fbc->lock));
	WARN_ON(!fbc->enabled);
	WARN_ON(fbc->active);

	DRM_DEBUG_KMS("Disabling FBC on pipe %c\n", pipe_name(crtc->pipe));

	__intel_fbc_cleanup_cfb(dev_priv);

	fbc->enabled = false;
	fbc->crtc = NULL;
}