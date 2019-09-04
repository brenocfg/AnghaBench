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
struct TYPE_3__ {int /*<<< orphan*/  finish; int /*<<< orphan*/  reset; int /*<<< orphan*/  prepare; } ;
struct intel_engine_cs {int /*<<< orphan*/  emit_bb_start; int /*<<< orphan*/  set_default_submission; scalar_t__ emit_breadcrumb_sz; int /*<<< orphan*/  emit_breadcrumb; int /*<<< orphan*/  request_alloc; int /*<<< orphan*/  context_pin; TYPE_1__ reset; int /*<<< orphan*/  init_hw; } ;
struct drm_i915_private {int dummy; } ;
struct TYPE_4__ {int num_rings; } ;

/* Variables and functions */
 int /*<<< orphan*/  GEM_BUG_ON (int) ; 
 scalar_t__ HAS_LEGACY_SEMAPHORES (struct drm_i915_private*) ; 
 int INTEL_GEN (struct drm_i915_private*) ; 
 TYPE_2__* INTEL_INFO (struct drm_i915_private*) ; 
 scalar_t__ IS_I830 (struct drm_i915_private*) ; 
 scalar_t__ IS_I845G (struct drm_i915_private*) ; 
 int /*<<< orphan*/  gen6_emit_bb_start ; 
 int /*<<< orphan*/  gen6_sema_emit_breadcrumb ; 
 int /*<<< orphan*/  i830_emit_bb_start ; 
 int /*<<< orphan*/  i915_emit_bb_start ; 
 int /*<<< orphan*/  i965_emit_bb_start ; 
 int /*<<< orphan*/  i9xx_emit_breadcrumb ; 
 scalar_t__ i9xx_emit_breadcrumb_sz ; 
 int /*<<< orphan*/  i9xx_set_default_submission ; 
 int /*<<< orphan*/  init_ring_common ; 
 int /*<<< orphan*/  intel_ring_context_pin ; 
 int /*<<< orphan*/  intel_ring_init_irq (struct drm_i915_private*,struct intel_engine_cs*) ; 
 int /*<<< orphan*/  intel_ring_init_semaphores (struct drm_i915_private*,struct intel_engine_cs*) ; 
 int /*<<< orphan*/  reset_finish ; 
 int /*<<< orphan*/  reset_prepare ; 
 int /*<<< orphan*/  reset_ring ; 
 int /*<<< orphan*/  ring_request_alloc ; 

__attribute__((used)) static void intel_ring_default_vfuncs(struct drm_i915_private *dev_priv,
				      struct intel_engine_cs *engine)
{
	/* gen8+ are only supported with execlists */
	GEM_BUG_ON(INTEL_GEN(dev_priv) >= 8);

	intel_ring_init_irq(dev_priv, engine);
	intel_ring_init_semaphores(dev_priv, engine);

	engine->init_hw = init_ring_common;
	engine->reset.prepare = reset_prepare;
	engine->reset.reset = reset_ring;
	engine->reset.finish = reset_finish;

	engine->context_pin = intel_ring_context_pin;
	engine->request_alloc = ring_request_alloc;

	engine->emit_breadcrumb = i9xx_emit_breadcrumb;
	engine->emit_breadcrumb_sz = i9xx_emit_breadcrumb_sz;
	if (HAS_LEGACY_SEMAPHORES(dev_priv)) {
		int num_rings;

		engine->emit_breadcrumb = gen6_sema_emit_breadcrumb;

		num_rings = INTEL_INFO(dev_priv)->num_rings - 1;
		engine->emit_breadcrumb_sz += num_rings * 3;
		if (num_rings & 1)
			engine->emit_breadcrumb_sz++;
	}

	engine->set_default_submission = i9xx_set_default_submission;

	if (INTEL_GEN(dev_priv) >= 6)
		engine->emit_bb_start = gen6_emit_bb_start;
	else if (INTEL_GEN(dev_priv) >= 4)
		engine->emit_bb_start = i965_emit_bb_start;
	else if (IS_I830(dev_priv) || IS_I845G(dev_priv))
		engine->emit_bb_start = i830_emit_bb_start;
	else
		engine->emit_bb_start = i915_emit_bb_start;
}