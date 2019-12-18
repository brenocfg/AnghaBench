#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
struct intel_renderstate {int batch_size; int aux_size; TYPE_4__* obj; TYPE_4__* vma; int /*<<< orphan*/  aux_offset; int /*<<< orphan*/  batch_offset; TYPE_3__* rodata; } ;
struct intel_engine_cs {int (* emit_bb_start ) (struct i915_request*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ;TYPE_2__* gt; int /*<<< orphan*/  i915; } ;
struct i915_request {int /*<<< orphan*/  i915; struct intel_engine_cs* engine; } ;
struct TYPE_19__ {int /*<<< orphan*/  obj; } ;
struct TYPE_18__ {int batch_items; } ;
struct TYPE_17__ {TYPE_1__* ggtt; } ;
struct TYPE_16__ {int /*<<< orphan*/  vm; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  I915_DISPATCH_SECURE ; 
 scalar_t__ IS_ERR (TYPE_4__*) ; 
 int PAGE_SIZE ; 
 int PIN_GLOBAL ; 
 int PIN_HIGH ; 
 int PTR_ERR (TYPE_4__*) ; 
 TYPE_4__* i915_gem_object_create_internal (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  i915_gem_object_put (TYPE_4__*) ; 
 int i915_request_await_object (struct i915_request*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  i915_vma_close (TYPE_4__*) ; 
 TYPE_4__* i915_vma_instance (TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i915_vma_lock (TYPE_4__*) ; 
 int i915_vma_move_to_active (TYPE_4__*,struct i915_request*,int /*<<< orphan*/ ) ; 
 int i915_vma_pin (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  i915_vma_unlock (TYPE_4__*) ; 
 int /*<<< orphan*/  i915_vma_unpin (TYPE_4__*) ; 
 TYPE_3__* render_state_get_rodata (struct intel_engine_cs*) ; 
 int render_state_setup (struct intel_renderstate*,int /*<<< orphan*/ ) ; 
 int stub1 (struct i915_request*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int stub2 (struct i915_request*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

int intel_renderstate_emit(struct i915_request *rq)
{
	struct intel_engine_cs *engine = rq->engine;
	struct intel_renderstate so = {}; /* keep the compiler happy */
	int err;

	so.rodata = render_state_get_rodata(engine);
	if (!so.rodata)
		return 0;

	if (so.rodata->batch_items * 4 > PAGE_SIZE)
		return -EINVAL;

	so.obj = i915_gem_object_create_internal(engine->i915, PAGE_SIZE);
	if (IS_ERR(so.obj))
		return PTR_ERR(so.obj);

	so.vma = i915_vma_instance(so.obj, &engine->gt->ggtt->vm, NULL);
	if (IS_ERR(so.vma)) {
		err = PTR_ERR(so.vma);
		goto err_obj;
	}

	err = i915_vma_pin(so.vma, 0, 0, PIN_GLOBAL | PIN_HIGH);
	if (err)
		goto err_vma;

	err = render_state_setup(&so, rq->i915);
	if (err)
		goto err_unpin;

	err = engine->emit_bb_start(rq,
				    so.batch_offset, so.batch_size,
				    I915_DISPATCH_SECURE);
	if (err)
		goto err_unpin;

	if (so.aux_size > 8) {
		err = engine->emit_bb_start(rq,
					    so.aux_offset, so.aux_size,
					    I915_DISPATCH_SECURE);
		if (err)
			goto err_unpin;
	}

	i915_vma_lock(so.vma);
	err = i915_request_await_object(rq, so.vma->obj, false);
	if (err == 0)
		err = i915_vma_move_to_active(so.vma, rq, 0);
	i915_vma_unlock(so.vma);
err_unpin:
	i915_vma_unpin(so.vma);
err_vma:
	i915_vma_close(so.vma);
err_obj:
	i915_gem_object_put(so.obj);
	return err;
}