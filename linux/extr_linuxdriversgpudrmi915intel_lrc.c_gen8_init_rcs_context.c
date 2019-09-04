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
struct i915_request {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int i915_gem_render_state_emit (struct i915_request*) ; 
 int intel_ctx_workarounds_emit (struct i915_request*) ; 
 int intel_rcs_context_init_mocs (struct i915_request*) ; 

__attribute__((used)) static int gen8_init_rcs_context(struct i915_request *rq)
{
	int ret;

	ret = intel_ctx_workarounds_emit(rq);
	if (ret)
		return ret;

	ret = intel_rcs_context_init_mocs(rq);
	/*
	 * Failing to program the MOCS is non-fatal.The system will not
	 * run at peak performance. So generate an error and carry on.
	 */
	if (ret)
		DRM_ERROR("MOCS failed to program: expect performance issues.\n");

	return i915_gem_render_state_emit(rq);
}