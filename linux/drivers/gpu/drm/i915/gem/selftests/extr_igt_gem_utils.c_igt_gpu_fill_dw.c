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
struct intel_engine_cs {int (* emit_bb_start ) (struct i915_vma*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ;TYPE_2__* gt; } ;
struct TYPE_6__ {int /*<<< orphan*/  size; int /*<<< orphan*/  start; } ;
struct i915_vma {scalar_t__ size; int /*<<< orphan*/  obj; TYPE_3__ node; } ;
struct i915_request {scalar_t__ size; int /*<<< orphan*/  obj; TYPE_3__ node; } ;
struct i915_gem_context {int /*<<< orphan*/  vm; } ;
struct i915_address_space {scalar_t__ total; int /*<<< orphan*/  i915; } ;
struct TYPE_5__ {TYPE_1__* ggtt; } ;
struct TYPE_4__ {struct i915_address_space vm; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXEC_OBJECT_WRITE ; 
 int /*<<< orphan*/  GEM_BUG_ON (int) ; 
 unsigned int I915_DISPATCH_SECURE ; 
 int INTEL_GEN (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (struct i915_vma*) ; 
 int PTR_ERR (struct i915_vma*) ; 
 int /*<<< orphan*/  i915_request_add (struct i915_vma*) ; 
 int i915_request_await_object (struct i915_vma*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  i915_request_skip (struct i915_vma*,int) ; 
 int /*<<< orphan*/  i915_vma_close (struct i915_vma*) ; 
 int /*<<< orphan*/  i915_vma_is_pinned (struct i915_vma*) ; 
 int /*<<< orphan*/  i915_vma_lock (struct i915_vma*) ; 
 int i915_vma_move_to_active (struct i915_vma*,struct i915_vma*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i915_vma_put (struct i915_vma*) ; 
 int /*<<< orphan*/  i915_vma_unlock (struct i915_vma*) ; 
 int /*<<< orphan*/  i915_vma_unpin (struct i915_vma*) ; 
 struct i915_vma* igt_emit_store_dw (struct i915_vma*,int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ ) ; 
 struct i915_vma* igt_request_alloc (struct i915_gem_context*,struct intel_engine_cs*) ; 
 int /*<<< orphan*/  intel_engine_can_store_dword (struct intel_engine_cs*) ; 
 int stub1 (struct i915_vma*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 

int igt_gpu_fill_dw(struct i915_vma *vma,
		    struct i915_gem_context *ctx,
		    struct intel_engine_cs *engine,
		    u64 offset,
		    unsigned long count,
		    u32 val)
{
	struct i915_address_space *vm = ctx->vm ?: &engine->gt->ggtt->vm;
	struct i915_request *rq;
	struct i915_vma *batch;
	unsigned int flags;
	int err;

	GEM_BUG_ON(vma->size > vm->total);
	GEM_BUG_ON(!intel_engine_can_store_dword(engine));
	GEM_BUG_ON(!i915_vma_is_pinned(vma));

	batch = igt_emit_store_dw(vma, offset, count, val);
	if (IS_ERR(batch))
		return PTR_ERR(batch);

	rq = igt_request_alloc(ctx, engine);
	if (IS_ERR(rq)) {
		err = PTR_ERR(rq);
		goto err_batch;
	}

	flags = 0;
	if (INTEL_GEN(vm->i915) <= 5)
		flags |= I915_DISPATCH_SECURE;

	err = engine->emit_bb_start(rq,
				    batch->node.start, batch->node.size,
				    flags);
	if (err)
		goto err_request;

	i915_vma_lock(batch);
	err = i915_request_await_object(rq, batch->obj, false);
	if (err == 0)
		err = i915_vma_move_to_active(batch, rq, 0);
	i915_vma_unlock(batch);
	if (err)
		goto skip_request;

	i915_vma_lock(vma);
	err = i915_request_await_object(rq, vma->obj, true);
	if (err == 0)
		err = i915_vma_move_to_active(vma, rq, EXEC_OBJECT_WRITE);
	i915_vma_unlock(vma);
	if (err)
		goto skip_request;

	i915_request_add(rq);

	i915_vma_unpin(batch);
	i915_vma_close(batch);
	i915_vma_put(batch);

	return 0;

skip_request:
	i915_request_skip(rq, err);
err_request:
	i915_request_add(rq);
err_batch:
	i915_vma_unpin(batch);
	i915_vma_put(batch);
	return err;
}