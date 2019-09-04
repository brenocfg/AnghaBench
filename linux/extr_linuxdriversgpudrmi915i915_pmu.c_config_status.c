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
typedef  int u64 ;
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOENT ; 
 int /*<<< orphan*/  HAS_RC6 (struct drm_i915_private*) ; 
#define  I915_PMU_ACTUAL_FREQUENCY 131 
#define  I915_PMU_INTERRUPTS 130 
#define  I915_PMU_RC6_RESIDENCY 129 
#define  I915_PMU_REQUESTED_FREQUENCY 128 
 int INTEL_GEN (struct drm_i915_private*) ; 
 int /*<<< orphan*/  IS_CHERRYVIEW (struct drm_i915_private*) ; 
 int /*<<< orphan*/  IS_VALLEYVIEW (struct drm_i915_private*) ; 

__attribute__((used)) static int
config_status(struct drm_i915_private *i915, u64 config)
{
	switch (config) {
	case I915_PMU_ACTUAL_FREQUENCY:
		if (IS_VALLEYVIEW(i915) || IS_CHERRYVIEW(i915))
			/* Requires a mutex for sampling! */
			return -ENODEV;
		/* Fall-through. */
	case I915_PMU_REQUESTED_FREQUENCY:
		if (INTEL_GEN(i915) < 6)
			return -ENODEV;
		break;
	case I915_PMU_INTERRUPTS:
		break;
	case I915_PMU_RC6_RESIDENCY:
		if (!HAS_RC6(i915))
			return -ENODEV;
		break;
	default:
		return -ENOENT;
	}

	return 0;
}