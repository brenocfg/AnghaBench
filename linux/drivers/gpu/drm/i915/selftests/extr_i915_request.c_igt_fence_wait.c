#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct i915_request {int /*<<< orphan*/  fence; } ;
struct TYPE_4__ {int /*<<< orphan*/  struct_mutex; } ;
struct drm_i915_private {TYPE_2__ drm; TYPE_1__** engine; } ;
struct TYPE_3__ {int /*<<< orphan*/  kernel_context; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  ETIME ; 
 int HZ ; 
 size_t RCS0 ; 
 scalar_t__ dma_fence_is_signaled (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dma_fence_wait_timeout (int /*<<< orphan*/ *,int,long const) ; 
 int /*<<< orphan*/  i915_request_add (struct i915_request*) ; 
 int /*<<< orphan*/  mock_device_flush (struct drm_i915_private*) ; 
 struct i915_request* mock_request (int /*<<< orphan*/ ,long const) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

__attribute__((used)) static int igt_fence_wait(void *arg)
{
	const long T = HZ / 4;
	struct drm_i915_private *i915 = arg;
	struct i915_request *request;
	int err = -EINVAL;

	/* Submit a request, treat it as a fence and wait upon it */

	mutex_lock(&i915->drm.struct_mutex);
	request = mock_request(i915->engine[RCS0]->kernel_context, T);
	if (!request) {
		err = -ENOMEM;
		goto out_locked;
	}

	if (dma_fence_wait_timeout(&request->fence, false, T) != -ETIME) {
		pr_err("fence wait success before submit (expected timeout)!\n");
		goto out_locked;
	}

	i915_request_add(request);
	mutex_unlock(&i915->drm.struct_mutex);

	if (dma_fence_is_signaled(&request->fence)) {
		pr_err("fence signaled immediately!\n");
		goto out_device;
	}

	if (dma_fence_wait_timeout(&request->fence, false, T / 2) != -ETIME) {
		pr_err("fence wait success after submit (expected timeout)!\n");
		goto out_device;
	}

	if (dma_fence_wait_timeout(&request->fence, false, T) <= 0) {
		pr_err("fence wait timed out (expected success)!\n");
		goto out_device;
	}

	if (!dma_fence_is_signaled(&request->fence)) {
		pr_err("fence unsignaled after waiting!\n");
		goto out_device;
	}

	if (dma_fence_wait_timeout(&request->fence, false, T) <= 0) {
		pr_err("fence wait timed out when complete (expected success)!\n");
		goto out_device;
	}

	err = 0;
out_device:
	mutex_lock(&i915->drm.struct_mutex);
out_locked:
	mock_device_flush(i915);
	mutex_unlock(&i915->drm.struct_mutex);
	return err;
}