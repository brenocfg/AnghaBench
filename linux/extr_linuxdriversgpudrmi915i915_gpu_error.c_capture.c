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
struct i915_gpu_state {int /*<<< orphan*/  epoch; TYPE_2__* i915; int /*<<< orphan*/  display; int /*<<< orphan*/  overlay; int /*<<< orphan*/  capture; int /*<<< orphan*/  uptime; int /*<<< orphan*/  boottime; int /*<<< orphan*/  time; } ;
struct TYPE_4__ {int /*<<< orphan*/  last_init_time; } ;
struct TYPE_5__ {TYPE_1__ gt; } ;

/* Variables and functions */
 int /*<<< orphan*/  capture_active_buffers (struct i915_gpu_state*) ; 
 int /*<<< orphan*/  capture_find_epoch (struct i915_gpu_state*) ; 
 int /*<<< orphan*/  capture_gen_state (struct i915_gpu_state*) ; 
 int /*<<< orphan*/  capture_params (struct i915_gpu_state*) ; 
 int /*<<< orphan*/  capture_pinned_buffers (struct i915_gpu_state*) ; 
 int /*<<< orphan*/  capture_reg_state (struct i915_gpu_state*) ; 
 int /*<<< orphan*/  capture_uc_state (struct i915_gpu_state*) ; 
 int /*<<< orphan*/  gem_record_fences (struct i915_gpu_state*) ; 
 int /*<<< orphan*/  gem_record_rings (struct i915_gpu_state*) ; 
 int /*<<< orphan*/  intel_display_capture_error_state (TYPE_2__*) ; 
 int /*<<< orphan*/  intel_overlay_capture_error_state (TYPE_2__*) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  ktime_get () ; 
 int /*<<< orphan*/  ktime_get_boottime () ; 
 int /*<<< orphan*/  ktime_get_real () ; 
 int /*<<< orphan*/  ktime_sub (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int capture(void *data)
{
	struct i915_gpu_state *error = data;

	error->time = ktime_get_real();
	error->boottime = ktime_get_boottime();
	error->uptime = ktime_sub(ktime_get(),
				  error->i915->gt.last_init_time);
	error->capture = jiffies;

	capture_params(error);
	capture_gen_state(error);
	capture_uc_state(error);
	capture_reg_state(error);
	gem_record_fences(error);
	gem_record_rings(error);
	capture_active_buffers(error);
	capture_pinned_buffers(error);

	error->overlay = intel_overlay_capture_error_state(error->i915);
	error->display = intel_display_capture_error_state(error->i915);

	error->epoch = capture_find_epoch(error);

	return 0;
}