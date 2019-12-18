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
struct intel_engine_cs {int /*<<< orphan*/  i915; int /*<<< orphan*/  mmio_base; } ;

/* Variables and functions */
 int ENGINE_READ (struct intel_engine_cs*,int /*<<< orphan*/ ) ; 
 int HEAD_ADDR ; 
 scalar_t__ I915_SELFTEST_ONLY (int) ; 
 int INTEL_GEN (int /*<<< orphan*/ ) ; 
 int MODE_IDLE ; 
 int /*<<< orphan*/  RING_HEAD ; 
 int /*<<< orphan*/  RING_MI_MODE ; 
 int /*<<< orphan*/  RING_TAIL ; 
 int TAIL_ADDR ; 
 int /*<<< orphan*/  intel_engine_pm_get_if_awake (struct intel_engine_cs*) ; 
 int /*<<< orphan*/  intel_engine_pm_put (struct intel_engine_cs*) ; 

__attribute__((used)) static bool ring_is_idle(struct intel_engine_cs *engine)
{
	bool idle = true;

	if (I915_SELFTEST_ONLY(!engine->mmio_base))
		return true;

	if (!intel_engine_pm_get_if_awake(engine))
		return true;

	/* First check that no commands are left in the ring */
	if ((ENGINE_READ(engine, RING_HEAD) & HEAD_ADDR) !=
	    (ENGINE_READ(engine, RING_TAIL) & TAIL_ADDR))
		idle = false;

	/* No bit for gen2, so assume the CS parser is idle */
	if (INTEL_GEN(engine->i915) > 2 &&
	    !(ENGINE_READ(engine, RING_MI_MODE) & MODE_IDLE))
		idle = false;

	intel_engine_pm_put(engine);

	return idle;
}