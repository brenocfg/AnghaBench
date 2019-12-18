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
struct intel_timeline {int /*<<< orphan*/  mutex; } ;
struct intel_context {TYPE_1__* engine; } ;
struct i915_request {int dummy; } ;
struct i915_execbuffer {struct intel_context* context; TYPE_1__* engine; } ;
struct TYPE_2__ {int /*<<< orphan*/  gt; } ;

/* Variables and functions */
 int EINTR ; 
 int /*<<< orphan*/  I915_WAIT_INTERRUPTIBLE ; 
 scalar_t__ IS_ERR (struct intel_timeline*) ; 
 int /*<<< orphan*/  MAX_SCHEDULE_TIMEOUT ; 
 int PTR_ERR (struct intel_timeline*) ; 
 int __eb_pin_context (struct i915_execbuffer*,struct intel_context*) ; 
 int /*<<< orphan*/  __eb_unpin_context (struct i915_execbuffer*,struct intel_context*) ; 
 struct i915_request* eb_throttle (struct intel_context*) ; 
 int /*<<< orphan*/  i915_request_put (struct i915_request*) ; 
 scalar_t__ i915_request_wait (struct i915_request*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_context_enter (struct intel_context*) ; 
 int /*<<< orphan*/  intel_context_exit (struct intel_context*) ; 
 struct intel_timeline* intel_context_timeline_lock (struct intel_context*) ; 
 int /*<<< orphan*/  intel_context_timeline_unlock (struct intel_timeline*) ; 
 int intel_gt_terminally_wedged (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int __eb_pin_engine(struct i915_execbuffer *eb, struct intel_context *ce)
{
	struct intel_timeline *tl;
	struct i915_request *rq;
	int err;

	/*
	 * ABI: Before userspace accesses the GPU (e.g. execbuffer), report
	 * EIO if the GPU is already wedged.
	 */
	err = intel_gt_terminally_wedged(ce->engine->gt);
	if (err)
		return err;

	/*
	 * Pinning the contexts may generate requests in order to acquire
	 * GGTT space, so do this first before we reserve a seqno for
	 * ourselves.
	 */
	err = __eb_pin_context(eb, ce);
	if (err)
		return err;

	/*
	 * Take a local wakeref for preparing to dispatch the execbuf as
	 * we expect to access the hardware fairly frequently in the
	 * process, and require the engine to be kept awake between accesses.
	 * Upon dispatch, we acquire another prolonged wakeref that we hold
	 * until the timeline is idle, which in turn releases the wakeref
	 * taken on the engine, and the parent device.
	 */
	tl = intel_context_timeline_lock(ce);
	if (IS_ERR(tl)) {
		err = PTR_ERR(tl);
		goto err_unpin;
	}

	intel_context_enter(ce);
	rq = eb_throttle(ce);

	intel_context_timeline_unlock(tl);

	if (rq) {
		if (i915_request_wait(rq,
				      I915_WAIT_INTERRUPTIBLE,
				      MAX_SCHEDULE_TIMEOUT) < 0) {
			i915_request_put(rq);
			err = -EINTR;
			goto err_exit;
		}

		i915_request_put(rq);
	}

	eb->engine = ce->engine;
	eb->context = ce;
	return 0;

err_exit:
	mutex_lock(&tl->mutex);
	intel_context_exit(ce);
	intel_context_timeline_unlock(tl);
err_unpin:
	__eb_unpin_context(eb, ce);
	return err;
}