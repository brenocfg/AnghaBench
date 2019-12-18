#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u64 ;
struct intel_engine_cs {scalar_t__ class; scalar_t__ instance; int /*<<< orphan*/  i915; } ;
struct intel_context {int /*<<< orphan*/  state; int /*<<< orphan*/  vm; struct i915_gem_context* gem_context; } ;
struct i915_gem_context {scalar_t__ hw_id; } ;

/* Variables and functions */
 scalar_t__ BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int /*<<< orphan*/  GEM_BUG_ON (int) ; 
 int GEN11_ENGINE_CLASS_SHIFT ; 
 int GEN11_ENGINE_INSTANCE_SHIFT ; 
 scalar_t__ GEN11_MAX_CONTEXT_HW_ID ; 
 int GEN11_SW_CTX_ID_SHIFT ; 
 int /*<<< orphan*/  GEN11_SW_CTX_ID_WIDTH ; 
 int GEN8_CTX_ADDRESSING_MODE_SHIFT ; 
 int GEN8_CTX_ID_SHIFT ; 
 int /*<<< orphan*/  GEN8_CTX_ID_WIDTH ; 
 int GEN8_CTX_L3LLC_COHERENT ; 
 int GEN8_CTX_PRIVILEGE ; 
 int GEN8_CTX_VALID ; 
 int INTEL_GEN (int /*<<< orphan*/ ) ; 
 int INTEL_LEGACY_32B_CONTEXT ; 
 int INTEL_LEGACY_64B_CONTEXT ; 
 scalar_t__ IS_GEN (int /*<<< orphan*/ ,int) ; 
 int LRC_HEADER_PAGES ; 
 scalar_t__ MAX_CONTEXT_HW_ID ; 
 int PAGE_SIZE ; 
 int i915_ggtt_offset (int /*<<< orphan*/ ) ; 
 scalar_t__ i915_vm_is_4lvl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u64
lrc_descriptor(struct intel_context *ce, struct intel_engine_cs *engine)
{
	struct i915_gem_context *ctx = ce->gem_context;
	u64 desc;

	BUILD_BUG_ON(MAX_CONTEXT_HW_ID > (BIT(GEN8_CTX_ID_WIDTH)));
	BUILD_BUG_ON(GEN11_MAX_CONTEXT_HW_ID > (BIT(GEN11_SW_CTX_ID_WIDTH)));

	desc = INTEL_LEGACY_32B_CONTEXT;
	if (i915_vm_is_4lvl(ce->vm))
		desc = INTEL_LEGACY_64B_CONTEXT;
	desc <<= GEN8_CTX_ADDRESSING_MODE_SHIFT;

	desc |= GEN8_CTX_VALID | GEN8_CTX_PRIVILEGE;
	if (IS_GEN(engine->i915, 8))
		desc |= GEN8_CTX_L3LLC_COHERENT;

	desc |= i915_ggtt_offset(ce->state) + LRC_HEADER_PAGES * PAGE_SIZE;
								/* bits 12-31 */
	/*
	 * The following 32bits are copied into the OA reports (dword 2).
	 * Consider updating oa_get_render_ctx_id in i915_perf.c when changing
	 * anything below.
	 */
	if (INTEL_GEN(engine->i915) >= 11) {
		GEM_BUG_ON(ctx->hw_id >= BIT(GEN11_SW_CTX_ID_WIDTH));
		desc |= (u64)ctx->hw_id << GEN11_SW_CTX_ID_SHIFT;
								/* bits 37-47 */

		desc |= (u64)engine->instance << GEN11_ENGINE_INSTANCE_SHIFT;
								/* bits 48-53 */

		/* TODO: decide what to do with SW counter (bits 55-60) */

		desc |= (u64)engine->class << GEN11_ENGINE_CLASS_SHIFT;
								/* bits 61-63 */
	} else {
		GEM_BUG_ON(ctx->hw_id >= BIT(GEN8_CTX_ID_WIDTH));
		desc |= (u64)ctx->hw_id << GEN8_CTX_ID_SHIFT;	/* bits 32-52 */
	}

	return desc;
}