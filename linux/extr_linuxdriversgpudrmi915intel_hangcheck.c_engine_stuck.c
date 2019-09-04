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
typedef  int /*<<< orphan*/  u64 ;
typedef  int u32 ;
struct intel_engine_cs {int /*<<< orphan*/  name; int /*<<< orphan*/  id; struct drm_i915_private* i915; } ;
struct drm_i915_private {int dummy; } ;
typedef  enum intel_engine_hangcheck_action { ____Placeholder_intel_engine_hangcheck_action } intel_engine_hangcheck_action ;

/* Variables and functions */
 int /*<<< orphan*/  ALL_ENGINES ; 
 int /*<<< orphan*/  BIT (int /*<<< orphan*/ ) ; 
 int ENGINE_DEAD ; 
 int ENGINE_WAIT ; 
 int ENGINE_WAIT_KICK ; 
 int I915_READ_CTL (struct intel_engine_cs*) ; 
 int /*<<< orphan*/  I915_WRITE_CTL (struct intel_engine_cs*,int) ; 
 scalar_t__ IS_GEN (struct drm_i915_private*,int,int) ; 
 scalar_t__ IS_GEN2 (struct drm_i915_private*) ; 
 int RING_WAIT ; 
 int RING_WAIT_SEMAPHORE ; 
 int head_stuck (struct intel_engine_cs*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i915_handle_error (struct drm_i915_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int semaphore_passed (struct intel_engine_cs*) ; 

__attribute__((used)) static enum intel_engine_hangcheck_action
engine_stuck(struct intel_engine_cs *engine, u64 acthd)
{
	struct drm_i915_private *dev_priv = engine->i915;
	enum intel_engine_hangcheck_action ha;
	u32 tmp;

	ha = head_stuck(engine, acthd);
	if (ha != ENGINE_DEAD)
		return ha;

	if (IS_GEN2(dev_priv))
		return ENGINE_DEAD;

	/* Is the chip hanging on a WAIT_FOR_EVENT?
	 * If so we can simply poke the RB_WAIT bit
	 * and break the hang. This should work on
	 * all but the second generation chipsets.
	 */
	tmp = I915_READ_CTL(engine);
	if (tmp & RING_WAIT) {
		i915_handle_error(dev_priv, BIT(engine->id), 0,
				  "stuck wait on %s", engine->name);
		I915_WRITE_CTL(engine, tmp);
		return ENGINE_WAIT_KICK;
	}

	if (IS_GEN(dev_priv, 6, 7) && tmp & RING_WAIT_SEMAPHORE) {
		switch (semaphore_passed(engine)) {
		default:
			return ENGINE_DEAD;
		case 1:
			i915_handle_error(dev_priv, ALL_ENGINES, 0,
					  "stuck semaphore on %s",
					  engine->name);
			I915_WRITE_CTL(engine, tmp);
			return ENGINE_WAIT_KICK;
		case 0:
			return ENGINE_WAIT;
		}
	}

	return ENGINE_DEAD;
}