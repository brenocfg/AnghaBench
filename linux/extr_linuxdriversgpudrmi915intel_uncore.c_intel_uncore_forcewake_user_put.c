#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  saved_mmio_debug; int /*<<< orphan*/  saved_mmio_check; int /*<<< orphan*/  count; } ;
struct TYPE_6__ {int /*<<< orphan*/  lock; TYPE_1__ user_forcewake; int /*<<< orphan*/  unclaimed_mmio_check; } ;
struct TYPE_7__ {int /*<<< orphan*/  dev; } ;
struct drm_i915_private {TYPE_2__ uncore; TYPE_3__ drm; } ;
struct TYPE_8__ {int /*<<< orphan*/  mmio_debug; } ;

/* Variables and functions */
 int /*<<< orphan*/  FORCEWAKE_ALL ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*) ; 
 TYPE_4__ i915_modparams ; 
 int /*<<< orphan*/  intel_uncore_forcewake_put__locked (struct drm_i915_private*,int /*<<< orphan*/ ) ; 
 scalar_t__ intel_uncore_unclaimed_mmio (struct drm_i915_private*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

void intel_uncore_forcewake_user_put(struct drm_i915_private *dev_priv)
{
	spin_lock_irq(&dev_priv->uncore.lock);
	if (!--dev_priv->uncore.user_forcewake.count) {
		if (intel_uncore_unclaimed_mmio(dev_priv))
			dev_info(dev_priv->drm.dev,
				 "Invalid mmio detected during user access\n");

		dev_priv->uncore.unclaimed_mmio_check =
			dev_priv->uncore.user_forcewake.saved_mmio_check;
		i915_modparams.mmio_debug =
			dev_priv->uncore.user_forcewake.saved_mmio_debug;

		intel_uncore_forcewake_put__locked(dev_priv, FORCEWAKE_ALL);
	}
	spin_unlock_irq(&dev_priv->uncore.lock);
}