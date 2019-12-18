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
struct TYPE_2__ {int /*<<< orphan*/ * shadow_va; int /*<<< orphan*/ * obj; } ;
struct intel_shadow_wa_ctx {TYPE_1__ indirect_ctx; } ;

/* Variables and functions */
 int /*<<< orphan*/  i915_gem_object_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i915_gem_object_unpin_map (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void release_shadow_wa_ctx(struct intel_shadow_wa_ctx *wa_ctx)
{
	if (!wa_ctx->indirect_ctx.obj)
		return;

	i915_gem_object_unpin_map(wa_ctx->indirect_ctx.obj);
	i915_gem_object_put(wa_ctx->indirect_ctx.obj);

	wa_ctx->indirect_ctx.obj = NULL;
	wa_ctx->indirect_ctx.shadow_va = NULL;
}