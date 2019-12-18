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
typedef  unsigned int u32 ;
struct intel_context {TYPE_1__* engine; } ;
struct igt_spinner {int dummy; } ;
struct i915_request {int dummy; } ;
struct drm_i915_gem_object {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  i915; } ;

/* Variables and functions */
 unsigned int GEN11_RPCS_S_CNT_MASK ; 
 unsigned int GEN11_RPCS_S_CNT_SHIFT ; 
 unsigned int GEN8_RPCS_S_CNT_MASK ; 
 unsigned int GEN8_RPCS_S_CNT_SHIFT ; 
 int /*<<< orphan*/  I915_MAP_WB ; 
 int INTEL_GEN (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (unsigned int*) ; 
 int /*<<< orphan*/  MAX_SCHEDULE_TIMEOUT ; 
 long PTR_ERR (unsigned int*) ; 
 long emit_rpcs_query (struct drm_i915_gem_object*,struct intel_context*,struct i915_request**) ; 
 unsigned int* i915_gem_object_pin_map (struct drm_i915_gem_object*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i915_gem_object_unpin_map (struct drm_i915_gem_object*) ; 
 int /*<<< orphan*/  i915_request_put (struct i915_request*) ; 
 long i915_request_wait (struct i915_request*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  igt_spinner_end (struct igt_spinner*) ; 

__attribute__((used)) static int
__read_slice_count(struct intel_context *ce,
		   struct drm_i915_gem_object *obj,
		   struct igt_spinner *spin,
		   u32 *rpcs)
{
	struct i915_request *rq = NULL;
	u32 s_mask, s_shift;
	unsigned int cnt;
	u32 *buf, val;
	long ret;

	ret = emit_rpcs_query(obj, ce, &rq);
	if (ret)
		return ret;

	if (spin)
		igt_spinner_end(spin);

	ret = i915_request_wait(rq, 0, MAX_SCHEDULE_TIMEOUT);
	i915_request_put(rq);
	if (ret < 0)
		return ret;

	buf = i915_gem_object_pin_map(obj, I915_MAP_WB);
	if (IS_ERR(buf)) {
		ret = PTR_ERR(buf);
		return ret;
	}

	if (INTEL_GEN(ce->engine->i915) >= 11) {
		s_mask = GEN11_RPCS_S_CNT_MASK;
		s_shift = GEN11_RPCS_S_CNT_SHIFT;
	} else {
		s_mask = GEN8_RPCS_S_CNT_MASK;
		s_shift = GEN8_RPCS_S_CNT_SHIFT;
	}

	val = *buf;
	cnt = (val & s_mask) >> s_shift;
	*rpcs = val;

	i915_gem_object_unpin_map(obj);

	return cnt;
}