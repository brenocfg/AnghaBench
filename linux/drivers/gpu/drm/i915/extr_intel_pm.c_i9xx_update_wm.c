#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct intel_watermark_params {int guard_size; int max_wm; int fifo_size; int /*<<< orphan*/  cacheline_size; } ;
struct TYPE_12__ {TYPE_4__* primary; int /*<<< orphan*/  dev; } ;
struct intel_crtc {TYPE_6__* config; TYPE_5__ base; } ;
struct TYPE_8__ {int (* get_fifo_size ) (struct drm_i915_private*,int /*<<< orphan*/ ) ;} ;
struct drm_i915_private {TYPE_1__ display; } ;
struct drm_i915_gem_object {int dummy; } ;
struct drm_framebuffer {TYPE_7__* format; } ;
struct drm_display_mode {int crtc_clock; int crtc_htotal; } ;
struct TYPE_14__ {int* cpp; } ;
struct TYPE_9__ {struct drm_display_mode adjusted_mode; } ;
struct TYPE_13__ {int pipe_src_w; TYPE_2__ base; } ;
struct TYPE_11__ {TYPE_3__* state; } ;
struct TYPE_10__ {struct drm_framebuffer* fb; } ;

/* Variables and functions */
 int DIV_ROUND_UP (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,int,...) ; 
 int /*<<< orphan*/  FW_BLC ; 
 int /*<<< orphan*/  FW_BLC2 ; 
 int /*<<< orphan*/  FW_BLC_SELF ; 
 int FW_BLC_SELF_FIFO_MASK ; 
 scalar_t__ HAS_FW_BLC (struct drm_i915_private*) ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int) ; 
 scalar_t__ IS_GEN (struct drm_i915_private*,int) ; 
 scalar_t__ IS_I915GM (struct drm_i915_private*) ; 
 scalar_t__ IS_I945G (struct drm_i915_private*) ; 
 scalar_t__ IS_I945GM (struct drm_i915_private*) ; 
 int /*<<< orphan*/  PLANE_A ; 
 int /*<<< orphan*/  PLANE_B ; 
 struct intel_watermark_params i830_a_wm_info ; 
 struct intel_watermark_params i830_bc_wm_info ; 
 int /*<<< orphan*/  i915_gem_object_is_tiled (struct drm_i915_gem_object*) ; 
 struct intel_watermark_params i915_wm_info ; 
 struct intel_watermark_params i945_wm_info ; 
 int intel_calculate_wm (int,struct intel_watermark_params const*,int,int,int /*<<< orphan*/ ) ; 
 scalar_t__ intel_crtc_active (struct intel_crtc*) ; 
 struct drm_i915_gem_object* intel_fb_obj (struct drm_framebuffer*) ; 
 struct intel_crtc* intel_get_crtc_for_plane (struct drm_i915_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_set_memory_cxsr (struct drm_i915_private*,int) ; 
 int intel_wm_method2 (int,int,int,int,int const) ; 
 int /*<<< orphan*/  pessimal_latency_ns ; 
 int stub1 (struct drm_i915_private*,int /*<<< orphan*/ ) ; 
 int stub2 (struct drm_i915_private*,int /*<<< orphan*/ ) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void i9xx_update_wm(struct intel_crtc *unused_crtc)
{
	struct drm_i915_private *dev_priv = to_i915(unused_crtc->base.dev);
	const struct intel_watermark_params *wm_info;
	u32 fwater_lo;
	u32 fwater_hi;
	int cwm, srwm = 1;
	int fifo_size;
	int planea_wm, planeb_wm;
	struct intel_crtc *crtc, *enabled = NULL;

	if (IS_I945GM(dev_priv))
		wm_info = &i945_wm_info;
	else if (!IS_GEN(dev_priv, 2))
		wm_info = &i915_wm_info;
	else
		wm_info = &i830_a_wm_info;

	fifo_size = dev_priv->display.get_fifo_size(dev_priv, PLANE_A);
	crtc = intel_get_crtc_for_plane(dev_priv, PLANE_A);
	if (intel_crtc_active(crtc)) {
		const struct drm_display_mode *adjusted_mode =
			&crtc->config->base.adjusted_mode;
		const struct drm_framebuffer *fb =
			crtc->base.primary->state->fb;
		int cpp;

		if (IS_GEN(dev_priv, 2))
			cpp = 4;
		else
			cpp = fb->format->cpp[0];

		planea_wm = intel_calculate_wm(adjusted_mode->crtc_clock,
					       wm_info, fifo_size, cpp,
					       pessimal_latency_ns);
		enabled = crtc;
	} else {
		planea_wm = fifo_size - wm_info->guard_size;
		if (planea_wm > (long)wm_info->max_wm)
			planea_wm = wm_info->max_wm;
	}

	if (IS_GEN(dev_priv, 2))
		wm_info = &i830_bc_wm_info;

	fifo_size = dev_priv->display.get_fifo_size(dev_priv, PLANE_B);
	crtc = intel_get_crtc_for_plane(dev_priv, PLANE_B);
	if (intel_crtc_active(crtc)) {
		const struct drm_display_mode *adjusted_mode =
			&crtc->config->base.adjusted_mode;
		const struct drm_framebuffer *fb =
			crtc->base.primary->state->fb;
		int cpp;

		if (IS_GEN(dev_priv, 2))
			cpp = 4;
		else
			cpp = fb->format->cpp[0];

		planeb_wm = intel_calculate_wm(adjusted_mode->crtc_clock,
					       wm_info, fifo_size, cpp,
					       pessimal_latency_ns);
		if (enabled == NULL)
			enabled = crtc;
		else
			enabled = NULL;
	} else {
		planeb_wm = fifo_size - wm_info->guard_size;
		if (planeb_wm > (long)wm_info->max_wm)
			planeb_wm = wm_info->max_wm;
	}

	DRM_DEBUG_KMS("FIFO watermarks - A: %d, B: %d\n", planea_wm, planeb_wm);

	if (IS_I915GM(dev_priv) && enabled) {
		struct drm_i915_gem_object *obj;

		obj = intel_fb_obj(enabled->base.primary->state->fb);

		/* self-refresh seems busted with untiled */
		if (!i915_gem_object_is_tiled(obj))
			enabled = NULL;
	}

	/*
	 * Overlay gets an aggressive default since video jitter is bad.
	 */
	cwm = 2;

	/* Play safe and disable self-refresh before adjusting watermarks. */
	intel_set_memory_cxsr(dev_priv, false);

	/* Calc sr entries for one plane configs */
	if (HAS_FW_BLC(dev_priv) && enabled) {
		/* self-refresh has much higher latency */
		static const int sr_latency_ns = 6000;
		const struct drm_display_mode *adjusted_mode =
			&enabled->config->base.adjusted_mode;
		const struct drm_framebuffer *fb =
			enabled->base.primary->state->fb;
		int clock = adjusted_mode->crtc_clock;
		int htotal = adjusted_mode->crtc_htotal;
		int hdisplay = enabled->config->pipe_src_w;
		int cpp;
		int entries;

		if (IS_I915GM(dev_priv) || IS_I945GM(dev_priv))
			cpp = 4;
		else
			cpp = fb->format->cpp[0];

		entries = intel_wm_method2(clock, htotal, hdisplay, cpp,
					   sr_latency_ns / 100);
		entries = DIV_ROUND_UP(entries, wm_info->cacheline_size);
		DRM_DEBUG_KMS("self-refresh entries: %d\n", entries);
		srwm = wm_info->fifo_size - entries;
		if (srwm < 0)
			srwm = 1;

		if (IS_I945G(dev_priv) || IS_I945GM(dev_priv))
			I915_WRITE(FW_BLC_SELF,
				   FW_BLC_SELF_FIFO_MASK | (srwm & 0xff));
		else
			I915_WRITE(FW_BLC_SELF, srwm & 0x3f);
	}

	DRM_DEBUG_KMS("Setting FIFO watermarks - A: %d, B: %d, C: %d, SR %d\n",
		      planea_wm, planeb_wm, cwm, srwm);

	fwater_lo = ((planeb_wm & 0x3f) << 16) | (planea_wm & 0x3f);
	fwater_hi = (cwm & 0x1f);

	/* Set request length to 8 cachelines per fetch */
	fwater_lo = fwater_lo | (1 << 24) | (1 << 8);
	fwater_hi = fwater_hi | (1 << 8);

	I915_WRITE(FW_BLC, fwater_lo);
	I915_WRITE(FW_BLC2, fwater_hi);

	if (enabled)
		intel_set_memory_cxsr(dev_priv, true);
}