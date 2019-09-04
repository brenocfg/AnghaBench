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
struct intel_engine_cs {int /*<<< orphan*/  i915; } ;
typedef  enum drm_i915_pmu_engine_sample { ____Placeholder_drm_i915_pmu_engine_sample } drm_i915_pmu_engine_sample ;

/* Variables and functions */
 int ENODEV ; 
 int ENOENT ; 
#define  I915_SAMPLE_BUSY 130 
#define  I915_SAMPLE_SEMA 129 
#define  I915_SAMPLE_WAIT 128 
 int INTEL_GEN (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
engine_event_status(struct intel_engine_cs *engine,
		    enum drm_i915_pmu_engine_sample sample)
{
	switch (sample) {
	case I915_SAMPLE_BUSY:
	case I915_SAMPLE_WAIT:
		break;
	case I915_SAMPLE_SEMA:
		if (INTEL_GEN(engine->i915) < 6)
			return -ENODEV;
		break;
	default:
		return -ENOENT;
	}

	return 0;
}