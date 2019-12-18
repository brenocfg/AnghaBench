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
typedef  scalar_t__ u32 ;
struct TYPE_6__ {unsigned int crtc_w; unsigned int crtc_h; scalar_t__ visible; } ;
struct intel_plane_state {scalar_t__ ctl; TYPE_2__ base; } ;
struct TYPE_7__ {scalar_t__ base; scalar_t__ size; scalar_t__ cntl; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;
struct intel_plane {TYPE_3__ cursor; TYPE_1__ base; } ;
struct intel_crtc_state {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  lock; } ;
struct drm_i915_private {TYPE_4__ uncore; } ;

/* Variables and functions */
 int /*<<< orphan*/  CURBASE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CURCNTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CURPOS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CURSIZE ; 
 int /*<<< orphan*/  I915_WRITE_FW (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  PIPE_A ; 
 scalar_t__ i845_cursor_ctl_crtc (struct intel_crtc_state const*) ; 
 scalar_t__ intel_cursor_base (struct intel_plane_state const*) ; 
 scalar_t__ intel_cursor_position (struct intel_plane_state const*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void i845_update_cursor(struct intel_plane *plane,
			       const struct intel_crtc_state *crtc_state,
			       const struct intel_plane_state *plane_state)
{
	struct drm_i915_private *dev_priv = to_i915(plane->base.dev);
	u32 cntl = 0, base = 0, pos = 0, size = 0;
	unsigned long irqflags;

	if (plane_state && plane_state->base.visible) {
		unsigned int width = plane_state->base.crtc_w;
		unsigned int height = plane_state->base.crtc_h;

		cntl = plane_state->ctl |
			i845_cursor_ctl_crtc(crtc_state);

		size = (height << 12) | width;

		base = intel_cursor_base(plane_state);
		pos = intel_cursor_position(plane_state);
	}

	spin_lock_irqsave(&dev_priv->uncore.lock, irqflags);

	/* On these chipsets we can only modify the base/size/stride
	 * whilst the cursor is disabled.
	 */
	if (plane->cursor.base != base ||
	    plane->cursor.size != size ||
	    plane->cursor.cntl != cntl) {
		I915_WRITE_FW(CURCNTR(PIPE_A), 0);
		I915_WRITE_FW(CURBASE(PIPE_A), base);
		I915_WRITE_FW(CURSIZE, size);
		I915_WRITE_FW(CURPOS(PIPE_A), pos);
		I915_WRITE_FW(CURCNTR(PIPE_A), cntl);

		plane->cursor.base = base;
		plane->cursor.size = size;
		plane->cursor.cntl = cntl;
	} else {
		I915_WRITE_FW(CURPOS(PIPE_A), pos);
	}

	spin_unlock_irqrestore(&dev_priv->uncore.lock, irqflags);
}