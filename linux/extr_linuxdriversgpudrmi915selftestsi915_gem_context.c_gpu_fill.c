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
struct intel_engine_cs {int (* emit_bb_start ) (struct i915_vma*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ;} ;
struct TYPE_8__ {int /*<<< orphan*/  size; int /*<<< orphan*/  start; } ;
struct i915_vma {int /*<<< orphan*/  obj; TYPE_4__ node; } ;
struct i915_request {int /*<<< orphan*/  obj; TYPE_4__ node; } ;
struct i915_gem_context {TYPE_1__* ppgtt; } ;
struct i915_address_space {scalar_t__ total; int /*<<< orphan*/  i915; } ;
struct TYPE_6__ {struct i915_address_space vm; } ;
struct drm_i915_private {TYPE_2__ ggtt; } ;
struct TYPE_7__ {scalar_t__ size; int /*<<< orphan*/  dev; } ;
struct drm_i915_gem_object {TYPE_3__ base; } ;
struct TYPE_5__ {struct i915_address_space vm; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXEC_OBJECT_WRITE ; 
 int /*<<< orphan*/  GEM_BUG_ON (int) ; 
 unsigned int I915_DISPATCH_SECURE ; 
 int INTEL_GEN (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (struct i915_vma*) ; 
 unsigned int PAGE_SHIFT ; 
 int PIN_HIGH ; 
 int PIN_USER ; 
 int PTR_ERR (struct i915_vma*) ; 
 struct i915_vma* gpu_fill_dw (struct i915_vma*,unsigned int,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  i915_gem_object_set_active_reference (int /*<<< orphan*/ ) ; 
 int i915_gem_object_set_to_gtt_domain (struct drm_i915_gem_object*,int) ; 
 int /*<<< orphan*/  i915_request_add (struct i915_vma*) ; 
 struct i915_vma* i915_request_alloc (struct intel_engine_cs*,struct i915_gem_context*) ; 
 int /*<<< orphan*/  i915_request_skip (struct i915_vma*,int) ; 
 int /*<<< orphan*/  i915_vma_close (struct i915_vma*) ; 
 struct i915_vma* i915_vma_instance (struct drm_i915_gem_object*,struct i915_address_space*,int /*<<< orphan*/ *) ; 
 int i915_vma_move_to_active (struct i915_vma*,struct i915_vma*,int /*<<< orphan*/ ) ; 
 int i915_vma_pin (struct i915_vma*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  i915_vma_unpin (struct i915_vma*) ; 
 int /*<<< orphan*/  intel_engine_can_store_dword (struct intel_engine_cs*) ; 
 unsigned int real_page_count (struct drm_i915_gem_object*) ; 
 int stub1 (struct i915_vma*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int gpu_fill(struct drm_i915_gem_object *obj,
		    struct i915_gem_context *ctx,
		    struct intel_engine_cs *engine,
		    unsigned int dw)
{
	struct drm_i915_private *i915 = to_i915(obj->base.dev);
	struct i915_address_space *vm =
		ctx->ppgtt ? &ctx->ppgtt->vm : &i915->ggtt.vm;
	struct i915_request *rq;
	struct i915_vma *vma;
	struct i915_vma *batch;
	unsigned int flags;
	int err;

	GEM_BUG_ON(obj->base.size > vm->total);
	GEM_BUG_ON(!intel_engine_can_store_dword(engine));

	vma = i915_vma_instance(obj, vm, NULL);
	if (IS_ERR(vma))
		return PTR_ERR(vma);

	err = i915_gem_object_set_to_gtt_domain(obj, false);
	if (err)
		return err;

	err = i915_vma_pin(vma, 0, 0, PIN_HIGH | PIN_USER);
	if (err)
		return err;

	/* Within the GTT the huge objects maps every page onto
	 * its 1024 real pages (using phys_pfn = dma_pfn % 1024).
	 * We set the nth dword within the page using the nth
	 * mapping via the GTT - this should exercise the GTT mapping
	 * whilst checking that each context provides a unique view
	 * into the object.
	 */
	batch = gpu_fill_dw(vma,
			    (dw * real_page_count(obj)) << PAGE_SHIFT |
			    (dw * sizeof(u32)),
			    real_page_count(obj),
			    dw);
	if (IS_ERR(batch)) {
		err = PTR_ERR(batch);
		goto err_vma;
	}

	rq = i915_request_alloc(engine, ctx);
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

	err = i915_vma_move_to_active(batch, rq, 0);
	if (err)
		goto skip_request;

	err = i915_vma_move_to_active(vma, rq, EXEC_OBJECT_WRITE);
	if (err)
		goto skip_request;

	i915_gem_object_set_active_reference(batch->obj);
	i915_vma_unpin(batch);
	i915_vma_close(batch);

	i915_vma_unpin(vma);

	i915_request_add(rq);

	return 0;

skip_request:
	i915_request_skip(rq, err);
err_request:
	i915_request_add(rq);
err_batch:
	i915_vma_unpin(batch);
err_vma:
	i915_vma_unpin(vma);
	return err;
}