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
struct i915_request {int /*<<< orphan*/  i915; } ;
struct drm_i915_mocs_table {int dummy; } ;

/* Variables and functions */
 int emit_mocs_control_table (struct i915_request*,struct drm_i915_mocs_table*) ; 
 int emit_mocs_l3cc_table (struct i915_request*,struct drm_i915_mocs_table*) ; 
 scalar_t__ get_mocs_settings (int /*<<< orphan*/ ,struct drm_i915_mocs_table*) ; 

int intel_rcs_context_init_mocs(struct i915_request *rq)
{
	struct drm_i915_mocs_table t;
	int ret;

	if (get_mocs_settings(rq->i915, &t)) {
		/* Program the RCS control registers */
		ret = emit_mocs_control_table(rq, &t);
		if (ret)
			return ret;

		/* Now program the l3cc registers */
		ret = emit_mocs_l3cc_table(rq, &t);
		if (ret)
			return ret;
	}

	return 0;
}