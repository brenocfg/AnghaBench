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
struct i915_gpu_state {struct drm_i915_error_engine* engine; struct drm_i915_error_engine* active_bo_count; struct drm_i915_error_engine* active_bo; struct drm_i915_error_engine* active_vm; } ;
struct drm_i915_error_engine {scalar_t__ vm; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct drm_i915_error_engine*) ; 
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int /*<<< orphan*/  gem_capture_vm (struct i915_gpu_state*,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void capture_active_buffers(struct i915_gpu_state *error)
{
	int cnt = 0, i, j;

	BUILD_BUG_ON(ARRAY_SIZE(error->engine) > ARRAY_SIZE(error->active_bo));
	BUILD_BUG_ON(ARRAY_SIZE(error->active_bo) != ARRAY_SIZE(error->active_vm));
	BUILD_BUG_ON(ARRAY_SIZE(error->active_bo) != ARRAY_SIZE(error->active_bo_count));

	/* Scan each engine looking for unique active contexts/vm */
	for (i = 0; i < ARRAY_SIZE(error->engine); i++) {
		struct drm_i915_error_engine *ee = &error->engine[i];
		bool found;

		if (!ee->vm)
			continue;

		found = false;
		for (j = 0; j < i && !found; j++)
			found = error->engine[j].vm == ee->vm;
		if (!found)
			gem_capture_vm(error, ee->vm, cnt++);
	}
}