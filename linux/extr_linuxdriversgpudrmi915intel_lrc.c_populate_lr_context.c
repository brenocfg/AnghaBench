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
typedef  int /*<<< orphan*/  u32 ;
struct intel_ring {int dummy; } ;
struct intel_engine_cs {int /*<<< orphan*/  i915; struct drm_i915_gem_object* default_state; int /*<<< orphan*/  context_size; } ;
struct i915_gem_context {TYPE_2__* i915; } ;
struct TYPE_3__ {int dirty; } ;
struct drm_i915_gem_object {TYPE_1__ mm; } ;
struct TYPE_4__ {struct i915_gem_context* preempt_context; } ;

/* Variables and functions */
 int CTX_CONTEXT_CONTROL ; 
 int CTX_CTRL_ENGINE_CTX_RESTORE_INHIBIT ; 
 int CTX_CTRL_ENGINE_CTX_SAVE_INHIBIT ; 
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*,...) ; 
 int /*<<< orphan*/  I915_MAP_WB ; 
 int INTEL_GEN (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (void*) ; 
 int LRC_HEADER_PAGES ; 
 int LRC_STATE_PN ; 
 int PAGE_SIZE ; 
 int PTR_ERR (void*) ; 
 int /*<<< orphan*/  _MASKED_BIT_ENABLE (int) ; 
 int /*<<< orphan*/  execlists_init_reg_state (int /*<<< orphan*/ *,struct i915_gem_context*,struct intel_engine_cs*,struct intel_ring*) ; 
 void* i915_gem_object_pin_map (struct drm_i915_gem_object*,int /*<<< orphan*/ ) ; 
 int i915_gem_object_set_to_cpu_domain (struct drm_i915_gem_object*,int) ; 
 int /*<<< orphan*/  i915_gem_object_unpin_map (struct drm_i915_gem_object*) ; 
 int /*<<< orphan*/  memcpy (void*,void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
populate_lr_context(struct i915_gem_context *ctx,
		    struct drm_i915_gem_object *ctx_obj,
		    struct intel_engine_cs *engine,
		    struct intel_ring *ring)
{
	void *vaddr;
	u32 *regs;
	int ret;

	ret = i915_gem_object_set_to_cpu_domain(ctx_obj, true);
	if (ret) {
		DRM_DEBUG_DRIVER("Could not set to CPU domain\n");
		return ret;
	}

	vaddr = i915_gem_object_pin_map(ctx_obj, I915_MAP_WB);
	if (IS_ERR(vaddr)) {
		ret = PTR_ERR(vaddr);
		DRM_DEBUG_DRIVER("Could not map object pages! (%d)\n", ret);
		return ret;
	}
	ctx_obj->mm.dirty = true;

	if (engine->default_state) {
		/*
		 * We only want to copy over the template context state;
		 * skipping over the headers reserved for GuC communication,
		 * leaving those as zero.
		 */
		const unsigned long start = LRC_HEADER_PAGES * PAGE_SIZE;
		void *defaults;

		defaults = i915_gem_object_pin_map(engine->default_state,
						   I915_MAP_WB);
		if (IS_ERR(defaults)) {
			ret = PTR_ERR(defaults);
			goto err_unpin_ctx;
		}

		memcpy(vaddr + start, defaults + start, engine->context_size);
		i915_gem_object_unpin_map(engine->default_state);
	}

	/* The second page of the context object contains some fields which must
	 * be set up prior to the first execution. */
	regs = vaddr + LRC_STATE_PN * PAGE_SIZE;
	execlists_init_reg_state(regs, ctx, engine, ring);
	if (!engine->default_state)
		regs[CTX_CONTEXT_CONTROL + 1] |=
			_MASKED_BIT_ENABLE(CTX_CTRL_ENGINE_CTX_RESTORE_INHIBIT);
	if (ctx == ctx->i915->preempt_context && INTEL_GEN(engine->i915) < 11)
		regs[CTX_CONTEXT_CONTROL + 1] |=
			_MASKED_BIT_ENABLE(CTX_CTRL_ENGINE_CTX_RESTORE_INHIBIT |
					   CTX_CTRL_ENGINE_CTX_SAVE_INHIBIT);

err_unpin_ctx:
	i915_gem_object_unpin_map(ctx_obj);
	return ret;
}