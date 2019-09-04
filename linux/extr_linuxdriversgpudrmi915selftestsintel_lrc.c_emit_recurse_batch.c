#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct spinner {int /*<<< orphan*/  i915; int /*<<< orphan*/ * batch; int /*<<< orphan*/  hws; int /*<<< orphan*/  obj; } ;
struct TYPE_10__ {int /*<<< orphan*/  start; } ;
struct i915_vma {TYPE_5__ node; int /*<<< orphan*/  obj; } ;
struct TYPE_8__ {int /*<<< orphan*/  seqno; } ;
struct i915_request {TYPE_4__* engine; TYPE_3__ fence; TYPE_2__* gem_context; } ;
struct i915_address_space {int dummy; } ;
struct TYPE_9__ {int (* emit_bb_start ) (struct i915_request*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct TYPE_7__ {TYPE_1__* ppgtt; } ;
struct TYPE_6__ {struct i915_address_space vm; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct i915_vma*) ; 
 int /*<<< orphan*/  MI_BATCH_BUFFER_END ; 
 int MI_BATCH_BUFFER_START ; 
 int /*<<< orphan*/  MI_STORE_DWORD_IMM_GEN4 ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  PIN_USER ; 
 int PTR_ERR (struct i915_vma*) ; 
 int /*<<< orphan*/  hws_address (struct i915_vma*,struct i915_request*) ; 
 int /*<<< orphan*/  i915_gem_chipset_flush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i915_gem_object_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i915_gem_object_has_active_reference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i915_gem_object_set_active_reference (int /*<<< orphan*/ ) ; 
 struct i915_vma* i915_vma_instance (int /*<<< orphan*/ ,struct i915_address_space*,int /*<<< orphan*/ *) ; 
 int i915_vma_move_to_active (struct i915_vma*,struct i915_request*,int /*<<< orphan*/ ) ; 
 int i915_vma_pin (struct i915_vma*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i915_vma_unpin (struct i915_vma*) ; 
 void* lower_32_bits (int /*<<< orphan*/ ) ; 
 int stub1 (struct i915_request*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* upper_32_bits (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int emit_recurse_batch(struct spinner *spin,
			      struct i915_request *rq,
			      u32 arbitration_command)
{
	struct i915_address_space *vm = &rq->gem_context->ppgtt->vm;
	struct i915_vma *hws, *vma;
	u32 *batch;
	int err;

	vma = i915_vma_instance(spin->obj, vm, NULL);
	if (IS_ERR(vma))
		return PTR_ERR(vma);

	hws = i915_vma_instance(spin->hws, vm, NULL);
	if (IS_ERR(hws))
		return PTR_ERR(hws);

	err = i915_vma_pin(vma, 0, 0, PIN_USER);
	if (err)
		return err;

	err = i915_vma_pin(hws, 0, 0, PIN_USER);
	if (err)
		goto unpin_vma;

	err = i915_vma_move_to_active(vma, rq, 0);
	if (err)
		goto unpin_hws;

	if (!i915_gem_object_has_active_reference(vma->obj)) {
		i915_gem_object_get(vma->obj);
		i915_gem_object_set_active_reference(vma->obj);
	}

	err = i915_vma_move_to_active(hws, rq, 0);
	if (err)
		goto unpin_hws;

	if (!i915_gem_object_has_active_reference(hws->obj)) {
		i915_gem_object_get(hws->obj);
		i915_gem_object_set_active_reference(hws->obj);
	}

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

	i915_gem_chipset_flush(spin->i915);

	err = rq->engine->emit_bb_start(rq, vma->node.start, PAGE_SIZE, 0);

unpin_hws:
	i915_vma_unpin(hws);
unpin_vma:
	i915_vma_unpin(vma);
	return err;
}