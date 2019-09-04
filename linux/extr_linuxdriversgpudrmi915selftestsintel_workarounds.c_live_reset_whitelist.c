#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct whitelist {int /*<<< orphan*/  count; } ;
struct intel_engine_cs {scalar_t__ id; } ;
struct i915_gpu_error {int /*<<< orphan*/  flags; } ;
struct drm_i915_private {struct i915_gpu_error gpu_error; struct intel_engine_cs** engine; } ;

/* Variables and functions */
 scalar_t__ I915_RESET_BACKOFF ; 
 scalar_t__ I915_RESET_ENGINE ; 
 size_t RCS ; 
 int check_whitelist_across_reset (struct intel_engine_cs*,int /*<<< orphan*/ ,struct whitelist*,char*) ; 
 int /*<<< orphan*/  clear_bit (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  do_device_reset ; 
 int /*<<< orphan*/  do_engine_reset ; 
 scalar_t__ intel_has_gpu_reset (struct drm_i915_private*) ; 
 scalar_t__ intel_has_reset_engine (struct drm_i915_private*) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  whitelist_build (struct intel_engine_cs*,struct whitelist*) ; 

__attribute__((used)) static int live_reset_whitelist(void *arg)
{
	struct drm_i915_private *i915 = arg;
	struct intel_engine_cs *engine = i915->engine[RCS];
	struct i915_gpu_error *error = &i915->gpu_error;
	struct whitelist w;
	int err = 0;

	/* If we reset the gpu, we should not lose the RING_NONPRIV */

	if (!engine)
		return 0;

	if (!whitelist_build(engine, &w))
		return 0;

	pr_info("Checking %d whitelisted registers (RING_NONPRIV)\n", w.count);

	set_bit(I915_RESET_BACKOFF, &error->flags);
	set_bit(I915_RESET_ENGINE + engine->id, &error->flags);

	if (intel_has_reset_engine(i915)) {
		err = check_whitelist_across_reset(engine,
						   do_engine_reset, &w,
						   "engine");
		if (err)
			goto out;
	}

	if (intel_has_gpu_reset(i915)) {
		err = check_whitelist_across_reset(engine,
						   do_device_reset, &w,
						   "device");
		if (err)
			goto out;
	}

out:
	clear_bit(I915_RESET_ENGINE + engine->id, &error->flags);
	clear_bit(I915_RESET_BACKOFF, &error->flags);
	return err;
}