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
struct live_active {int /*<<< orphan*/  retired; int /*<<< orphan*/  base; } ;
struct TYPE_2__ {int /*<<< orphan*/  struct_mutex; } ;
struct drm_i915_private {TYPE_1__ drm; int /*<<< orphan*/  runtime_pm; } ;
typedef  int /*<<< orphan*/  intel_wakeref_t ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 int /*<<< orphan*/  I915_WAIT_LOCKED ; 
 scalar_t__ IS_ERR (struct live_active*) ; 
 int PTR_ERR (struct live_active*) ; 
 struct live_active* __live_active_setup (struct drm_i915_private*) ; 
 int /*<<< orphan*/  __live_put (struct live_active*) ; 
 int /*<<< orphan*/  i915_active_wait (int /*<<< orphan*/ *) ; 
 scalar_t__ igt_flush_test (struct drm_i915_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_runtime_pm_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  intel_runtime_pm_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

__attribute__((used)) static int live_active_wait(void *arg)
{
	struct drm_i915_private *i915 = arg;
	struct live_active *active;
	intel_wakeref_t wakeref;
	int err = 0;

	/* Check that we get a callback when requests retire upon waiting */

	mutex_lock(&i915->drm.struct_mutex);
	wakeref = intel_runtime_pm_get(&i915->runtime_pm);

	active = __live_active_setup(i915);
	if (IS_ERR(active)) {
		err = PTR_ERR(active);
		goto err;
	}

	i915_active_wait(&active->base);
	if (!active->retired) {
		pr_err("i915_active not retired after waiting!\n");
		err = -EINVAL;
	}

	__live_put(active);

	if (igt_flush_test(i915, I915_WAIT_LOCKED))
		err = -EIO;

err:
	intel_runtime_pm_put(&i915->runtime_pm, wakeref);
	mutex_unlock(&i915->drm.struct_mutex);

	return err;
}