#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ saved_mmio_debug; scalar_t__ saved_mmio_check; int /*<<< orphan*/  count; } ;
struct TYPE_5__ {int /*<<< orphan*/  lock; scalar_t__ unclaimed_mmio_check; TYPE_1__ user_forcewake; } ;
struct drm_i915_private {TYPE_2__ uncore; } ;
struct TYPE_6__ {scalar_t__ mmio_debug; } ;

/* Variables and functions */
 int /*<<< orphan*/  FORCEWAKE_ALL ; 
 TYPE_3__ i915_modparams ; 
 int /*<<< orphan*/  intel_uncore_forcewake_get__locked (struct drm_i915_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

void intel_uncore_forcewake_user_get(struct drm_i915_private *dev_priv)
{
	spin_lock_irq(&dev_priv->uncore.lock);
	if (!dev_priv->uncore.user_forcewake.count++) {
		intel_uncore_forcewake_get__locked(dev_priv, FORCEWAKE_ALL);

		/* Save and disable mmio debugging for the user bypass */
		dev_priv->uncore.user_forcewake.saved_mmio_check =
			dev_priv->uncore.unclaimed_mmio_check;
		dev_priv->uncore.user_forcewake.saved_mmio_debug =
			i915_modparams.mmio_debug;

		dev_priv->uncore.unclaimed_mmio_check = 0;
		i915_modparams.mmio_debug = 0;
	}
	spin_unlock_irq(&dev_priv->uncore.lock);
}