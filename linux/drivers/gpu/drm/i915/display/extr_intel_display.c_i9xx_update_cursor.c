#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  void* u32 ;
struct TYPE_6__ {int crtc_h; int crtc_w; scalar_t__ visible; } ;
struct intel_plane_state {int ctl; TYPE_2__ base; } ;
struct TYPE_7__ {void* base; void* size; void* cntl; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;
struct intel_plane {int pipe; TYPE_3__ cursor; TYPE_1__ base; } ;
struct intel_crtc_state {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  lock; } ;
struct drm_i915_private {TYPE_4__ uncore; } ;
typedef  enum pipe { ____Placeholder_pipe } pipe ;

/* Variables and functions */
 int /*<<< orphan*/  CURBASE (int) ; 
 int /*<<< orphan*/  CURCNTR (int) ; 
 int /*<<< orphan*/  CURPOS (int) ; 
 int /*<<< orphan*/  CUR_FBC_CTL (int) ; 
 int CUR_FBC_CTL_EN ; 
 scalar_t__ HAS_CUR_FBC (struct drm_i915_private*) ; 
 int /*<<< orphan*/  I915_WRITE_FW (int /*<<< orphan*/ ,void*) ; 
 int INTEL_GEN (struct drm_i915_private*) ; 
 int i9xx_cursor_ctl_crtc (struct intel_crtc_state const*) ; 
 void* intel_cursor_base (struct intel_plane_state const*) ; 
 void* intel_cursor_position (struct intel_plane_state const*) ; 
 int /*<<< orphan*/  skl_write_cursor_wm (struct intel_plane*,struct intel_crtc_state const*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void i9xx_update_cursor(struct intel_plane *plane,
			       const struct intel_crtc_state *crtc_state,
			       const struct intel_plane_state *plane_state)
{
	struct drm_i915_private *dev_priv = to_i915(plane->base.dev);
	enum pipe pipe = plane->pipe;
	u32 cntl = 0, base = 0, pos = 0, fbc_ctl = 0;
	unsigned long irqflags;

	if (plane_state && plane_state->base.visible) {
		cntl = plane_state->ctl |
			i9xx_cursor_ctl_crtc(crtc_state);

		if (plane_state->base.crtc_h != plane_state->base.crtc_w)
			fbc_ctl = CUR_FBC_CTL_EN | (plane_state->base.crtc_h - 1);

		base = intel_cursor_base(plane_state);
		pos = intel_cursor_position(plane_state);
	}

	spin_lock_irqsave(&dev_priv->uncore.lock, irqflags);

	/*
	 * On some platforms writing CURCNTR first will also
	 * cause CURPOS to be armed by the CURBASE write.
	 * Without the CURCNTR write the CURPOS write would
	 * arm itself. Thus we always update CURCNTR before
	 * CURPOS.
	 *
	 * On other platforms CURPOS always requires the
	 * CURBASE write to arm the update. Additonally
	 * a write to any of the cursor register will cancel
	 * an already armed cursor update. Thus leaving out
	 * the CURBASE write after CURPOS could lead to a
	 * cursor that doesn't appear to move, or even change
	 * shape. Thus we always write CURBASE.
	 *
	 * The other registers are armed by by the CURBASE write
	 * except when the plane is getting enabled at which time
	 * the CURCNTR write arms the update.
	 */

	if (INTEL_GEN(dev_priv) >= 9)
		skl_write_cursor_wm(plane, crtc_state);

	if (plane->cursor.base != base ||
	    plane->cursor.size != fbc_ctl ||
	    plane->cursor.cntl != cntl) {
		if (HAS_CUR_FBC(dev_priv))
			I915_WRITE_FW(CUR_FBC_CTL(pipe), fbc_ctl);
		I915_WRITE_FW(CURCNTR(pipe), cntl);
		I915_WRITE_FW(CURPOS(pipe), pos);
		I915_WRITE_FW(CURBASE(pipe), base);

		plane->cursor.base = base;
		plane->cursor.size = fbc_ctl;
		plane->cursor.cntl = cntl;
	} else {
		I915_WRITE_FW(CURPOS(pipe), pos);
		I915_WRITE_FW(CURBASE(pipe), base);
	}

	spin_unlock_irqrestore(&dev_priv->uncore.lock, irqflags);
}