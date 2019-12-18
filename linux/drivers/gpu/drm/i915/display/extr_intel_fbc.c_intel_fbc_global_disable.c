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
struct intel_fbc {int /*<<< orphan*/  lock; TYPE_1__* crtc; scalar_t__ enabled; } ;
struct drm_i915_private {struct intel_fbc fbc; } ;
struct TYPE_2__ {int /*<<< orphan*/  active; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __intel_fbc_disable (struct drm_i915_private*) ; 
 int /*<<< orphan*/  fbc_supported (struct drm_i915_private*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void intel_fbc_global_disable(struct drm_i915_private *dev_priv)
{
	struct intel_fbc *fbc = &dev_priv->fbc;

	if (!fbc_supported(dev_priv))
		return;

	mutex_lock(&fbc->lock);
	if (fbc->enabled) {
		WARN_ON(fbc->crtc->active);
		__intel_fbc_disable(dev_priv);
	}
	mutex_unlock(&fbc->lock);
}