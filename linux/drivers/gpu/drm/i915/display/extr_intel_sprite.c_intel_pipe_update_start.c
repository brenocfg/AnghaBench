#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wait_queue_head_t ;
typedef  int /*<<< orphan*/  u32 ;
struct drm_display_mode {int crtc_vblank_start; int flags; } ;
struct TYPE_6__ {struct drm_display_mode adjusted_mode; int /*<<< orphan*/  crtc; } ;
struct intel_crtc_state {TYPE_1__ base; } ;
struct TYPE_7__ {int min_vbl; int max_vbl; int scanline_start; int /*<<< orphan*/  start_vbl_count; int /*<<< orphan*/  start_vbl_time; } ;
struct TYPE_8__ {int /*<<< orphan*/  dev; } ;
struct intel_crtc {TYPE_2__ debug; TYPE_3__ base; int /*<<< orphan*/  pipe; } ;
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEFINE_WAIT (int /*<<< orphan*/ ) ; 
 int DIV_ROUND_UP (int,int) ; 
 int /*<<< orphan*/  DRM_ERROR (char*,int /*<<< orphan*/ ) ; 
 int DRM_MODE_FLAG_INTERLACE ; 
 int /*<<< orphan*/  INTEL_OUTPUT_DSI ; 
 scalar_t__ IS_CHERRYVIEW (struct drm_i915_private*) ; 
 scalar_t__ IS_VALLEYVIEW (struct drm_i915_private*) ; 
 int /*<<< orphan*/  TASK_UNINTERRUPTIBLE ; 
 int /*<<< orphan*/  VBLANK_EVASION_TIME_US ; 
 scalar_t__ WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_crtc_vblank_get (TYPE_3__*) ; 
 int /*<<< orphan*/  drm_crtc_vblank_put (TYPE_3__*) ; 
 int /*<<< orphan*/ * drm_crtc_vblank_waitqueue (TYPE_3__*) ; 
 int /*<<< orphan*/  finish_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  intel_crtc_get_vblank_counter (struct intel_crtc*) ; 
 scalar_t__ intel_crtc_has_type (struct intel_crtc_state const*,int /*<<< orphan*/ ) ; 
 int intel_get_crtc_scanline (struct intel_crtc*) ; 
 scalar_t__ intel_psr_wait_for_idle (struct intel_crtc_state const*,int /*<<< orphan*/ *) ; 
 int intel_usecs_to_scanlines (struct drm_display_mode const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ktime_get () ; 
 int /*<<< orphan*/  local_irq_disable () ; 
 int /*<<< orphan*/  local_irq_enable () ; 
 long msecs_to_jiffies_timeout (int) ; 
 int /*<<< orphan*/  pipe_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  prepare_to_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 long schedule_timeout (long) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 
 struct intel_crtc* to_intel_crtc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_i915_pipe_update_start (struct intel_crtc*) ; 
 int /*<<< orphan*/  trace_i915_pipe_update_vblank_evaded (struct intel_crtc*) ; 
 int /*<<< orphan*/  wait ; 

void intel_pipe_update_start(const struct intel_crtc_state *new_crtc_state)
{
	struct intel_crtc *crtc = to_intel_crtc(new_crtc_state->base.crtc);
	struct drm_i915_private *dev_priv = to_i915(crtc->base.dev);
	const struct drm_display_mode *adjusted_mode = &new_crtc_state->base.adjusted_mode;
	long timeout = msecs_to_jiffies_timeout(1);
	int scanline, min, max, vblank_start;
	wait_queue_head_t *wq = drm_crtc_vblank_waitqueue(&crtc->base);
	bool need_vlv_dsi_wa = (IS_VALLEYVIEW(dev_priv) || IS_CHERRYVIEW(dev_priv)) &&
		intel_crtc_has_type(new_crtc_state, INTEL_OUTPUT_DSI);
	DEFINE_WAIT(wait);
	u32 psr_status;

	vblank_start = adjusted_mode->crtc_vblank_start;
	if (adjusted_mode->flags & DRM_MODE_FLAG_INTERLACE)
		vblank_start = DIV_ROUND_UP(vblank_start, 2);

	/* FIXME needs to be calibrated sensibly */
	min = vblank_start - intel_usecs_to_scanlines(adjusted_mode,
						      VBLANK_EVASION_TIME_US);
	max = vblank_start - 1;

	if (min <= 0 || max <= 0)
		goto irq_disable;

	if (WARN_ON(drm_crtc_vblank_get(&crtc->base)))
		goto irq_disable;

	/*
	 * Wait for psr to idle out after enabling the VBL interrupts
	 * VBL interrupts will start the PSR exit and prevent a PSR
	 * re-entry as well.
	 */
	if (intel_psr_wait_for_idle(new_crtc_state, &psr_status))
		DRM_ERROR("PSR idle timed out 0x%x, atomic update may fail\n",
			  psr_status);

	local_irq_disable();

	crtc->debug.min_vbl = min;
	crtc->debug.max_vbl = max;
	trace_i915_pipe_update_start(crtc);

	for (;;) {
		/*
		 * prepare_to_wait() has a memory barrier, which guarantees
		 * other CPUs can see the task state update by the time we
		 * read the scanline.
		 */
		prepare_to_wait(wq, &wait, TASK_UNINTERRUPTIBLE);

		scanline = intel_get_crtc_scanline(crtc);
		if (scanline < min || scanline > max)
			break;

		if (!timeout) {
			DRM_ERROR("Potential atomic update failure on pipe %c\n",
				  pipe_name(crtc->pipe));
			break;
		}

		local_irq_enable();

		timeout = schedule_timeout(timeout);

		local_irq_disable();
	}

	finish_wait(wq, &wait);

	drm_crtc_vblank_put(&crtc->base);

	/*
	 * On VLV/CHV DSI the scanline counter would appear to
	 * increment approx. 1/3 of a scanline before start of vblank.
	 * The registers still get latched at start of vblank however.
	 * This means we must not write any registers on the first
	 * line of vblank (since not the whole line is actually in
	 * vblank). And unfortunately we can't use the interrupt to
	 * wait here since it will fire too soon. We could use the
	 * frame start interrupt instead since it will fire after the
	 * critical scanline, but that would require more changes
	 * in the interrupt code. So for now we'll just do the nasty
	 * thing and poll for the bad scanline to pass us by.
	 *
	 * FIXME figure out if BXT+ DSI suffers from this as well
	 */
	while (need_vlv_dsi_wa && scanline == vblank_start)
		scanline = intel_get_crtc_scanline(crtc);

	crtc->debug.scanline_start = scanline;
	crtc->debug.start_vbl_time = ktime_get();
	crtc->debug.start_vbl_count = intel_crtc_get_vblank_counter(crtc);

	trace_i915_pipe_update_vblank_evaded(crtc);
	return;

irq_disable:
	local_irq_disable();
}