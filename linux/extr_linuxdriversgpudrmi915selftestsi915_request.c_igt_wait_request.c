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
struct i915_request {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  struct_mutex; } ;
struct drm_i915_private {TYPE_1__ drm; int /*<<< orphan*/  kernel_context; int /*<<< orphan*/ * engine; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  ETIME ; 
 int HZ ; 
 int /*<<< orphan*/  I915_WAIT_LOCKED ; 
 size_t RCS ; 
 int /*<<< orphan*/  i915_request_add (struct i915_request*) ; 
 scalar_t__ i915_request_completed (struct i915_request*) ; 
 int /*<<< orphan*/  i915_request_wait (struct i915_request*,int /*<<< orphan*/ ,long const) ; 
 int /*<<< orphan*/  mock_device_flush (struct drm_i915_private*) ; 
 struct i915_request* mock_request (int /*<<< orphan*/ ,int /*<<< orphan*/ ,long const) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

__attribute__((used)) static int igt_wait_request(void *arg)
{
	const long T = HZ / 4;
	struct drm_i915_private *i915 = arg;
	struct i915_request *request;
	int err = -EINVAL;

	/* Submit a request, then wait upon it */

	mutex_lock(&i915->drm.struct_mutex);
	request = mock_request(i915->engine[RCS], i915->kernel_context, T);
	if (!request) {
		err = -ENOMEM;
		goto out_unlock;
	}

	if (i915_request_wait(request, I915_WAIT_LOCKED, 0) != -ETIME) {
		pr_err("request wait (busy query) succeeded (expected timeout before submit!)\n");
		goto out_unlock;
	}

	if (i915_request_wait(request, I915_WAIT_LOCKED, T) != -ETIME) {
		pr_err("request wait succeeded (expected timeout before submit!)\n");
		goto out_unlock;
	}

	if (i915_request_completed(request)) {
		pr_err("request completed before submit!!\n");
		goto out_unlock;
	}

	i915_request_add(request);

	if (i915_request_wait(request, I915_WAIT_LOCKED, 0) != -ETIME) {
		pr_err("request wait (busy query) succeeded (expected timeout after submit!)\n");
		goto out_unlock;
	}

	if (i915_request_completed(request)) {
		pr_err("request completed immediately!\n");
		goto out_unlock;
	}

	if (i915_request_wait(request, I915_WAIT_LOCKED, T / 2) != -ETIME) {
		pr_err("request wait succeeded (expected timeout!)\n");
		goto out_unlock;
	}

	if (i915_request_wait(request, I915_WAIT_LOCKED, T) == -ETIME) {
		pr_err("request wait timed out!\n");
		goto out_unlock;
	}

	if (!i915_request_completed(request)) {
		pr_err("request not complete after waiting!\n");
		goto out_unlock;
	}

	if (i915_request_wait(request, I915_WAIT_LOCKED, T) == -ETIME) {
		pr_err("request wait timed out when already complete!\n");
		goto out_unlock;
	}

	err = 0;
out_unlock:
	mock_device_flush(i915);
	mutex_unlock(&i915->drm.struct_mutex);
	return err;
}