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
typedef  int u32 ;
struct intel_engine_cs {int (* emit_bb_start ) (struct i915_vma*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ;} ;
struct TYPE_2__ {int /*<<< orphan*/  size; int /*<<< orphan*/  start; } ;
struct i915_vma {TYPE_1__ node; int /*<<< orphan*/  obj; } ;
struct i915_request {TYPE_1__ node; int /*<<< orphan*/  obj; } ;
struct i915_gem_context {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXEC_OBJECT_WRITE ; 
 int /*<<< orphan*/  GEM_BUG_ON (int) ; 
 scalar_t__ IS_ERR (struct i915_vma*) ; 
 int PTR_ERR (struct i915_vma*) ; 
 struct i915_vma* gpu_write_dw (struct i915_vma*,int,int) ; 
 int /*<<< orphan*/  i915_gem_object_set_active_reference (int /*<<< orphan*/ ) ; 
 int i915_gem_object_set_to_gtt_domain (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  i915_request_add (struct i915_vma*) ; 
 struct i915_vma* i915_request_alloc (struct intel_engine_cs*,struct i915_gem_context*) ; 
 int /*<<< orphan*/  i915_request_skip (struct i915_vma*,int) ; 
 int /*<<< orphan*/  i915_vma_close (struct i915_vma*) ; 
 int i915_vma_move_to_active (struct i915_vma*,struct i915_vma*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i915_vma_unpin (struct i915_vma*) ; 
 int /*<<< orphan*/  intel_engine_can_store_dword (struct intel_engine_cs*) ; 
 int stub1 (struct i915_vma*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int gpu_write(struct i915_vma *vma,
		     struct i915_gem_context *ctx,
		     struct intel_engine_cs *engine,
		     u32 dword,
		     u32 value)
{
	struct i915_request *rq;
	struct i915_vma *batch;
	int flags = 0;
	int err;

	GEM_BUG_ON(!intel_engine_can_store_dword(engine));

	err = i915_gem_object_set_to_gtt_domain(vma->obj, true);
	if (err)
		return err;

	rq = i915_request_alloc(engine, ctx);
	if (IS_ERR(rq))
		return PTR_ERR(rq);

	batch = gpu_write_dw(vma, dword * sizeof(u32), value);
	if (IS_ERR(batch)) {
		err = PTR_ERR(batch);
		goto err_request;
	}

	err = i915_vma_move_to_active(batch, rq, 0);
	if (err)
		goto err_request;

	i915_gem_object_set_active_reference(batch->obj);
	i915_vma_unpin(batch);
	i915_vma_close(batch);

	err = engine->emit_bb_start(rq,
				    batch->node.start, batch->node.size,
				    flags);
	if (err)
		goto err_request;

	err = i915_vma_move_to_active(vma, rq, EXEC_OBJECT_WRITE);
	if (err)
		i915_request_skip(rq, err);

err_request:
	i915_request_add(rq);

	return err;
}