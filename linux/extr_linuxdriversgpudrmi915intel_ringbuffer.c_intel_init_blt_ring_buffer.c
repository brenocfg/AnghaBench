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
struct intel_engine_cs {int /*<<< orphan*/  irq_enable_mask; int /*<<< orphan*/  emit_flush; struct drm_i915_private* i915; } ;
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GT_BLT_USER_INTERRUPT ; 
 int /*<<< orphan*/  gen6_ring_flush ; 
 int intel_init_ring_buffer (struct intel_engine_cs*) ; 
 int /*<<< orphan*/  intel_ring_default_vfuncs (struct drm_i915_private*,struct intel_engine_cs*) ; 

int intel_init_blt_ring_buffer(struct intel_engine_cs *engine)
{
	struct drm_i915_private *dev_priv = engine->i915;

	intel_ring_default_vfuncs(dev_priv, engine);

	engine->emit_flush = gen6_ring_flush;
	engine->irq_enable_mask = GT_BLT_USER_INTERRUPT;

	return intel_init_ring_buffer(engine);
}