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
struct intel_engine_cs {int (* emit_init_breadcrumb ) (struct i915_vma*) ;int (* emit_bb_start ) (struct i915_vma*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  gt; } ;
struct intel_context {TYPE_4__* vm; struct intel_engine_cs* engine; } ;
struct igt_spinner {scalar_t__ gt; int /*<<< orphan*/ * batch; int /*<<< orphan*/  hws; int /*<<< orphan*/  obj; } ;
struct TYPE_7__ {int /*<<< orphan*/  start; } ;
struct TYPE_5__ {int /*<<< orphan*/  seqno; } ;
struct i915_vma {TYPE_3__ node; TYPE_2__* timeline; TYPE_1__ fence; } ;
struct i915_request {TYPE_3__ node; TYPE_2__* timeline; TYPE_1__ fence; } ;
struct TYPE_8__ {scalar_t__ gt; } ;
struct TYPE_6__ {scalar_t__ has_initial_breadcrumb; } ;

/* Variables and functions */
 struct i915_vma* ERR_CAST (struct i915_vma*) ; 
 struct i915_vma* ERR_PTR (int) ; 
 int /*<<< orphan*/  GEM_BUG_ON (int) ; 
 scalar_t__ IS_ERR (struct i915_vma*) ; 
 int /*<<< orphan*/  MI_BATCH_BUFFER_END ; 
 int MI_BATCH_BUFFER_START ; 
 int /*<<< orphan*/  MI_STORE_DWORD_IMM_GEN4 ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  PIN_USER ; 
 int PTR_ERR (struct i915_vma*) ; 
 int /*<<< orphan*/  hws_address (struct i915_vma*,struct i915_vma*) ; 
 int /*<<< orphan*/  i915_request_add (struct i915_vma*) ; 
 int /*<<< orphan*/  i915_request_skip (struct i915_vma*,int) ; 
 struct i915_vma* i915_vma_instance (int /*<<< orphan*/ ,TYPE_4__*,int /*<<< orphan*/ *) ; 
 int i915_vma_pin (struct i915_vma*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i915_vma_unpin (struct i915_vma*) ; 
 struct i915_vma* intel_context_create_request (struct intel_context*) ; 
 int /*<<< orphan*/  intel_gt_chipset_flush (int /*<<< orphan*/ ) ; 
 void* lower_32_bits (int /*<<< orphan*/ ) ; 
 int move_to_active (struct i915_vma*,struct i915_vma*,int /*<<< orphan*/ ) ; 
 int stub1 (struct i915_vma*) ; 
 int stub2 (struct i915_vma*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* upper_32_bits (int /*<<< orphan*/ ) ; 

struct i915_request *
igt_spinner_create_request(struct igt_spinner *spin,
			   struct intel_context *ce,
			   u32 arbitration_command)
{
	struct intel_engine_cs *engine = ce->engine;
	struct i915_request *rq = NULL;
	struct i915_vma *hws, *vma;
	u32 *batch;
	int err;

	GEM_BUG_ON(spin->gt != ce->vm->gt);

	vma = i915_vma_instance(spin->obj, ce->vm, NULL);
	if (IS_ERR(vma))
		return ERR_CAST(vma);

	hws = i915_vma_instance(spin->hws, ce->vm, NULL);
	if (IS_ERR(hws))
		return ERR_CAST(hws);

	err = i915_vma_pin(vma, 0, 0, PIN_USER);
	if (err)
		return ERR_PTR(err);

	err = i915_vma_pin(hws, 0, 0, PIN_USER);
	if (err)
		goto unpin_vma;

	rq = intel_context_create_request(ce);
	if (IS_ERR(rq)) {
		err = PTR_ERR(rq);
		goto unpin_hws;
	}

	err = move_to_active(vma, rq, 0);
	if (err)
		goto cancel_rq;

	err = move_to_active(hws, rq, 0);
	if (err)
		goto cancel_rq;

	batch = spin->batch;

	*batch++ = MI_STORE_DWORD_IMM_GEN4;
	*batch++ = lower_32_bits(hws_address(hws, rq));
	*batch++ = upper_32_bits(hws_address(hws, rq));
	*batch++ = rq->fence.seqno;

	*batch++ = arbitration_command;

	*batch++ = MI_BATCH_BUFFER_START | 1 << 8 | 1;
	*batch++ = lower_32_bits(vma->node.start);
	*batch++ = upper_32_bits(vma->node.start);
	*batch++ = MI_BATCH_BUFFER_END; /* not reached */

	intel_gt_chipset_flush(engine->gt);

	if (engine->emit_init_breadcrumb &&
	    rq->timeline->has_initial_breadcrumb) {
		err = engine->emit_init_breadcrumb(rq);
		if (err)
			goto cancel_rq;
	}

	err = engine->emit_bb_start(rq, vma->node.start, PAGE_SIZE, 0);

cancel_rq:
	if (err) {
		i915_request_skip(rq, err);
		i915_request_add(rq);
	}
unpin_hws:
	i915_vma_unpin(hws);
unpin_vma:
	i915_vma_unpin(vma);
	return err ? ERR_PTR(err) : rq;
}