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
struct i915_gpu_state {unsigned long capture; struct drm_i915_error_engine* engine; } ;
struct drm_i915_error_engine {unsigned long hangcheck_timestamp; scalar_t__ hangcheck_stalled; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct drm_i915_error_engine*) ; 
 scalar_t__ time_before (unsigned long,unsigned long) ; 

__attribute__((used)) static unsigned long capture_find_epoch(const struct i915_gpu_state *error)
{
	unsigned long epoch = error->capture;
	int i;

	for (i = 0; i < ARRAY_SIZE(error->engine); i++) {
		const struct drm_i915_error_engine *ee = &error->engine[i];

		if (ee->hangcheck_stalled &&
		    time_before(ee->hangcheck_timestamp, epoch))
			epoch = ee->hangcheck_timestamp;
	}

	return epoch;
}