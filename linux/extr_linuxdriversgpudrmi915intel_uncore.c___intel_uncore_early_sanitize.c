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
struct TYPE_3__ {int /*<<< orphan*/  (* force_wake_get ) (struct drm_i915_private*,unsigned int) ;} ;
struct TYPE_4__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  fifo_count; TYPE_1__ funcs; } ;
struct drm_i915_private {TYPE_2__ uncore; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG (char*) ; 
 int /*<<< orphan*/  GTFIFOCTL ; 
 int GT_FIFO_CTL_BLOCK_ALL_POLICY_STALL ; 
 int GT_FIFO_CTL_RC6_POLICY_STALL ; 
 scalar_t__ IS_CHERRYVIEW (struct drm_i915_private*) ; 
 scalar_t__ IS_GEN6 (struct drm_i915_private*) ; 
 scalar_t__ IS_GEN7 (struct drm_i915_private*) ; 
 int __raw_i915_read32 (struct drm_i915_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __raw_i915_write32 (struct drm_i915_private*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ check_for_unclaimed_mmio (struct drm_i915_private*) ; 
 int /*<<< orphan*/  fifo_free_entries (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_uncore_forcewake_reset (struct drm_i915_private*) ; 
 int /*<<< orphan*/  iosf_mbi_punit_acquire () ; 
 int /*<<< orphan*/  iosf_mbi_punit_release () ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct drm_i915_private*,unsigned int) ; 

__attribute__((used)) static void __intel_uncore_early_sanitize(struct drm_i915_private *dev_priv,
					  unsigned int restore_forcewake)
{
	/* clear out unclaimed reg detection bit */
	if (check_for_unclaimed_mmio(dev_priv))
		DRM_DEBUG("unclaimed mmio detected on uncore init, clearing\n");

	/* WaDisableShadowRegForCpd:chv */
	if (IS_CHERRYVIEW(dev_priv)) {
		__raw_i915_write32(dev_priv, GTFIFOCTL,
				   __raw_i915_read32(dev_priv, GTFIFOCTL) |
				   GT_FIFO_CTL_BLOCK_ALL_POLICY_STALL |
				   GT_FIFO_CTL_RC6_POLICY_STALL);
	}

	iosf_mbi_punit_acquire();
	intel_uncore_forcewake_reset(dev_priv);
	if (restore_forcewake) {
		spin_lock_irq(&dev_priv->uncore.lock);
		dev_priv->uncore.funcs.force_wake_get(dev_priv,
						      restore_forcewake);

		if (IS_GEN6(dev_priv) || IS_GEN7(dev_priv))
			dev_priv->uncore.fifo_count =
				fifo_free_entries(dev_priv);
		spin_unlock_irq(&dev_priv->uncore.lock);
	}
	iosf_mbi_punit_release();
}