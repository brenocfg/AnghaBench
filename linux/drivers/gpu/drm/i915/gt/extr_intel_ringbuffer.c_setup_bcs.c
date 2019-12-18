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
struct intel_engine_cs {int /*<<< orphan*/  emit_fini_breadcrumb; int /*<<< orphan*/  irq_enable_mask; int /*<<< orphan*/  emit_flush; struct drm_i915_private* i915; } ;
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GT_BLT_USER_INTERRUPT ; 
 scalar_t__ IS_GEN (struct drm_i915_private*,int) ; 
 int /*<<< orphan*/  gen6_ring_flush ; 
 int /*<<< orphan*/  gen6_xcs_emit_breadcrumb ; 
 int /*<<< orphan*/  gen7_xcs_emit_breadcrumb ; 

__attribute__((used)) static void setup_bcs(struct intel_engine_cs *engine)
{
	struct drm_i915_private *i915 = engine->i915;

	engine->emit_flush = gen6_ring_flush;
	engine->irq_enable_mask = GT_BLT_USER_INTERRUPT;

	if (IS_GEN(i915, 6))
		engine->emit_fini_breadcrumb = gen6_xcs_emit_breadcrumb;
	else
		engine->emit_fini_breadcrumb = gen7_xcs_emit_breadcrumb;
}