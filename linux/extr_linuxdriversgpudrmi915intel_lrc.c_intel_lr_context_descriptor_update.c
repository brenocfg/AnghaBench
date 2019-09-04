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
struct intel_engine_cs {scalar_t__ class; scalar_t__ instance; } ;
struct intel_context {int lrc_desc; int /*<<< orphan*/  state; } ;
struct i915_gem_context {int desc_template; scalar_t__ hw_id; int /*<<< orphan*/  i915; } ;

/* Variables and functions */
 scalar_t__ BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int /*<<< orphan*/  GEM_BUG_ON (int) ; 
 int GEN11_ENGINE_CLASS_SHIFT ; 
 int GEN11_ENGINE_INSTANCE_SHIFT ; 
 scalar_t__ GEN11_MAX_CONTEXT_HW_ID ; 
 int GEN11_SW_CTX_ID_SHIFT ; 
 int /*<<< orphan*/  GEN11_SW_CTX_ID_WIDTH ; 
 int GEN8_CTX_ID_SHIFT ; 
 int /*<<< orphan*/  GEN8_CTX_ID_WIDTH ; 
 int GENMASK_ULL (int,int) ; 
 int INTEL_GEN (int /*<<< orphan*/ ) ; 
 int LRC_HEADER_PAGES ; 
 scalar_t__ MAX_CONTEXT_HW_ID ; 
 int PAGE_SIZE ; 
 int i915_ggtt_offset (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
intel_lr_context_descriptor_update(struct i915_gem_context *ctx,
				   struct intel_engine_cs *engine,
				   struct intel_context *ce)
{
	u64 desc;

	BUILD_BUG_ON(MAX_CONTEXT_HW_ID > (BIT(GEN8_CTX_ID_WIDTH)));
	BUILD_BUG_ON(GEN11_MAX_CONTEXT_HW_ID > (BIT(GEN11_SW_CTX_ID_WIDTH)));

	desc = ctx->desc_template;				/* bits  0-11 */
	GEM_BUG_ON(desc & GENMASK_ULL(63, 12));

	desc |= i915_ggtt_offset(ce->state) + LRC_HEADER_PAGES * PAGE_SIZE;
								/* bits 12-31 */
	GEM_BUG_ON(desc & GENMASK_ULL(63, 32));

	/*
	 * The following 32bits are copied into the OA reports (dword 2).
	 * Consider updating oa_get_render_ctx_id in i915_perf.c when changing
	 * anything below.
	 */
	if (INTEL_GEN(ctx->i915) >= 11) {
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

	ce->lrc_desc = desc;
}