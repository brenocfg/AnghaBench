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
struct intel_engine_cs {int /*<<< orphan*/  name; int /*<<< orphan*/  mmio_base; int /*<<< orphan*/  uncore; struct drm_i915_private* i915; } ;
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,int /*<<< orphan*/ ) ; 
 int ENGINE_READ (struct intel_engine_cs*,int /*<<< orphan*/  (*) (int /*<<< orphan*/ )) ; 
 int /*<<< orphan*/  ENGINE_WRITE (struct intel_engine_cs*,int /*<<< orphan*/  (*) (int /*<<< orphan*/ ),int) ; 
 int HEAD_ADDR ; 
 int INTEL_GEN (struct drm_i915_private*) ; 
 int /*<<< orphan*/  MODE_IDLE ; 
 int /*<<< orphan*/  RING_CTL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RING_HEAD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RING_MI_MODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RING_TAIL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STOP_RING ; 
 int _MASKED_BIT_ENABLE (int /*<<< orphan*/ ) ; 
 scalar_t__ intel_wait_for_register (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static bool stop_ring(struct intel_engine_cs *engine)
{
	struct drm_i915_private *dev_priv = engine->i915;

	if (INTEL_GEN(dev_priv) > 2) {
		ENGINE_WRITE(engine,
			     RING_MI_MODE, _MASKED_BIT_ENABLE(STOP_RING));
		if (intel_wait_for_register(engine->uncore,
					    RING_MI_MODE(engine->mmio_base),
					    MODE_IDLE,
					    MODE_IDLE,
					    1000)) {
			DRM_ERROR("%s : timed out trying to stop ring\n",
				  engine->name);

			/*
			 * Sometimes we observe that the idle flag is not
			 * set even though the ring is empty. So double
			 * check before giving up.
			 */
			if (ENGINE_READ(engine, RING_HEAD) !=
			    ENGINE_READ(engine, RING_TAIL))
				return false;
		}
	}

	ENGINE_WRITE(engine, RING_HEAD, ENGINE_READ(engine, RING_TAIL));

	ENGINE_WRITE(engine, RING_HEAD, 0);
	ENGINE_WRITE(engine, RING_TAIL, 0);

	/* The ring must be empty before it is disabled */
	ENGINE_WRITE(engine, RING_CTL, 0);

	return (ENGINE_READ(engine, RING_HEAD) & HEAD_ADDR) == 0;
}