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
struct intel_engine_cs {int /*<<< orphan*/  name; int /*<<< orphan*/  mmio_base; struct drm_i915_private* i915; } ;
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,int /*<<< orphan*/ ) ; 
 int HEAD_ADDR ; 
 int I915_READ_HEAD (struct intel_engine_cs*) ; 
 int I915_READ_TAIL (struct intel_engine_cs*) ; 
 int /*<<< orphan*/  I915_WRITE_CTL (struct intel_engine_cs*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_WRITE_HEAD (struct intel_engine_cs*,int) ; 
 int /*<<< orphan*/  I915_WRITE_MODE (struct intel_engine_cs*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_WRITE_TAIL (struct intel_engine_cs*,int /*<<< orphan*/ ) ; 
 int INTEL_GEN (struct drm_i915_private*) ; 
 int /*<<< orphan*/  MODE_IDLE ; 
 int /*<<< orphan*/  RING_MI_MODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STOP_RING ; 
 int /*<<< orphan*/  _MASKED_BIT_ENABLE (int /*<<< orphan*/ ) ; 
 scalar_t__ intel_wait_for_register (struct drm_i915_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static bool stop_ring(struct intel_engine_cs *engine)
{
	struct drm_i915_private *dev_priv = engine->i915;

	if (INTEL_GEN(dev_priv) > 2) {
		I915_WRITE_MODE(engine, _MASKED_BIT_ENABLE(STOP_RING));
		if (intel_wait_for_register(dev_priv,
					    RING_MI_MODE(engine->mmio_base),
					    MODE_IDLE,
					    MODE_IDLE,
					    1000)) {
			DRM_ERROR("%s : timed out trying to stop ring\n",
				  engine->name);
			/* Sometimes we observe that the idle flag is not
			 * set even though the ring is empty. So double
			 * check before giving up.
			 */
			if (I915_READ_HEAD(engine) != I915_READ_TAIL(engine))
				return false;
		}
	}

	I915_WRITE_HEAD(engine, I915_READ_TAIL(engine));

	I915_WRITE_HEAD(engine, 0);
	I915_WRITE_TAIL(engine, 0);

	/* The ring must be empty before it is disabled */
	I915_WRITE_CTL(engine, 0);

	return (I915_READ_HEAD(engine) & HEAD_ADDR) == 0;
}