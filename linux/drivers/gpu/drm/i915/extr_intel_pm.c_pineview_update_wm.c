#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_16__ {TYPE_4__* primary; int /*<<< orphan*/  dev; } ;
struct intel_crtc {TYPE_5__ base; TYPE_2__* config; } ;
struct drm_i915_private {int /*<<< orphan*/  mem_freq; int /*<<< orphan*/  fsb_freq; int /*<<< orphan*/  is_ddr3; } ;
struct drm_framebuffer {TYPE_6__* format; } ;
struct drm_display_mode {int crtc_clock; } ;
struct cxsr_latency {int /*<<< orphan*/  cursor_hpll_disable; int /*<<< orphan*/  display_hpll_disable; int /*<<< orphan*/  cursor_sr; int /*<<< orphan*/  display_sr; } ;
struct TYPE_18__ {int /*<<< orphan*/  fifo_size; } ;
struct TYPE_17__ {int* cpp; } ;
struct TYPE_15__ {TYPE_3__* state; } ;
struct TYPE_14__ {struct drm_framebuffer* fb; } ;
struct TYPE_12__ {struct drm_display_mode adjusted_mode; } ;
struct TYPE_13__ {TYPE_1__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  CURSOR_SR ; 
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,...) ; 
 int /*<<< orphan*/  DSPFW1 ; 
 int /*<<< orphan*/  DSPFW3 ; 
 int /*<<< orphan*/  DSPFW_CURSOR_SR_MASK ; 
 int /*<<< orphan*/  DSPFW_HPLL_CURSOR_MASK ; 
 int /*<<< orphan*/  DSPFW_HPLL_SR_MASK ; 
 int /*<<< orphan*/  DSPFW_SR_MASK ; 
 int /*<<< orphan*/  FW_WM (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HPLL_CURSOR ; 
 int /*<<< orphan*/  HPLL_SR ; 
 int /*<<< orphan*/  I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IS_MOBILE (struct drm_i915_private*) ; 
 int /*<<< orphan*/  SR ; 
 unsigned int intel_calculate_wm (int,TYPE_7__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 struct cxsr_latency* intel_get_cxsr_latency (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_set_memory_cxsr (struct drm_i915_private*,int) ; 
 TYPE_7__ pineview_cursor_hplloff_wm ; 
 TYPE_7__ pineview_cursor_wm ; 
 TYPE_7__ pineview_display_hplloff_wm ; 
 TYPE_7__ pineview_display_wm ; 
 struct intel_crtc* single_enabled_crtc (struct drm_i915_private*) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pineview_update_wm(struct intel_crtc *unused_crtc)
{
	struct drm_i915_private *dev_priv = to_i915(unused_crtc->base.dev);
	struct intel_crtc *crtc;
	const struct cxsr_latency *latency;
	u32 reg;
	unsigned int wm;

	latency = intel_get_cxsr_latency(!IS_MOBILE(dev_priv),
					 dev_priv->is_ddr3,
					 dev_priv->fsb_freq,
					 dev_priv->mem_freq);
	if (!latency) {
		DRM_DEBUG_KMS("Unknown FSB/MEM found, disable CxSR\n");
		intel_set_memory_cxsr(dev_priv, false);
		return;
	}

	crtc = single_enabled_crtc(dev_priv);
	if (crtc) {
		const struct drm_display_mode *adjusted_mode =
			&crtc->config->base.adjusted_mode;
		const struct drm_framebuffer *fb =
			crtc->base.primary->state->fb;
		int cpp = fb->format->cpp[0];
		int clock = adjusted_mode->crtc_clock;

		/* Display SR */
		wm = intel_calculate_wm(clock, &pineview_display_wm,
					pineview_display_wm.fifo_size,
					cpp, latency->display_sr);
		reg = I915_READ(DSPFW1);
		reg &= ~DSPFW_SR_MASK;
		reg |= FW_WM(wm, SR);
		I915_WRITE(DSPFW1, reg);
		DRM_DEBUG_KMS("DSPFW1 register is %x\n", reg);

		/* cursor SR */
		wm = intel_calculate_wm(clock, &pineview_cursor_wm,
					pineview_display_wm.fifo_size,
					4, latency->cursor_sr);
		reg = I915_READ(DSPFW3);
		reg &= ~DSPFW_CURSOR_SR_MASK;
		reg |= FW_WM(wm, CURSOR_SR);
		I915_WRITE(DSPFW3, reg);

		/* Display HPLL off SR */
		wm = intel_calculate_wm(clock, &pineview_display_hplloff_wm,
					pineview_display_hplloff_wm.fifo_size,
					cpp, latency->display_hpll_disable);
		reg = I915_READ(DSPFW3);
		reg &= ~DSPFW_HPLL_SR_MASK;
		reg |= FW_WM(wm, HPLL_SR);
		I915_WRITE(DSPFW3, reg);

		/* cursor HPLL off SR */
		wm = intel_calculate_wm(clock, &pineview_cursor_hplloff_wm,
					pineview_display_hplloff_wm.fifo_size,
					4, latency->cursor_hpll_disable);
		reg = I915_READ(DSPFW3);
		reg &= ~DSPFW_HPLL_CURSOR_MASK;
		reg |= FW_WM(wm, HPLL_CURSOR);
		I915_WRITE(DSPFW3, reg);
		DRM_DEBUG_KMS("DSPFW3 register is %x\n", reg);

		intel_set_memory_cxsr(dev_priv, true);
	} else {
		intel_set_memory_cxsr(dev_priv, false);
	}
}