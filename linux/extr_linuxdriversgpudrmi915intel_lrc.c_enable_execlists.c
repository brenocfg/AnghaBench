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
struct TYPE_2__ {int ggtt_offset; } ;
struct intel_engine_cs {int /*<<< orphan*/  mmio_base; TYPE_1__ status_page; struct drm_i915_private* i915; } ;
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GEN11_GFX_DISABLE_LEGACY_MODE ; 
 int /*<<< orphan*/  GFX_RUN_LIST_ENABLE ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int) ; 
 int INTEL_GEN (struct drm_i915_private*) ; 
 int /*<<< orphan*/  POSTING_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RING_HWSTAM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RING_HWS_PGA (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RING_MI_MODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RING_MODE_GEN7 (struct intel_engine_cs*) ; 
 int /*<<< orphan*/  STOP_RING ; 
 int _MASKED_BIT_DISABLE (int /*<<< orphan*/ ) ; 
 int _MASKED_BIT_ENABLE (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void enable_execlists(struct intel_engine_cs *engine)
{
	struct drm_i915_private *dev_priv = engine->i915;

	I915_WRITE(RING_HWSTAM(engine->mmio_base), 0xffffffff);

	/*
	 * Make sure we're not enabling the new 12-deep CSB
	 * FIFO as that requires a slightly updated handling
	 * in the ctx switch irq. Since we're currently only
	 * using only 2 elements of the enhanced execlists the
	 * deeper FIFO it's not needed and it's not worth adding
	 * more statements to the irq handler to support it.
	 */
	if (INTEL_GEN(dev_priv) >= 11)
		I915_WRITE(RING_MODE_GEN7(engine),
			   _MASKED_BIT_DISABLE(GEN11_GFX_DISABLE_LEGACY_MODE));
	else
		I915_WRITE(RING_MODE_GEN7(engine),
			   _MASKED_BIT_ENABLE(GFX_RUN_LIST_ENABLE));

	I915_WRITE(RING_MI_MODE(engine->mmio_base),
		   _MASKED_BIT_DISABLE(STOP_RING));

	I915_WRITE(RING_HWS_PGA(engine->mmio_base),
		   engine->status_page.ggtt_offset);
	POSTING_READ(RING_HWS_PGA(engine->mmio_base));
}