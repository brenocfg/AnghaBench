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
typedef  scalar_t__ u32 ;
struct intel_engine_cs {int /*<<< orphan*/  irq_posted; int /*<<< orphan*/  mmio_base; struct drm_i915_private* i915; } ;
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENGINE_IRQ_BREADCRUMB ; 
 int /*<<< orphan*/  GEM_BUG_ON (int) ; 
 scalar_t__ HAS_VEBOX (struct drm_i915_private*) ; 
 int /*<<< orphan*/  I915_GEM_HWS_INDEX ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ IS_GEN6 (struct drm_i915_private*) ; 
 scalar_t__ IS_GEN7 (struct drm_i915_private*) ; 
 int /*<<< orphan*/  RING_SYNC_0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RING_SYNC_1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RING_SYNC_2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ intel_engine_get_seqno (struct intel_engine_cs*) ; 
 int /*<<< orphan*/  intel_engine_wakeup (struct intel_engine_cs*) ; 
 int /*<<< orphan*/  intel_write_status_page (struct intel_engine_cs*,int /*<<< orphan*/ ,scalar_t__) ; 

void intel_engine_init_global_seqno(struct intel_engine_cs *engine, u32 seqno)
{
	struct drm_i915_private *dev_priv = engine->i915;

	/* Our semaphore implementation is strictly monotonic (i.e. we proceed
	 * so long as the semaphore value in the register/page is greater
	 * than the sync value), so whenever we reset the seqno,
	 * so long as we reset the tracking semaphore value to 0, it will
	 * always be before the next request's seqno. If we don't reset
	 * the semaphore value, then when the seqno moves backwards all
	 * future waits will complete instantly (causing rendering corruption).
	 */
	if (IS_GEN6(dev_priv) || IS_GEN7(dev_priv)) {
		I915_WRITE(RING_SYNC_0(engine->mmio_base), 0);
		I915_WRITE(RING_SYNC_1(engine->mmio_base), 0);
		if (HAS_VEBOX(dev_priv))
			I915_WRITE(RING_SYNC_2(engine->mmio_base), 0);
	}

	intel_write_status_page(engine, I915_GEM_HWS_INDEX, seqno);
	clear_bit(ENGINE_IRQ_BREADCRUMB, &engine->irq_posted);

	/* After manually advancing the seqno, fake the interrupt in case
	 * there are any waiters for that seqno.
	 */
	intel_engine_wakeup(engine);

	GEM_BUG_ON(intel_engine_get_seqno(engine) != seqno);
}