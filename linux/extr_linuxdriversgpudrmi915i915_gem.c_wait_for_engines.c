#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct drm_i915_private {TYPE_1__ drm; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  GEM_TRACE_DUMP () ; 
 int /*<<< orphan*/  I915_IDLE_ENGINES_TIMEOUT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  i915_gem_set_wedged (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_engines_are_idle (struct drm_i915_private*) ; 
 scalar_t__ wait_for (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int wait_for_engines(struct drm_i915_private *i915)
{
	if (wait_for(intel_engines_are_idle(i915), I915_IDLE_ENGINES_TIMEOUT)) {
		dev_err(i915->drm.dev,
			"Failed to idle engines, declaring wedged!\n");
		GEM_TRACE_DUMP();
		i915_gem_set_wedged(i915);
		return -EIO;
	}

	return 0;
}