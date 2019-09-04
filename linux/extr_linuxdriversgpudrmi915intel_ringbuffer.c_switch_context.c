#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct intel_engine_cs {scalar_t__ id; } ;
struct i915_request {TYPE_3__* hw_context; TYPE_4__* i915; struct i915_gem_context* gem_context; struct intel_engine_cs* engine; } ;
struct i915_hw_ppgtt {int pd_dirty_rings; } ;
struct i915_gem_context {int remap_slice; int /*<<< orphan*/  ppgtt; } ;
struct TYPE_6__ {int /*<<< orphan*/  struct_mutex; } ;
struct TYPE_5__ {struct i915_hw_ppgtt* aliasing_ppgtt; } ;
struct TYPE_8__ {TYPE_2__ drm; TYPE_1__ mm; } ;
struct TYPE_7__ {scalar_t__ state; } ;

/* Variables and functions */
 int BIT (int) ; 
 int /*<<< orphan*/  GEM_BUG_ON (int) ; 
 int HAS_EXECLISTS (TYPE_4__*) ; 
 int MAX_L3_SLICES ; 
 int /*<<< orphan*/  MI_FORCE_RESTORE ; 
 int /*<<< orphan*/  MI_RESTORE_INHIBIT ; 
 scalar_t__ RCS ; 
 int flush_pd_dir (struct i915_request*) ; 
 scalar_t__ i915_gem_context_is_kernel (struct i915_gem_context*) ; 
 int intel_engine_flag (struct intel_engine_cs*) ; 
 int load_pd_dir (struct i915_request*,struct i915_hw_ppgtt*) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int mi_set_context (struct i915_request*,int /*<<< orphan*/ ) ; 
 int remap_l3 (struct i915_request*,int) ; 

__attribute__((used)) static int switch_context(struct i915_request *rq)
{
	struct intel_engine_cs *engine = rq->engine;
	struct i915_gem_context *ctx = rq->gem_context;
	struct i915_hw_ppgtt *ppgtt = ctx->ppgtt ?: rq->i915->mm.aliasing_ppgtt;
	unsigned int unwind_mm = 0;
	u32 hw_flags = 0;
	int ret, i;

	lockdep_assert_held(&rq->i915->drm.struct_mutex);
	GEM_BUG_ON(HAS_EXECLISTS(rq->i915));

	if (ppgtt) {
		ret = load_pd_dir(rq, ppgtt);
		if (ret)
			goto err;

		if (intel_engine_flag(engine) & ppgtt->pd_dirty_rings) {
			unwind_mm = intel_engine_flag(engine);
			ppgtt->pd_dirty_rings &= ~unwind_mm;
			hw_flags = MI_FORCE_RESTORE;
		}
	}

	if (rq->hw_context->state) {
		GEM_BUG_ON(engine->id != RCS);

		/*
		 * The kernel context(s) is treated as pure scratch and is not
		 * expected to retain any state (as we sacrifice it during
		 * suspend and on resume it may be corrupted). This is ok,
		 * as nothing actually executes using the kernel context; it
		 * is purely used for flushing user contexts.
		 */
		if (i915_gem_context_is_kernel(ctx))
			hw_flags = MI_RESTORE_INHIBIT;

		ret = mi_set_context(rq, hw_flags);
		if (ret)
			goto err_mm;
	}

	if (ppgtt) {
		ret = flush_pd_dir(rq);
		if (ret)
			goto err_mm;
	}

	if (ctx->remap_slice) {
		for (i = 0; i < MAX_L3_SLICES; i++) {
			if (!(ctx->remap_slice & BIT(i)))
				continue;

			ret = remap_l3(rq, i);
			if (ret)
				goto err_mm;
		}

		ctx->remap_slice = 0;
	}

	return 0;

err_mm:
	if (unwind_mm)
		ppgtt->pd_dirty_rings |= unwind_mm;
err:
	return ret;
}