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
struct intel_fbc {int /*<<< orphan*/  lock; } ;
struct drm_i915_private {struct intel_fbc fbc; } ;

/* Variables and functions */
 int /*<<< orphan*/  __intel_fbc_cleanup_cfb (struct drm_i915_private*) ; 
 int /*<<< orphan*/  fbc_supported (struct drm_i915_private*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void intel_fbc_cleanup_cfb(struct drm_i915_private *dev_priv)
{
	struct intel_fbc *fbc = &dev_priv->fbc;

	if (!fbc_supported(dev_priv))
		return;

	mutex_lock(&fbc->lock);
	__intel_fbc_cleanup_cfb(dev_priv);
	mutex_unlock(&fbc->lock);
}