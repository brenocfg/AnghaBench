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
struct TYPE_4__ {int /*<<< orphan*/  start; } ;
struct intel_engine_pool_node {int /*<<< orphan*/  obj; struct intel_engine_pool_node* batch; TYPE_2__ node; int /*<<< orphan*/  vm; } ;
typedef  struct intel_engine_pool_node u32 ;
struct reloc_cache {int gen; scalar_t__ rq_size; struct intel_engine_pool_node* rq_cmd; struct intel_engine_pool_node* rq; scalar_t__ has_llc; } ;
struct i915_vma {int /*<<< orphan*/  obj; struct i915_vma* batch; TYPE_2__ node; int /*<<< orphan*/  vm; } ;
struct i915_request {int /*<<< orphan*/  obj; struct i915_request* batch; TYPE_2__ node; int /*<<< orphan*/  vm; } ;
struct i915_execbuffer {TYPE_1__* engine; int /*<<< orphan*/  context; struct reloc_cache reloc_cache; } ;
struct TYPE_3__ {int (* emit_bb_start ) (struct intel_engine_pool_node*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  pool; } ;

/* Variables and functions */
 int /*<<< orphan*/  I915_DISPATCH_SECURE ; 
 int /*<<< orphan*/  I915_MAP_FORCE_WB ; 
 int /*<<< orphan*/  I915_MAP_FORCE_WC ; 
 scalar_t__ IS_ERR (struct intel_engine_pool_node*) ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int PIN_NONBLOCK ; 
 int PIN_USER ; 
 int PTR_ERR (struct intel_engine_pool_node*) ; 
 struct intel_engine_pool_node* i915_gem_object_pin_map (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i915_gem_object_unpin_map (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i915_request_add (struct intel_engine_pool_node*) ; 
 int i915_request_await_object (struct intel_engine_pool_node*,int /*<<< orphan*/ ,int) ; 
 struct intel_engine_pool_node* i915_request_create (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i915_request_skip (struct intel_engine_pool_node*,int) ; 
 struct intel_engine_pool_node* i915_vma_instance (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i915_vma_lock (struct intel_engine_pool_node*) ; 
 int i915_vma_move_to_active (struct intel_engine_pool_node*,struct intel_engine_pool_node*,int /*<<< orphan*/ ) ; 
 int i915_vma_pin (struct intel_engine_pool_node*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  i915_vma_unlock (struct intel_engine_pool_node*) ; 
 int /*<<< orphan*/  i915_vma_unpin (struct intel_engine_pool_node*) ; 
 struct intel_engine_pool_node* intel_engine_pool_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int intel_engine_pool_mark_active (struct intel_engine_pool_node*,struct intel_engine_pool_node*) ; 
 int /*<<< orphan*/  intel_engine_pool_put (struct intel_engine_pool_node*) ; 
 int reloc_move_to_gpu (struct intel_engine_pool_node*,struct intel_engine_pool_node*) ; 
 int stub1 (struct intel_engine_pool_node*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int __reloc_gpu_alloc(struct i915_execbuffer *eb,
			     struct i915_vma *vma,
			     unsigned int len)
{
	struct reloc_cache *cache = &eb->reloc_cache;
	struct intel_engine_pool_node *pool;
	struct i915_request *rq;
	struct i915_vma *batch;
	u32 *cmd;
	int err;

	pool = intel_engine_pool_get(&eb->engine->pool, PAGE_SIZE);
	if (IS_ERR(pool))
		return PTR_ERR(pool);

	cmd = i915_gem_object_pin_map(pool->obj,
				      cache->has_llc ?
				      I915_MAP_FORCE_WB :
				      I915_MAP_FORCE_WC);
	if (IS_ERR(cmd)) {
		err = PTR_ERR(cmd);
		goto out_pool;
	}

	batch = i915_vma_instance(pool->obj, vma->vm, NULL);
	if (IS_ERR(batch)) {
		err = PTR_ERR(batch);
		goto err_unmap;
	}

	err = i915_vma_pin(batch, 0, 0, PIN_USER | PIN_NONBLOCK);
	if (err)
		goto err_unmap;

	rq = i915_request_create(eb->context);
	if (IS_ERR(rq)) {
		err = PTR_ERR(rq);
		goto err_unpin;
	}

	err = intel_engine_pool_mark_active(pool, rq);
	if (err)
		goto err_request;

	err = reloc_move_to_gpu(rq, vma);
	if (err)
		goto err_request;

	err = eb->engine->emit_bb_start(rq,
					batch->node.start, PAGE_SIZE,
					cache->gen > 5 ? 0 : I915_DISPATCH_SECURE);
	if (err)
		goto skip_request;

	i915_vma_lock(batch);
	err = i915_request_await_object(rq, batch->obj, false);
	if (err == 0)
		err = i915_vma_move_to_active(batch, rq, 0);
	i915_vma_unlock(batch);
	if (err)
		goto skip_request;

	rq->batch = batch;
	i915_vma_unpin(batch);

	cache->rq = rq;
	cache->rq_cmd = cmd;
	cache->rq_size = 0;

	/* Return with batch mapping (cmd) still pinned */
	goto out_pool;

skip_request:
	i915_request_skip(rq, err);
err_request:
	i915_request_add(rq);
err_unpin:
	i915_vma_unpin(batch);
err_unmap:
	i915_gem_object_unpin_map(pool->obj);
out_pool:
	intel_engine_pool_put(pool);
	return err;
}