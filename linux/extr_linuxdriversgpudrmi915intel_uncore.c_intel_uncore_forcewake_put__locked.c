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
struct TYPE_3__ {int /*<<< orphan*/  force_wake_put; } ;
struct TYPE_4__ {TYPE_1__ funcs; int /*<<< orphan*/  lock; } ;
struct drm_i915_private {TYPE_2__ uncore; } ;
typedef  enum forcewake_domains { ____Placeholder_forcewake_domains } forcewake_domains ;

/* Variables and functions */
 int /*<<< orphan*/  __intel_uncore_forcewake_put (struct drm_i915_private*,int) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 

void intel_uncore_forcewake_put__locked(struct drm_i915_private *dev_priv,
					enum forcewake_domains fw_domains)
{
	lockdep_assert_held(&dev_priv->uncore.lock);

	if (!dev_priv->uncore.funcs.force_wake_put)
		return;

	__intel_uncore_forcewake_put(dev_priv, fw_domains);
}