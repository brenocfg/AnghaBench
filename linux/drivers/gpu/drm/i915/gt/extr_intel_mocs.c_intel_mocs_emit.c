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
struct i915_request {TYPE_1__* engine; int /*<<< orphan*/  i915; } ;
struct drm_i915_mocs_table {int dummy; } ;
struct TYPE_2__ {scalar_t__ class; int /*<<< orphan*/  gt; } ;

/* Variables and functions */
 scalar_t__ HAS_GLOBAL_MOCS_REGISTERS (int /*<<< orphan*/ ) ; 
 scalar_t__ RENDER_CLASS ; 
 int emit_mocs_control_table (struct i915_request*,struct drm_i915_mocs_table*) ; 
 int emit_mocs_l3cc_table (struct i915_request*,struct drm_i915_mocs_table*) ; 
 scalar_t__ get_mocs_settings (int /*<<< orphan*/ ,struct drm_i915_mocs_table*) ; 

int intel_mocs_emit(struct i915_request *rq)
{
	struct drm_i915_mocs_table t;
	int ret;

	if (HAS_GLOBAL_MOCS_REGISTERS(rq->i915) ||
	    rq->engine->class != RENDER_CLASS)
		return 0;

	if (get_mocs_settings(rq->engine->gt, &t)) {
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