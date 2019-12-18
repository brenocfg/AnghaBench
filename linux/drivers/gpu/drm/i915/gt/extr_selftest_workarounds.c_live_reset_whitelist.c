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
struct TYPE_2__ {scalar_t__ count; } ;
struct intel_engine_cs {TYPE_1__ whitelist; } ;
struct drm_i915_private {int /*<<< orphan*/  gt; struct intel_engine_cs** engine; } ;

/* Variables and functions */
 size_t RCS0 ; 
 int check_whitelist_across_reset (struct intel_engine_cs*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  do_device_reset ; 
 int /*<<< orphan*/  do_engine_reset ; 
 int /*<<< orphan*/  igt_global_reset_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  igt_global_reset_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ intel_has_gpu_reset (struct drm_i915_private*) ; 
 scalar_t__ intel_has_reset_engine (struct drm_i915_private*) ; 

__attribute__((used)) static int live_reset_whitelist(void *arg)
{
	struct drm_i915_private *i915 = arg;
	struct intel_engine_cs *engine = i915->engine[RCS0];
	int err = 0;

	/* If we reset the gpu, we should not lose the RING_NONPRIV */

	if (!engine || engine->whitelist.count == 0)
		return 0;

	igt_global_reset_lock(&i915->gt);

	if (intel_has_reset_engine(i915)) {
		err = check_whitelist_across_reset(engine,
						   do_engine_reset,
						   "engine");
		if (err)
			goto out;
	}

	if (intel_has_gpu_reset(i915)) {
		err = check_whitelist_across_reset(engine,
						   do_device_reset,
						   "device");
		if (err)
			goto out;
	}

out:
	igt_global_reset_unlock(&i915->gt);
	return err;
}