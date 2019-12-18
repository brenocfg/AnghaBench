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
struct drm_i915_private {int /*<<< orphan*/  gt; } ;

/* Variables and functions */
 int intel_gt_terminally_wedged (int /*<<< orphan*/ *) ; 

int __i915_live_setup(void *data)
{
	struct drm_i915_private *i915 = data;

	return intel_gt_terminally_wedged(&i915->gt);
}