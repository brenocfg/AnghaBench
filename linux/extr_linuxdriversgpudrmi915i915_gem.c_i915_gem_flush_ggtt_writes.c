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
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;
struct drm_i915_private {TYPE_1__ uncore; } ;

/* Variables and functions */
 int /*<<< orphan*/  POSTING_READ_FW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RENDER_RING_BASE ; 
 int /*<<< orphan*/  RING_HEAD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i915_gem_chipset_flush (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_runtime_pm_get (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_runtime_pm_put (struct drm_i915_private*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

void i915_gem_flush_ggtt_writes(struct drm_i915_private *dev_priv)
{
	/*
	 * No actual flushing is required for the GTT write domain for reads
	 * from the GTT domain. Writes to it "immediately" go to main memory
	 * as far as we know, so there's no chipset flush. It also doesn't
	 * land in the GPU render cache.
	 *
	 * However, we do have to enforce the order so that all writes through
	 * the GTT land before any writes to the device, such as updates to
	 * the GATT itself.
	 *
	 * We also have to wait a bit for the writes to land from the GTT.
	 * An uncached read (i.e. mmio) seems to be ideal for the round-trip
	 * timing. This issue has only been observed when switching quickly
	 * between GTT writes and CPU reads from inside the kernel on recent hw,
	 * and it appears to only affect discrete GTT blocks (i.e. on LLC
	 * system agents we cannot reproduce this behaviour, until Cannonlake
	 * that was!).
	 */

	i915_gem_chipset_flush(dev_priv);

	intel_runtime_pm_get(dev_priv);
	spin_lock_irq(&dev_priv->uncore.lock);

	POSTING_READ_FW(RING_HEAD(RENDER_RING_BASE));

	spin_unlock_irq(&dev_priv->uncore.lock);
	intel_runtime_pm_put(dev_priv);
}