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
struct intel_engine_cs {int /*<<< orphan*/  mmio_base; struct drm_i915_private* i915; } ;
struct drm_i915_private {int dummy; } ;
struct drm_i915_error_engine {void** semaphore_mboxes; } ;

/* Variables and functions */
 scalar_t__ HAS_VEBOX (struct drm_i915_private*) ; 
 void* I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RING_SYNC_0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RING_SYNC_1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RING_SYNC_2 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void gen6_record_semaphore_state(struct intel_engine_cs *engine,
					struct drm_i915_error_engine *ee)
{
	struct drm_i915_private *dev_priv = engine->i915;

	ee->semaphore_mboxes[0] = I915_READ(RING_SYNC_0(engine->mmio_base));
	ee->semaphore_mboxes[1] = I915_READ(RING_SYNC_1(engine->mmio_base));
	if (HAS_VEBOX(dev_priv))
		ee->semaphore_mboxes[2] =
			I915_READ(RING_SYNC_2(engine->mmio_base));
}