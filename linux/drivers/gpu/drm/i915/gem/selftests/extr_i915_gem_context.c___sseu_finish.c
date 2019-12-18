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
typedef  int /*<<< orphan*/  u32 ;
struct intel_context {TYPE_2__* engine; } ;
struct igt_spinner {int dummy; } ;
struct drm_i915_gem_object {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  slice_mask; } ;
struct TYPE_4__ {int /*<<< orphan*/  i915; struct intel_context* kernel_context; TYPE_1__ sseu; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAX_SCHEDULE_TIMEOUT ; 
 unsigned int TEST_IDLE ; 
 unsigned int TEST_RESET ; 
 int __check_rpcs (char const*,int /*<<< orphan*/ ,int,unsigned int,char*,char*) ; 
 int __read_slice_count (struct intel_context*,struct drm_i915_gem_object*,struct igt_spinner*,int /*<<< orphan*/ *) ; 
 unsigned int hweight32 (int /*<<< orphan*/ ) ; 
 int i915_gem_wait_for_idle (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  igt_spinner_end (struct igt_spinner*) ; 
 int intel_engine_reset (TYPE_2__*,char*) ; 

__attribute__((used)) static int
__sseu_finish(const char *name,
	      unsigned int flags,
	      struct intel_context *ce,
	      struct drm_i915_gem_object *obj,
	      unsigned int expected,
	      struct igt_spinner *spin)
{
	unsigned int slices = hweight32(ce->engine->sseu.slice_mask);
	u32 rpcs = 0;
	int ret = 0;

	if (flags & TEST_RESET) {
		ret = intel_engine_reset(ce->engine, "sseu");
		if (ret)
			goto out;
	}

	ret = __read_slice_count(ce, obj,
				 flags & TEST_RESET ? NULL : spin, &rpcs);
	ret = __check_rpcs(name, rpcs, ret, expected, "Context", "!");
	if (ret)
		goto out;

	ret = __read_slice_count(ce->engine->kernel_context, obj, NULL, &rpcs);
	ret = __check_rpcs(name, rpcs, ret, slices, "Kernel context", "!");

out:
	if (spin)
		igt_spinner_end(spin);

	if ((flags & TEST_IDLE) && ret == 0) {
		ret = i915_gem_wait_for_idle(ce->engine->i915,
					     0, MAX_SCHEDULE_TIMEOUT);
		if (ret)
			return ret;

		ret = __read_slice_count(ce, obj, NULL, &rpcs);
		ret = __check_rpcs(name, rpcs, ret, expected,
				   "Context", " after idle!");
	}

	return ret;
}