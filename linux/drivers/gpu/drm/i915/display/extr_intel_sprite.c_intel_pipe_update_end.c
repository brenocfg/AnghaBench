#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct TYPE_6__ {int /*<<< orphan*/ * event; int /*<<< orphan*/  crtc; } ;
struct intel_crtc_state {TYPE_1__ base; } ;
struct TYPE_7__ {scalar_t__ start_vbl_count; int /*<<< orphan*/  start_vbl_time; int /*<<< orphan*/  scanline_start; int /*<<< orphan*/  max_vbl; int /*<<< orphan*/  min_vbl; } ;
struct TYPE_9__ {TYPE_3__* dev; } ;
struct intel_crtc {int pipe; TYPE_2__ debug; TYPE_4__ base; } ;
struct drm_i915_private {int dummy; } ;
typedef  int /*<<< orphan*/  ktime_t ;
typedef  enum pipe { ____Placeholder_pipe } pipe ;
struct TYPE_8__ {int /*<<< orphan*/  event_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DRM_WARN (char*,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 scalar_t__ VBLANK_EVASION_TIME_US ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  drm_crtc_arm_vblank_event (TYPE_4__*,int /*<<< orphan*/ *) ; 
 scalar_t__ drm_crtc_vblank_get (TYPE_4__*) ; 
 scalar_t__ intel_crtc_get_vblank_counter (struct intel_crtc*) ; 
 int intel_get_crtc_scanline (struct intel_crtc*) ; 
 scalar_t__ intel_vgpu_active (struct drm_i915_private*) ; 
 int /*<<< orphan*/  ktime_get () ; 
 scalar_t__ ktime_us_delta (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  local_irq_enable () ; 
 int /*<<< orphan*/  pipe_name (int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 struct drm_i915_private* to_i915 (TYPE_3__*) ; 
 struct intel_crtc* to_intel_crtc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_i915_pipe_update_end (struct intel_crtc*,scalar_t__,int) ; 

void intel_pipe_update_end(struct intel_crtc_state *new_crtc_state)
{
	struct intel_crtc *crtc = to_intel_crtc(new_crtc_state->base.crtc);
	enum pipe pipe = crtc->pipe;
	int scanline_end = intel_get_crtc_scanline(crtc);
	u32 end_vbl_count = intel_crtc_get_vblank_counter(crtc);
	ktime_t end_vbl_time = ktime_get();
	struct drm_i915_private *dev_priv = to_i915(crtc->base.dev);

	trace_i915_pipe_update_end(crtc, end_vbl_count, scanline_end);

	/* We're still in the vblank-evade critical section, this can't race.
	 * Would be slightly nice to just grab the vblank count and arm the
	 * event outside of the critical section - the spinlock might spin for a
	 * while ... */
	if (new_crtc_state->base.event) {
		WARN_ON(drm_crtc_vblank_get(&crtc->base) != 0);

		spin_lock(&crtc->base.dev->event_lock);
		drm_crtc_arm_vblank_event(&crtc->base, new_crtc_state->base.event);
		spin_unlock(&crtc->base.dev->event_lock);

		new_crtc_state->base.event = NULL;
	}

	local_irq_enable();

	if (intel_vgpu_active(dev_priv))
		return;

	if (crtc->debug.start_vbl_count &&
	    crtc->debug.start_vbl_count != end_vbl_count) {
		DRM_ERROR("Atomic update failure on pipe %c (start=%u end=%u) time %lld us, min %d, max %d, scanline start %d, end %d\n",
			  pipe_name(pipe), crtc->debug.start_vbl_count,
			  end_vbl_count,
			  ktime_us_delta(end_vbl_time, crtc->debug.start_vbl_time),
			  crtc->debug.min_vbl, crtc->debug.max_vbl,
			  crtc->debug.scanline_start, scanline_end);
	}
#ifdef CONFIG_DRM_I915_DEBUG_VBLANK_EVADE
	else if (ktime_us_delta(end_vbl_time, crtc->debug.start_vbl_time) >
		 VBLANK_EVASION_TIME_US)
		DRM_WARN("Atomic update on pipe (%c) took %lld us, max time under evasion is %u us\n",
			 pipe_name(pipe),
			 ktime_us_delta(end_vbl_time, crtc->debug.start_vbl_time),
			 VBLANK_EVASION_TIME_US);
#endif
}