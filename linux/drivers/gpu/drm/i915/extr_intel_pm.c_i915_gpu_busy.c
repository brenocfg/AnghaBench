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
struct TYPE_2__ {int awake; } ;
struct drm_i915_private {int /*<<< orphan*/  drm; TYPE_1__ gt; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_dev_put (int /*<<< orphan*/ *) ; 
 struct drm_i915_private* mchdev_get () ; 

bool i915_gpu_busy(void)
{
	struct drm_i915_private *i915;
	bool ret;

	i915 = mchdev_get();
	if (!i915)
		return false;

	ret = i915->gt.awake;

	drm_dev_put(&i915->drm);
	return ret;
}