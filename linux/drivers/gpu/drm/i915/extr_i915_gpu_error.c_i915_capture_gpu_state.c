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
struct i915_gpu_state {int /*<<< orphan*/  epoch; int /*<<< orphan*/  display; int /*<<< orphan*/  overlay; int /*<<< orphan*/  capture; int /*<<< orphan*/  uptime; int /*<<< orphan*/  boottime; int /*<<< orphan*/  time; struct drm_i915_private* i915; int /*<<< orphan*/  ref; } ;
struct TYPE_4__ {int /*<<< orphan*/  last_init_time; } ;
struct TYPE_3__ {int /*<<< orphan*/  first_error; } ;
struct drm_i915_private {TYPE_2__ gt; TYPE_1__ gpu_error; } ;
struct compress {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOW_FAIL ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct i915_gpu_state* ERR_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (struct i915_gpu_state*) ; 
 struct i915_gpu_state* READ_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  capture_find_epoch (struct i915_gpu_state*) ; 
 int /*<<< orphan*/  capture_finish (struct i915_gpu_state*) ; 
 int /*<<< orphan*/  capture_gen_state (struct i915_gpu_state*) ; 
 int /*<<< orphan*/  capture_params (struct i915_gpu_state*) ; 
 int /*<<< orphan*/  capture_reg_state (struct i915_gpu_state*) ; 
 int /*<<< orphan*/  capture_uc_state (struct i915_gpu_state*,struct compress*) ; 
 int /*<<< orphan*/  compress_fini (struct compress*) ; 
 int /*<<< orphan*/  compress_init (struct compress*) ; 
 int /*<<< orphan*/  gem_record_fences (struct i915_gpu_state*) ; 
 int /*<<< orphan*/  gem_record_rings (struct i915_gpu_state*,struct compress*) ; 
 int /*<<< orphan*/  i915_disable_error_state (struct drm_i915_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_display_capture_error_state (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_overlay_capture_error_state (struct drm_i915_private*) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  kfree (struct i915_gpu_state*) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ktime_get () ; 
 int /*<<< orphan*/  ktime_get_boottime () ; 
 int /*<<< orphan*/  ktime_get_real () ; 
 int /*<<< orphan*/  ktime_sub (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct i915_gpu_state* kzalloc (int,int /*<<< orphan*/ ) ; 

struct i915_gpu_state *
i915_capture_gpu_state(struct drm_i915_private *i915)
{
	struct i915_gpu_state *error;
	struct compress compress;

	/* Check if GPU capture has been disabled */
	error = READ_ONCE(i915->gpu_error.first_error);
	if (IS_ERR(error))
		return error;

	error = kzalloc(sizeof(*error), ALLOW_FAIL);
	if (!error) {
		i915_disable_error_state(i915, -ENOMEM);
		return ERR_PTR(-ENOMEM);
	}

	if (!compress_init(&compress)) {
		kfree(error);
		i915_disable_error_state(i915, -ENOMEM);
		return ERR_PTR(-ENOMEM);
	}

	kref_init(&error->ref);
	error->i915 = i915;

	error->time = ktime_get_real();
	error->boottime = ktime_get_boottime();
	error->uptime = ktime_sub(ktime_get(), i915->gt.last_init_time);
	error->capture = jiffies;

	capture_params(error);
	capture_gen_state(error);
	capture_uc_state(error, &compress);
	capture_reg_state(error);
	gem_record_fences(error);
	gem_record_rings(error, &compress);

	error->overlay = intel_overlay_capture_error_state(i915);
	error->display = intel_display_capture_error_state(i915);

	error->epoch = capture_find_epoch(error);

	capture_finish(error);
	compress_fini(&compress);

	return error;
}