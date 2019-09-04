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
typedef  int /*<<< orphan*/  u32 ;
struct i915_gpu_state {int /*<<< orphan*/  ref; int /*<<< orphan*/  simulated; int /*<<< orphan*/  error_msg; } ;
struct TYPE_7__ {TYPE_2__* primary; } ;
struct TYPE_5__ {int /*<<< orphan*/  lock; struct i915_gpu_state* first_error; } ;
struct drm_i915_private {TYPE_3__ drm; TYPE_1__ gpu_error; } ;
struct TYPE_8__ {int /*<<< orphan*/  error_capture; } ;
struct TYPE_6__ {int /*<<< orphan*/  index; } ;

/* Variables and functions */
 scalar_t__ DAY_AS_SECONDS (int) ; 
 scalar_t__ DRIVER_TIMESTAMP ; 
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*) ; 
 int /*<<< orphan*/  DRM_INFO (char*,...) ; 
 scalar_t__ READ_ONCE (struct i915_gpu_state*) ; 
 int /*<<< orphan*/  __i915_gpu_state_free (int /*<<< orphan*/ *) ; 
 struct i915_gpu_state* i915_capture_gpu_state (struct drm_i915_private*) ; 
 int /*<<< orphan*/  i915_error_capture_msg (struct drm_i915_private*,struct i915_gpu_state*,int /*<<< orphan*/ ,char const*) ; 
 TYPE_4__ i915_modparams ; 
 scalar_t__ ktime_get_real_seconds () ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void i915_capture_error_state(struct drm_i915_private *i915,
			      u32 engine_mask,
			      const char *error_msg)
{
	static bool warned;
	struct i915_gpu_state *error;
	unsigned long flags;

	if (!i915_modparams.error_capture)
		return;

	if (READ_ONCE(i915->gpu_error.first_error))
		return;

	error = i915_capture_gpu_state(i915);
	if (!error) {
		DRM_DEBUG_DRIVER("out of memory, not capturing error state\n");
		return;
	}

	i915_error_capture_msg(i915, error, engine_mask, error_msg);
	DRM_INFO("%s\n", error->error_msg);

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

	if (!warned &&
	    ktime_get_real_seconds() - DRIVER_TIMESTAMP < DAY_AS_SECONDS(180)) {
		DRM_INFO("GPU hangs can indicate a bug anywhere in the entire gfx stack, including userspace.\n");
		DRM_INFO("Please file a _new_ bug report on bugs.freedesktop.org against DRI -> DRM/Intel\n");
		DRM_INFO("drm/i915 developers can then reassign to the right component if it's not a kernel issue.\n");
		DRM_INFO("The gpu crash dump is required to analyze gpu hangs, so please always attach it.\n");
		DRM_INFO("GPU crash dump saved to /sys/class/drm/card%d/error\n",
			 i915->drm.primary->index);
		warned = true;
	}
}