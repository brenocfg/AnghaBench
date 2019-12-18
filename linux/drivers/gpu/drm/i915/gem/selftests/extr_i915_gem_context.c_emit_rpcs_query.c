#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct intel_context {int /*<<< orphan*/  vm; int /*<<< orphan*/  engine; } ;
struct TYPE_4__ {int /*<<< orphan*/  size; int /*<<< orphan*/  start; } ;
struct i915_vma {int /*<<< orphan*/  obj; TYPE_2__ node; TYPE_1__* engine; } ;
struct i915_request {int /*<<< orphan*/  obj; TYPE_2__ node; TYPE_1__* engine; } ;
struct drm_i915_gem_object {int dummy; } ;
struct TYPE_3__ {int (* emit_bb_start ) (struct i915_vma*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  EXEC_OBJECT_WRITE ; 
 int /*<<< orphan*/  GEM_BUG_ON (int) ; 
 scalar_t__ IS_ERR (struct i915_vma*) ; 
 int /*<<< orphan*/  PIN_USER ; 
 int PTR_ERR (struct i915_vma*) ; 
 int /*<<< orphan*/  i915_gem_object_lock (struct drm_i915_gem_object*) ; 
 int i915_gem_object_set_to_gtt_domain (struct drm_i915_gem_object*,int) ; 
 int /*<<< orphan*/  i915_gem_object_unlock (struct drm_i915_gem_object*) ; 
 int /*<<< orphan*/  i915_request_add (struct i915_vma*) ; 
 int i915_request_await_object (struct i915_vma*,int /*<<< orphan*/ ,int) ; 
 struct i915_vma* i915_request_create (struct intel_context*) ; 
 struct i915_vma* i915_request_get (struct i915_vma*) ; 
 int /*<<< orphan*/  i915_request_skip (struct i915_vma*,int) ; 
 int /*<<< orphan*/  i915_vma_close (struct i915_vma*) ; 
 struct i915_vma* i915_vma_instance (struct drm_i915_gem_object*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i915_vma_lock (struct i915_vma*) ; 
 int i915_vma_move_to_active (struct i915_vma*,struct i915_vma*,int /*<<< orphan*/ ) ; 
 int i915_vma_pin (struct i915_vma*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i915_vma_put (struct i915_vma*) ; 
 int /*<<< orphan*/  i915_vma_unlock (struct i915_vma*) ; 
 int /*<<< orphan*/  i915_vma_unpin (struct i915_vma*) ; 
 int /*<<< orphan*/  intel_engine_can_store_dword (int /*<<< orphan*/ ) ; 
 struct i915_vma* rpcs_query_batch (struct i915_vma*) ; 
 int stub1 (struct i915_vma*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
emit_rpcs_query(struct drm_i915_gem_object *obj,
		struct intel_context *ce,
		struct i915_request **rq_out)
{
	struct i915_request *rq;
	struct i915_vma *batch;
	struct i915_vma *vma;
	int err;

	GEM_BUG_ON(!intel_engine_can_store_dword(ce->engine));

	vma = i915_vma_instance(obj, ce->vm, NULL);
	if (IS_ERR(vma))
		return PTR_ERR(vma);

	i915_gem_object_lock(obj);
	err = i915_gem_object_set_to_gtt_domain(obj, false);
	i915_gem_object_unlock(obj);
	if (err)
		return err;

	err = i915_vma_pin(vma, 0, 0, PIN_USER);
	if (err)
		return err;

	batch = rpcs_query_batch(vma);
	if (IS_ERR(batch)) {
		err = PTR_ERR(batch);
		goto err_vma;
	}

	rq = i915_request_create(ce);
	if (IS_ERR(rq)) {
		err = PTR_ERR(rq);
		goto err_batch;
	}

	err = rq->engine->emit_bb_start(rq,
					batch->node.start, batch->node.size,
					0);
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

	i915_vma_unpin(batch);
	i915_vma_close(batch);
	i915_vma_put(batch);

	i915_vma_unpin(vma);

	*rq_out = i915_request_get(rq);

	i915_request_add(rq);

	return 0;

skip_request:
	i915_request_skip(rq, err);
err_request:
	i915_request_add(rq);
err_batch:
	i915_vma_unpin(batch);
	i915_vma_put(batch);
err_vma:
	i915_vma_unpin(vma);

	return err;
}