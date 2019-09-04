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
 int /*<<< orphan*/  ASYNC_FLIP_PERF_DISABLE ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INSTPM ; 
 int /*<<< orphan*/  INSTPM_FORCE_ORDERING ; 
 int /*<<< orphan*/  MI_MODE ; 
 int /*<<< orphan*/  _MASKED_BIT_ENABLE (int /*<<< orphan*/ ) ; 
 int gen8_init_common_ring (struct intel_engine_cs*) ; 
 int /*<<< orphan*/  intel_whitelist_workarounds_apply (struct intel_engine_cs*) ; 

__attribute__((used)) static int gen8_init_render_ring(struct intel_engine_cs *engine)
{
	struct drm_i915_private *dev_priv = engine->i915;
	int ret;

	ret = gen8_init_common_ring(engine);
	if (ret)
		return ret;

	intel_whitelist_workarounds_apply(engine);

	/* We need to disable the AsyncFlip performance optimisations in order
	 * to use MI_WAIT_FOR_EVENT within the CS. It should already be
	 * programmed to '1' on all products.
	 *
	 * WaDisableAsyncFlipPerfMode:snb,ivb,hsw,vlv,bdw,chv
	 */
	I915_WRITE(MI_MODE, _MASKED_BIT_ENABLE(ASYNC_FLIP_PERF_DISABLE));

	I915_WRITE(INSTPM, _MASKED_BIT_ENABLE(INSTPM_FORCE_ORDERING));

	return 0;
}