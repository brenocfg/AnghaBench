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
struct intel_engine_cs {struct drm_i915_private* i915; } ;
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
 int HEAD_ADDR ; 
 int I915_READ_HEAD (struct intel_engine_cs*) ; 
 int I915_READ_MODE (struct intel_engine_cs*) ; 
 int I915_READ_TAIL (struct intel_engine_cs*) ; 
 int INTEL_GEN (struct drm_i915_private*) ; 
 int MODE_IDLE ; 
 int TAIL_ADDR ; 
 int /*<<< orphan*/  intel_runtime_pm_get_if_in_use (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_runtime_pm_put (struct drm_i915_private*) ; 

__attribute__((used)) static bool ring_is_idle(struct intel_engine_cs *engine)
{
	struct drm_i915_private *dev_priv = engine->i915;
	bool idle = true;

	/* If the whole device is asleep, the engine must be idle */
	if (!intel_runtime_pm_get_if_in_use(dev_priv))
		return true;

	/* First check that no commands are left in the ring */
	if ((I915_READ_HEAD(engine) & HEAD_ADDR) !=
	    (I915_READ_TAIL(engine) & TAIL_ADDR))
		idle = false;

	/* No bit for gen2, so assume the CS parser is idle */
	if (INTEL_GEN(dev_priv) > 2 && !(I915_READ_MODE(engine) & MODE_IDLE))
		idle = false;

	intel_runtime_pm_put(dev_priv);

	return idle;
}