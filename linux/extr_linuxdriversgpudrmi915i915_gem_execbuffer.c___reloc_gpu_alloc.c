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
struct TYPE_4__ {int /*<<< orphan*/  start; } ;
struct i915_vma {struct i915_vma* batch; int /*<<< orphan*/  resv; TYPE_1__ node; TYPE_2__* obj; int /*<<< orphan*/  vm; } ;
typedef  struct i915_vma u32 ;
struct reloc_cache {int gen; scalar_t__ rq_size; struct i915_vma* rq_cmd; struct i915_vma* rq; scalar_t__ has_llc; } ;
struct i915_request {struct i915_request* batch; int /*<<< orphan*/  resv; TYPE_1__ node; TYPE_2__* obj; int /*<<< orphan*/  vm; } ;
struct i915_execbuffer {TYPE_3__* engine; int /*<<< orphan*/  ctx; struct reloc_cache reloc_cache; } ;
struct drm_i915_gem_object {struct drm_i915_gem_object* batch; int /*<<< orphan*/  resv; TYPE_1__ node; TYPE_2__* obj; int /*<<< orphan*/  vm; } ;
struct TYPE_6__ {int (* emit_bb_start ) (struct i915_vma*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  batch_pool; } ;
struct TYPE_5__ {int write_domain; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXEC_OBJECT_WRITE ; 
 int /*<<< orphan*/  GEM_BUG_ON (int) ; 
 int /*<<< orphan*/  I915_DISPATCH_SECURE ; 
 int I915_GEM_DOMAIN_CPU ; 
 int /*<<< orphan*/  I915_MAP_FORCE_WB ; 
 int /*<<< orphan*/  I915_MAP_FORCE_WC ; 
 scalar_t__ IS_ERR (struct i915_vma*) ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int PIN_NONBLOCK ; 
 int PIN_USER ; 
 int PTR_ERR (struct i915_vma*) ; 
 struct i915_vma* i915_gem_batch_pool_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct i915_vma* i915_gem_object_pin_map (struct i915_vma*,int /*<<< orphan*/ ) ; 
 int i915_gem_object_set_to_wc_domain (struct i915_vma*,int) ; 
 int /*<<< orphan*/  i915_gem_object_unpin_map (struct i915_vma*) ; 
 int /*<<< orphan*/  i915_gem_object_unpin_pages (struct i915_vma*) ; 
 int /*<<< orphan*/  i915_request_add (struct i915_vma*) ; 
 struct i915_vma* i915_request_alloc (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int i915_request_await_object (struct i915_vma*,TYPE_2__*,int) ; 
 int /*<<< orphan*/  i915_request_skip (struct i915_vma*,int) ; 
 struct i915_vma* i915_vma_instance (struct i915_vma*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int i915_vma_move_to_active (struct i915_vma*,struct i915_vma*,int /*<<< orphan*/ ) ; 
 int i915_vma_pin (struct i915_vma*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  i915_vma_unpin (struct i915_vma*) ; 
 int /*<<< orphan*/  reservation_object_test_signaled_rcu (int /*<<< orphan*/ ,int) ; 
 int stub1 (struct i915_vma*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int __reloc_gpu_alloc(struct i915_execbuffer *eb,
			     struct i915_vma *vma,
			     unsigned int len)
{
	struct reloc_cache *cache = &eb->reloc_cache;
	struct drm_i915_gem_object *obj;
	struct i915_request *rq;
	struct i915_vma *batch;
	u32 *cmd;
	int err;

	GEM_BUG_ON(vma->obj->write_domain & I915_GEM_DOMAIN_CPU);

	obj = i915_gem_batch_pool_get(&eb->engine->batch_pool, PAGE_SIZE);
	if (IS_ERR(obj))
		return PTR_ERR(obj);

	cmd = i915_gem_object_pin_map(obj,
				      cache->has_llc ?
				      I915_MAP_FORCE_WB :
				      I915_MAP_FORCE_WC);
	i915_gem_object_unpin_pages(obj);
	if (IS_ERR(cmd))
		return PTR_ERR(cmd);

	err = i915_gem_object_set_to_wc_domain(obj, false);
	if (err)
		goto err_unmap;

	batch = i915_vma_instance(obj, vma->vm, NULL);
	if (IS_ERR(batch)) {
		err = PTR_ERR(batch);
		goto err_unmap;
	}

	err = i915_vma_pin(batch, 0, 0, PIN_USER | PIN_NONBLOCK);
	if (err)
		goto err_unmap;

	rq = i915_request_alloc(eb->engine, eb->ctx);
	if (IS_ERR(rq)) {
		err = PTR_ERR(rq);
		goto err_unpin;
	}

	err = i915_request_await_object(rq, vma->obj, true);
	if (err)
		goto err_request;

	err = eb->engine->emit_bb_start(rq,
					batch->node.start, PAGE_SIZE,
					cache->gen > 5 ? 0 : I915_DISPATCH_SECURE);
	if (err)
		goto err_request;

	GEM_BUG_ON(!reservation_object_test_signaled_rcu(batch->resv, true));
	err = i915_vma_move_to_active(batch, rq, 0);
	if (err)
		goto skip_request;

	err = i915_vma_move_to_active(vma, rq, EXEC_OBJECT_WRITE);
	if (err)
		goto skip_request;

	rq->batch = batch;
	i915_vma_unpin(batch);

	cache->rq = rq;
	cache->rq_cmd = cmd;
	cache->rq_size = 0;

	/* Return with batch mapping (cmd) still pinned */
	return 0;

skip_request:
	i915_request_skip(rq, err);
err_request:
	i915_request_add(rq);
err_unpin:
	i915_vma_unpin(batch);
err_unmap:
	i915_gem_object_unpin_map(obj);
	return err;
}