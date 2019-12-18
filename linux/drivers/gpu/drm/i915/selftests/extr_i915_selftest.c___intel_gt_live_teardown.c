#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct intel_gt {TYPE_2__* i915; } ;
struct TYPE_4__ {int /*<<< orphan*/  struct_mutex; } ;
struct TYPE_5__ {TYPE_1__ drm; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  I915_WAIT_LOCKED ; 
 int /*<<< orphan*/  i915_gem_drain_freed_objects (TYPE_2__*) ; 
 scalar_t__ igt_flush_test (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int __intel_gt_live_teardown(int err, void *data)
{
	struct intel_gt *gt = data;

	mutex_lock(&gt->i915->drm.struct_mutex);
	if (igt_flush_test(gt->i915, I915_WAIT_LOCKED))
		err = -EIO;
	mutex_unlock(&gt->i915->drm.struct_mutex);

	i915_gem_drain_freed_objects(gt->i915);

	return err;
}