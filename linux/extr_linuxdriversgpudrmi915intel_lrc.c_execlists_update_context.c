#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct intel_context {int /*<<< orphan*/  lrc_desc; int /*<<< orphan*/ * lrc_reg_state; } ;
struct i915_request {int /*<<< orphan*/  tail; int /*<<< orphan*/  ring; TYPE_3__* i915; TYPE_1__* gem_context; struct intel_context* hw_context; } ;
struct i915_hw_ppgtt {int /*<<< orphan*/  vm; } ;
struct TYPE_5__ {struct i915_hw_ppgtt* aliasing_ppgtt; } ;
struct TYPE_6__ {TYPE_2__ mm; } ;
struct TYPE_4__ {int /*<<< orphan*/  ppgtt; } ;

/* Variables and functions */
 int CTX_RING_TAIL ; 
 int /*<<< orphan*/  execlists_update_context_pdps (struct i915_hw_ppgtt*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i915_vm_is_48bit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  intel_ring_set_tail (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mb () ; 

__attribute__((used)) static u64 execlists_update_context(struct i915_request *rq)
{
	struct intel_context *ce = rq->hw_context;
	struct i915_hw_ppgtt *ppgtt =
		rq->gem_context->ppgtt ?: rq->i915->mm.aliasing_ppgtt;
	u32 *reg_state = ce->lrc_reg_state;

	reg_state[CTX_RING_TAIL+1] = intel_ring_set_tail(rq->ring, rq->tail);

	/*
	 * True 32b PPGTT with dynamic page allocation: update PDP
	 * registers and point the unallocated PDPs to scratch page.
	 * PML4 is allocated during ppgtt init, so this is not needed
	 * in 48-bit mode.
	 */
	if (ppgtt && !i915_vm_is_48bit(&ppgtt->vm))
		execlists_update_context_pdps(ppgtt, reg_state);

	/*
	 * Make sure the context image is complete before we submit it to HW.
	 *
	 * Ostensibly, writes (including the WCB) should be flushed prior to
	 * an uncached write such as our mmio register access, the empirical
	 * evidence (esp. on Braswell) suggests that the WC write into memory
	 * may not be visible to the HW prior to the completion of the UC
	 * register write and that we may begin execution from the context
	 * before its image is complete leading to invalid PD chasing.
	 *
	 * Furthermore, Braswell, at least, wants a full mb to be sure that
	 * the writes are coherent in memory (visible to the GPU) prior to
	 * execution, and not just visible to other CPUs (as is the result of
	 * wmb).
	 */
	mb();
	return ce->lrc_desc;
}