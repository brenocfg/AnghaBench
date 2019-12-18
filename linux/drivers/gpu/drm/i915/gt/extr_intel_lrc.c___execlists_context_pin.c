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
struct intel_engine_cs {int /*<<< orphan*/  i915; } ;
struct intel_context {TYPE_1__* state; void* lrc_reg_state; int /*<<< orphan*/  lrc_desc; int /*<<< orphan*/  gem_context; } ;
struct TYPE_2__ {int /*<<< orphan*/  obj; } ;

/* Variables and functions */
 int /*<<< orphan*/  GEM_BUG_ON (int) ; 
 int I915_MAP_OVERRIDE ; 
 scalar_t__ IS_ERR (void*) ; 
 int LRC_STATE_PN ; 
 int PAGE_SIZE ; 
 int PTR_ERR (void*) ; 
 int /*<<< orphan*/  __execlists_update_reg_state (struct intel_context*,struct intel_engine_cs*) ; 
 int i915_coherent_map_type (int /*<<< orphan*/ ) ; 
 int i915_gem_context_pin_hw_id (int /*<<< orphan*/ ) ; 
 void* i915_gem_object_pin_map (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  i915_gem_object_unpin_map (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i915_vma_is_pinned (TYPE_1__*) ; 
 int intel_context_active_acquire (struct intel_context*) ; 
 int /*<<< orphan*/  intel_context_active_release (struct intel_context*) ; 
 int /*<<< orphan*/  lrc_descriptor (struct intel_context*,struct intel_engine_cs*) ; 

__attribute__((used)) static int
__execlists_context_pin(struct intel_context *ce,
			struct intel_engine_cs *engine)
{
	void *vaddr;
	int ret;

	GEM_BUG_ON(!ce->state);

	ret = intel_context_active_acquire(ce);
	if (ret)
		goto err;
	GEM_BUG_ON(!i915_vma_is_pinned(ce->state));

	vaddr = i915_gem_object_pin_map(ce->state->obj,
					i915_coherent_map_type(engine->i915) |
					I915_MAP_OVERRIDE);
	if (IS_ERR(vaddr)) {
		ret = PTR_ERR(vaddr);
		goto unpin_active;
	}

	ret = i915_gem_context_pin_hw_id(ce->gem_context);
	if (ret)
		goto unpin_map;

	ce->lrc_desc = lrc_descriptor(ce, engine);
	ce->lrc_reg_state = vaddr + LRC_STATE_PN * PAGE_SIZE;
	__execlists_update_reg_state(ce, engine);

	return 0;

unpin_map:
	i915_gem_object_unpin_map(ce->state->obj);
unpin_active:
	intel_context_active_release(ce);
err:
	return ret;
}