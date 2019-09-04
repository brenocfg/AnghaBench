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
struct intel_engine_cs {int /*<<< orphan*/  emit_breadcrumb_sz; int /*<<< orphan*/  emit_breadcrumb; int /*<<< orphan*/  emit_flush; int /*<<< orphan*/  init_context; int /*<<< orphan*/  init_hw; int /*<<< orphan*/  irq_keep_mask; struct drm_i915_private* i915; } ;
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,int) ; 
 int /*<<< orphan*/  GT_RENDER_L3_PARITY_ERROR_INTERRUPT ; 
 scalar_t__ HAS_L3_DPF (struct drm_i915_private*) ; 
 int INTEL_GEN (struct drm_i915_private*) ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  gen8_emit_breadcrumb_rcs ; 
 int /*<<< orphan*/  gen8_emit_breadcrumb_rcs_sz ; 
 int /*<<< orphan*/  gen8_emit_flush_render ; 
 int /*<<< orphan*/  gen8_init_rcs_context ; 
 int /*<<< orphan*/  gen8_init_render_ring ; 
 int /*<<< orphan*/  gen9_init_render_ring ; 
 int intel_engine_create_scratch (struct intel_engine_cs*,int /*<<< orphan*/ ) ; 
 int intel_init_workaround_bb (struct intel_engine_cs*) ; 
 int logical_ring_init (struct intel_engine_cs*) ; 
 int /*<<< orphan*/  logical_ring_setup (struct intel_engine_cs*) ; 

int logical_render_ring_init(struct intel_engine_cs *engine)
{
	struct drm_i915_private *dev_priv = engine->i915;
	int ret;

	logical_ring_setup(engine);

	if (HAS_L3_DPF(dev_priv))
		engine->irq_keep_mask |= GT_RENDER_L3_PARITY_ERROR_INTERRUPT;

	/* Override some for render ring. */
	if (INTEL_GEN(dev_priv) >= 9)
		engine->init_hw = gen9_init_render_ring;
	else
		engine->init_hw = gen8_init_render_ring;
	engine->init_context = gen8_init_rcs_context;
	engine->emit_flush = gen8_emit_flush_render;
	engine->emit_breadcrumb = gen8_emit_breadcrumb_rcs;
	engine->emit_breadcrumb_sz = gen8_emit_breadcrumb_rcs_sz;

	ret = intel_engine_create_scratch(engine, PAGE_SIZE);
	if (ret)
		return ret;

	ret = intel_init_workaround_bb(engine);
	if (ret) {
		/*
		 * We continue even if we fail to initialize WA batch
		 * because we only expect rare glitches but nothing
		 * critical to prevent us from using GPU
		 */
		DRM_ERROR("WA batch buffer initialization failed: %d\n",
			  ret);
	}

	return logical_ring_init(engine);
}