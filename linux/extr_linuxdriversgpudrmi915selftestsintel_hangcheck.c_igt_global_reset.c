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
struct TYPE_5__ {int /*<<< orphan*/  flags; } ;
struct TYPE_4__ {int /*<<< orphan*/  struct_mutex; } ;
struct drm_i915_private {TYPE_2__ gpu_error; TYPE_1__ drm; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALL_ENGINES ; 
 int EINVAL ; 
 int EIO ; 
 int /*<<< orphan*/  GEM_BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_RESET_HANDOFF ; 
 int /*<<< orphan*/  global_reset_lock (struct drm_i915_private*) ; 
 int /*<<< orphan*/  global_reset_unlock (struct drm_i915_private*) ; 
 int /*<<< orphan*/  i915_reset (struct drm_i915_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 unsigned int i915_reset_count (TYPE_2__*) ; 
 scalar_t__ i915_terminally_wedged (TYPE_2__*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int igt_global_reset(void *arg)
{
	struct drm_i915_private *i915 = arg;
	unsigned int reset_count;
	int err = 0;

	/* Check that we can issue a global GPU reset */

	global_reset_lock(i915);
	set_bit(I915_RESET_HANDOFF, &i915->gpu_error.flags);

	mutex_lock(&i915->drm.struct_mutex);
	reset_count = i915_reset_count(&i915->gpu_error);

	i915_reset(i915, ALL_ENGINES, NULL);

	if (i915_reset_count(&i915->gpu_error) == reset_count) {
		pr_err("No GPU reset recorded!\n");
		err = -EINVAL;
	}
	mutex_unlock(&i915->drm.struct_mutex);

	GEM_BUG_ON(test_bit(I915_RESET_HANDOFF, &i915->gpu_error.flags));
	global_reset_unlock(i915);

	if (i915_terminally_wedged(&i915->gpu_error))
		err = -EIO;

	return err;
}