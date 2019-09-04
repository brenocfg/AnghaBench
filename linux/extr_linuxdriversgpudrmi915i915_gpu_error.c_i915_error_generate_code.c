#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct i915_gpu_state {TYPE_1__* engine; } ;
struct drm_i915_private {int dummy; } ;
struct TYPE_4__ {int instdone; } ;
struct TYPE_3__ {int ipehr; TYPE_2__ instdone; scalar_t__ hangcheck_stalled; } ;

/* Variables and functions */
 int I915_NUM_ENGINES ; 

__attribute__((used)) static uint32_t i915_error_generate_code(struct drm_i915_private *dev_priv,
					 struct i915_gpu_state *error,
					 int *engine_id)
{
	uint32_t error_code = 0;
	int i;

	/* IPEHR would be an ideal way to detect errors, as it's the gross
	 * measure of "the command that hung." However, has some very common
	 * synchronization commands which almost always appear in the case
	 * strictly a client bug. Use instdone to differentiate those some.
	 */
	for (i = 0; i < I915_NUM_ENGINES; i++) {
		if (error->engine[i].hangcheck_stalled) {
			if (engine_id)
				*engine_id = i;

			return error->engine[i].ipehr ^
			       error->engine[i].instdone.instdone;
		}
	}

	return error_code;
}