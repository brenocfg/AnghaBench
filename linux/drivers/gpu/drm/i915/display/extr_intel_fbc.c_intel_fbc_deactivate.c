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
struct intel_fbc {char const* no_fbc_reason; scalar_t__ active; int /*<<< orphan*/  lock; } ;
struct drm_i915_private {struct intel_fbc fbc; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  intel_fbc_hw_deactivate (struct drm_i915_private*) ; 
 int /*<<< orphan*/  mutex_is_locked (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void intel_fbc_deactivate(struct drm_i915_private *dev_priv,
				 const char *reason)
{
	struct intel_fbc *fbc = &dev_priv->fbc;

	WARN_ON(!mutex_is_locked(&fbc->lock));

	if (fbc->active)
		intel_fbc_hw_deactivate(dev_priv);

	fbc->no_fbc_reason = reason;
}