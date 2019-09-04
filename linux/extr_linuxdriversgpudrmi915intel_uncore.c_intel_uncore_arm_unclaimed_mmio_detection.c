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
struct TYPE_3__ {scalar_t__ unclaimed_mmio_check; } ;
struct drm_i915_private {TYPE_1__ uncore; } ;
struct TYPE_4__ {scalar_t__ mmio_debug; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG (char*) ; 
 TYPE_2__ i915_modparams ; 
 int intel_uncore_unclaimed_mmio (struct drm_i915_private*) ; 
 scalar_t__ unlikely (int) ; 

bool
intel_uncore_arm_unclaimed_mmio_detection(struct drm_i915_private *dev_priv)
{
	if (unlikely(i915_modparams.mmio_debug ||
		     dev_priv->uncore.unclaimed_mmio_check <= 0))
		return false;

	if (unlikely(intel_uncore_unclaimed_mmio(dev_priv))) {
		DRM_DEBUG("Unclaimed register detected, "
			  "enabling oneshot unclaimed register reporting. "
			  "Please use i915.mmio_debug=N for more information.\n");
		i915_modparams.mmio_debug++;
		dev_priv->uncore.unclaimed_mmio_check--;
		return true;
	}

	return false;
}