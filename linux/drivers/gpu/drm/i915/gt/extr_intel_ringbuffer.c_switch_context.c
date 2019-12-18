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
typedef  int /*<<< orphan*/  u32 ;
struct intel_engine_cs {scalar_t__ id; int mask; int (* emit_flush ) (struct i915_request*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  i915; } ;
struct i915_request {int /*<<< orphan*/  gem_context; TYPE_1__* hw_context; int /*<<< orphan*/  i915; struct intel_engine_cs* engine; } ;
struct i915_ppgtt {int pd_dirty_engines; } ;
struct i915_address_space {int dummy; } ;
struct TYPE_2__ {scalar_t__ state; } ;

/* Variables and functions */
 scalar_t__ BCS0 ; 
 int /*<<< orphan*/  EMIT_FLUSH ; 
 int /*<<< orphan*/  EMIT_INVALIDATE ; 
 int /*<<< orphan*/  GEM_BUG_ON (int) ; 
 int HAS_EXECLISTS (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_VALLEYVIEW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MI_FORCE_RESTORE ; 
 int /*<<< orphan*/  MI_RESTORE_INHIBIT ; 
 scalar_t__ RCS0 ; 
 int flush_pd_dir (struct i915_request*) ; 
 scalar_t__ i915_gem_context_is_kernel (int /*<<< orphan*/ ) ; 
 struct i915_ppgtt* i915_vm_to_ppgtt (struct i915_address_space*) ; 
 int load_pd_dir (struct i915_request*,struct i915_ppgtt*) ; 
 int mi_set_context (struct i915_request*,int /*<<< orphan*/ ) ; 
 int remap_l3 (struct i915_request*) ; 
 int stub1 (struct i915_request*,int /*<<< orphan*/ ) ; 
 int stub2 (struct i915_request*,int /*<<< orphan*/ ) ; 
 int stub3 (struct i915_request*,int /*<<< orphan*/ ) ; 
 struct i915_address_space* vm_alias (TYPE_1__*) ; 

__attribute__((used)) static int switch_context(struct i915_request *rq)
{
	struct intel_engine_cs *engine = rq->engine;
	struct i915_address_space *vm = vm_alias(rq->hw_context);
	unsigned int unwind_mm = 0;
	u32 hw_flags = 0;
	int ret;

	GEM_BUG_ON(HAS_EXECLISTS(rq->i915));

	if (vm) {
		struct i915_ppgtt *ppgtt = i915_vm_to_ppgtt(vm);
		int loops;

		/*
		 * Baytail takes a little more convincing that it really needs
		 * to reload the PD between contexts. It is not just a little
		 * longer, as adding more stalls after the load_pd_dir (i.e.
		 * adding a long loop around flush_pd_dir) is not as effective
		 * as reloading the PD umpteen times. 32 is derived from
		 * experimentation (gem_exec_parallel/fds) and has no good
		 * explanation.
		 */
		loops = 1;
		if (engine->id == BCS0 && IS_VALLEYVIEW(engine->i915))
			loops = 32;

		do {
			ret = load_pd_dir(rq, ppgtt);
			if (ret)
				goto err;
		} while (--loops);

		if (ppgtt->pd_dirty_engines & engine->mask) {
			unwind_mm = engine->mask;
			ppgtt->pd_dirty_engines &= ~unwind_mm;
			hw_flags = MI_FORCE_RESTORE;
		}
	}

	if (rq->hw_context->state) {
		GEM_BUG_ON(engine->id != RCS0);

		/*
		 * The kernel context(s) is treated as pure scratch and is not
		 * expected to retain any state (as we sacrifice it during
		 * suspend and on resume it may be corrupted). This is ok,
		 * as nothing actually executes using the kernel context; it
		 * is purely used for flushing user contexts.
		 */
		if (i915_gem_context_is_kernel(rq->gem_context))
			hw_flags = MI_RESTORE_INHIBIT;

		ret = mi_set_context(rq, hw_flags);
		if (ret)
			goto err_mm;
	}

	if (vm) {
		ret = engine->emit_flush(rq, EMIT_INVALIDATE);
		if (ret)
			goto err_mm;

		ret = flush_pd_dir(rq);
		if (ret)
			goto err_mm;

		/*
		 * Not only do we need a full barrier (post-sync write) after
		 * invalidating the TLBs, but we need to wait a little bit
		 * longer. Whether this is merely delaying us, or the
		 * subsequent flush is a key part of serialising with the
		 * post-sync op, this extra pass appears vital before a
		 * mm switch!
		 */
		ret = engine->emit_flush(rq, EMIT_INVALIDATE);
		if (ret)
			goto err_mm;

		ret = engine->emit_flush(rq, EMIT_FLUSH);
		if (ret)
			goto err_mm;
	}

	ret = remap_l3(rq);
	if (ret)
		goto err_mm;

	return 0;

err_mm:
	if (unwind_mm)
		i915_vm_to_ppgtt(vm)->pd_dirty_engines |= unwind_mm;
err:
	return ret;
}