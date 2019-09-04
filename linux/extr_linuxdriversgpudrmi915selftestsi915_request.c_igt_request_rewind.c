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
struct i915_request {int /*<<< orphan*/  global_seqno; TYPE_1__* engine; } ;
struct i915_gem_context {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  struct_mutex; } ;
struct drm_i915_private {TYPE_2__ drm; int /*<<< orphan*/ * engine; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* submit_request ) (struct i915_request*) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  ETIME ; 
 int HZ ; 
 size_t RCS ; 
 int /*<<< orphan*/  i915_request_add (struct i915_request*) ; 
 scalar_t__ i915_request_completed (struct i915_request*) ; 
 int /*<<< orphan*/  i915_request_get (struct i915_request*) ; 
 int /*<<< orphan*/  i915_request_put (struct i915_request*) ; 
 int /*<<< orphan*/  i915_request_wait (struct i915_request*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  intel_engine_get_seqno (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mock_cancel_request (struct i915_request*) ; 
 struct i915_gem_context* mock_context (struct drm_i915_private*,char*) ; 
 int /*<<< orphan*/  mock_context_close (struct i915_gem_context*) ; 
 int /*<<< orphan*/  mock_device_flush (struct drm_i915_private*) ; 
 struct i915_request* mock_request (int /*<<< orphan*/ ,struct i915_gem_context*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  stub1 (struct i915_request*) ; 

__attribute__((used)) static int igt_request_rewind(void *arg)
{
	struct drm_i915_private *i915 = arg;
	struct i915_request *request, *vip;
	struct i915_gem_context *ctx[2];
	int err = -EINVAL;

	mutex_lock(&i915->drm.struct_mutex);
	ctx[0] = mock_context(i915, "A");
	request = mock_request(i915->engine[RCS], ctx[0], 2 * HZ);
	if (!request) {
		err = -ENOMEM;
		goto err_context_0;
	}

	i915_request_get(request);
	i915_request_add(request);

	ctx[1] = mock_context(i915, "B");
	vip = mock_request(i915->engine[RCS], ctx[1], 0);
	if (!vip) {
		err = -ENOMEM;
		goto err_context_1;
	}

	/* Simulate preemption by manual reordering */
	if (!mock_cancel_request(request)) {
		pr_err("failed to cancel request (already executed)!\n");
		i915_request_add(vip);
		goto err_context_1;
	}
	i915_request_get(vip);
	i915_request_add(vip);
	rcu_read_lock();
	request->engine->submit_request(request);
	rcu_read_unlock();

	mutex_unlock(&i915->drm.struct_mutex);

	if (i915_request_wait(vip, 0, HZ) == -ETIME) {
		pr_err("timed out waiting for high priority request, vip.seqno=%d, current seqno=%d\n",
		       vip->global_seqno, intel_engine_get_seqno(i915->engine[RCS]));
		goto err;
	}

	if (i915_request_completed(request)) {
		pr_err("low priority request already completed\n");
		goto err;
	}

	err = 0;
err:
	i915_request_put(vip);
	mutex_lock(&i915->drm.struct_mutex);
err_context_1:
	mock_context_close(ctx[1]);
	i915_request_put(request);
err_context_0:
	mock_context_close(ctx[0]);
	mock_device_flush(i915);
	mutex_unlock(&i915->drm.struct_mutex);
	return err;
}