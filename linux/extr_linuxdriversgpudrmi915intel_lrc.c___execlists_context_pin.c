#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct intel_engine_cs {int dummy; } ;
struct intel_context {scalar_t__ pin_count; TYPE_5__* state; TYPE_1__* ring; int /*<<< orphan*/ * lrc_reg_state; } ;
struct i915_gem_context {int /*<<< orphan*/  ggtt_offset_bias; int /*<<< orphan*/  i915; } ;
struct TYPE_9__ {TYPE_3__* obj; } ;
struct TYPE_8__ {int /*<<< orphan*/  pin_global; } ;
struct TYPE_7__ {int /*<<< orphan*/  head; int /*<<< orphan*/  vma; } ;

/* Variables and functions */
 int CTX_RING_BUFFER_START ; 
 int CTX_RING_HEAD ; 
 struct intel_context* ERR_PTR (int) ; 
 int /*<<< orphan*/  GEM_BUG_ON (int) ; 
 int /*<<< orphan*/  I915_MAP_WB ; 
 scalar_t__ IS_ERR (void*) ; 
 int LRC_STATE_PN ; 
 int PAGE_SIZE ; 
 int PTR_ERR (void*) ; 
 int __context_pin (struct i915_gem_context*,TYPE_5__*) ; 
 int /*<<< orphan*/  __i915_vma_unpin (TYPE_5__*) ; 
 int execlists_context_deferred_alloc (struct i915_gem_context*,struct intel_engine_cs*,struct intel_context*) ; 
 int /*<<< orphan*/  i915_gem_context_get (struct i915_gem_context*) ; 
 void* i915_gem_object_pin_map (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i915_gem_object_unpin_map (TYPE_3__*) ; 
 int /*<<< orphan*/  i915_ggtt_offset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_lr_context_descriptor_update (struct i915_gem_context*,struct intel_engine_cs*,struct intel_context*) ; 
 int /*<<< orphan*/  intel_ring_offset_valid (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int intel_ring_pin (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct intel_context *
__execlists_context_pin(struct intel_engine_cs *engine,
			struct i915_gem_context *ctx,
			struct intel_context *ce)
{
	void *vaddr;
	int ret;

	ret = execlists_context_deferred_alloc(ctx, engine, ce);
	if (ret)
		goto err;
	GEM_BUG_ON(!ce->state);

	ret = __context_pin(ctx, ce->state);
	if (ret)
		goto err;

	vaddr = i915_gem_object_pin_map(ce->state->obj, I915_MAP_WB);
	if (IS_ERR(vaddr)) {
		ret = PTR_ERR(vaddr);
		goto unpin_vma;
	}

	ret = intel_ring_pin(ce->ring, ctx->i915, ctx->ggtt_offset_bias);
	if (ret)
		goto unpin_map;

	intel_lr_context_descriptor_update(ctx, engine, ce);

	ce->lrc_reg_state = vaddr + LRC_STATE_PN * PAGE_SIZE;
	ce->lrc_reg_state[CTX_RING_BUFFER_START+1] =
		i915_ggtt_offset(ce->ring->vma);
	GEM_BUG_ON(!intel_ring_offset_valid(ce->ring, ce->ring->head));
	ce->lrc_reg_state[CTX_RING_HEAD+1] = ce->ring->head;

	ce->state->obj->pin_global++;
	i915_gem_context_get(ctx);
	return ce;

unpin_map:
	i915_gem_object_unpin_map(ce->state->obj);
unpin_vma:
	__i915_vma_unpin(ce->state);
err:
	ce->pin_count = 0;
	return ERR_PTR(ret);
}