#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct i915_gpu_state {int /*<<< orphan*/  ref; int /*<<< orphan*/  simulated; } ;
struct TYPE_7__ {TYPE_2__* primary; int /*<<< orphan*/  dev; } ;
struct TYPE_5__ {int /*<<< orphan*/  lock; struct i915_gpu_state* first_error; } ;
struct drm_i915_private {TYPE_3__ drm; TYPE_1__ gpu_error; } ;
typedef  int /*<<< orphan*/  intel_engine_mask_t ;
struct TYPE_8__ {int /*<<< orphan*/  error_capture; } ;
struct TYPE_6__ {int /*<<< orphan*/  index; } ;

/* Variables and functions */
 scalar_t__ DAY_AS_SECONDS (int) ; 
 scalar_t__ DRIVER_TIMESTAMP ; 
 scalar_t__ IS_ERR (struct i915_gpu_state*) ; 
 scalar_t__ READ_ONCE (struct i915_gpu_state*) ; 
 int /*<<< orphan*/  __i915_gpu_state_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  error_msg (struct i915_gpu_state*,int /*<<< orphan*/ ,char const*) ; 
 struct i915_gpu_state* i915_capture_gpu_state (struct drm_i915_private*) ; 
 TYPE_4__ i915_modparams ; 
 scalar_t__ ktime_get_real_seconds () ; 
 int /*<<< orphan*/  pr_info (char*,...) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  xchg (int*,int) ; 

void i915_capture_error_state(struct drm_i915_private *i915,
			      intel_engine_mask_t engine_mask,
			      const char *msg)
{
	static bool warned;
	struct i915_gpu_state *error;
	unsigned long flags;

	if (!i915_modparams.error_capture)
		return;

	if (READ_ONCE(i915->gpu_error.first_error))
		return;

	error = i915_capture_gpu_state(i915);
	if (IS_ERR(error))
		return;

	dev_info(i915->drm.dev, "%s\n", error_msg(error, engine_mask, msg));

	if (!error->simulated) {
		spin_lock_irqsave(&i915->gpu_error.lock, flags);
		if (!i915->gpu_error.first_error) {
			i915->gpu_error.first_error = error;
			error = NULL;
		}
		spin_unlock_irqrestore(&i915->gpu_error.lock, flags);
	}

	if (error) {
		__i915_gpu_state_free(&error->ref);
		return;
	}

	if (!xchg(&warned, true) &&
	    ktime_get_real_seconds() - DRIVER_TIMESTAMP < DAY_AS_SECONDS(180)) {
		pr_info("GPU hangs can indicate a bug anywhere in the entire gfx stack, including userspace.\n");
		pr_info("Please file a _new_ bug report on bugs.freedesktop.org against DRI -> DRM/Intel\n");
		pr_info("drm/i915 developers can then reassign to the right component if it's not a kernel issue.\n");
		pr_info("The GPU crash dump is required to analyze GPU hangs, so please always attach it.\n");
		pr_info("GPU crash dump saved to /sys/class/drm/card%d/error\n",
			i915->drm.primary->index);
	}
}