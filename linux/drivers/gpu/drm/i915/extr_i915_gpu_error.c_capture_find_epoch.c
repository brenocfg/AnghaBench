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
struct drm_i915_error_engine {unsigned long hangcheck_timestamp; struct drm_i915_error_engine* next; } ;

/* Variables and functions */
 scalar_t__ time_before (unsigned long,unsigned long) ; 

__attribute__((used)) static unsigned long capture_find_epoch(const struct i915_gpu_state *error)
{
	const struct drm_i915_error_engine *ee;
	unsigned long epoch = error->capture;

	for (ee = error->engine; ee; ee = ee->next) {
		if (ee->hangcheck_timestamp &&
		    time_before(ee->hangcheck_timestamp, epoch))
			epoch = ee->hangcheck_timestamp;
	}

	return epoch;
}