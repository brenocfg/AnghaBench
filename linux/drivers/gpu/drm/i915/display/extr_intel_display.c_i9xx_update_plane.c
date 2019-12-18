#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_11__ {int x1; int y1; } ;
struct TYPE_8__ {TYPE_5__ dst; } ;
struct intel_plane_state {int ctl; TYPE_3__* color_plane; TYPE_2__ base; } ;
struct TYPE_7__ {int /*<<< orphan*/  dev; } ;
struct intel_plane {int i9xx_plane; TYPE_1__ base; } ;
struct intel_crtc_state {int dummy; } ;
struct TYPE_10__ {int /*<<< orphan*/  lock; } ;
struct drm_i915_private {TYPE_4__ uncore; } ;
typedef  enum i9xx_plane_id { ____Placeholder_i9xx_plane_id } i9xx_plane_id ;
struct TYPE_9__ {int x; int y; int offset; int stride; } ;

/* Variables and functions */
 int /*<<< orphan*/  DSPADDR (int) ; 
 int /*<<< orphan*/  DSPCNTR (int) ; 
 int /*<<< orphan*/  DSPLINOFF (int) ; 
 int /*<<< orphan*/  DSPOFFSET (int) ; 
 int /*<<< orphan*/  DSPPOS (int) ; 
 int /*<<< orphan*/  DSPSIZE (int) ; 
 int /*<<< orphan*/  DSPSTRIDE (int) ; 
 int /*<<< orphan*/  DSPSURF (int) ; 
 int /*<<< orphan*/  DSPTILEOFF (int) ; 
 int /*<<< orphan*/  I915_WRITE_FW (int /*<<< orphan*/ ,int) ; 
 int INTEL_GEN (struct drm_i915_private*) ; 
 scalar_t__ IS_BROADWELL (struct drm_i915_private*) ; 
 scalar_t__ IS_CHERRYVIEW (struct drm_i915_private*) ; 
 scalar_t__ IS_HASWELL (struct drm_i915_private*) ; 
 int PLANE_B ; 
 int /*<<< orphan*/  PRIMCNSTALPHA (int) ; 
 int /*<<< orphan*/  PRIMPOS (int) ; 
 int /*<<< orphan*/  PRIMSIZE (int) ; 
 int drm_rect_height (TYPE_5__*) ; 
 int drm_rect_width (TYPE_5__*) ; 
 int i9xx_plane_ctl_crtc (struct intel_crtc_state const*) ; 
 int intel_fb_xy_to_linear (int,int,struct intel_plane_state const*,int /*<<< orphan*/ ) ; 
 int intel_plane_ggtt_offset (struct intel_plane_state const*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void i9xx_update_plane(struct intel_plane *plane,
			      const struct intel_crtc_state *crtc_state,
			      const struct intel_plane_state *plane_state)
{
	struct drm_i915_private *dev_priv = to_i915(plane->base.dev);
	enum i9xx_plane_id i9xx_plane = plane->i9xx_plane;
	u32 linear_offset;
	int x = plane_state->color_plane[0].x;
	int y = plane_state->color_plane[0].y;
	int crtc_x = plane_state->base.dst.x1;
	int crtc_y = plane_state->base.dst.y1;
	int crtc_w = drm_rect_width(&plane_state->base.dst);
	int crtc_h = drm_rect_height(&plane_state->base.dst);
	unsigned long irqflags;
	u32 dspaddr_offset;
	u32 dspcntr;

	dspcntr = plane_state->ctl | i9xx_plane_ctl_crtc(crtc_state);

	linear_offset = intel_fb_xy_to_linear(x, y, plane_state, 0);

	if (INTEL_GEN(dev_priv) >= 4)
		dspaddr_offset = plane_state->color_plane[0].offset;
	else
		dspaddr_offset = linear_offset;

	spin_lock_irqsave(&dev_priv->uncore.lock, irqflags);

	I915_WRITE_FW(DSPSTRIDE(i9xx_plane), plane_state->color_plane[0].stride);

	if (INTEL_GEN(dev_priv) < 4) {
		/*
		 * PLANE_A doesn't actually have a full window
		 * generator but let's assume we still need to
		 * program whatever is there.
		 */
		I915_WRITE_FW(DSPPOS(i9xx_plane), (crtc_y << 16) | crtc_x);
		I915_WRITE_FW(DSPSIZE(i9xx_plane),
			      ((crtc_h - 1) << 16) | (crtc_w - 1));
	} else if (IS_CHERRYVIEW(dev_priv) && i9xx_plane == PLANE_B) {
		I915_WRITE_FW(PRIMPOS(i9xx_plane), (crtc_y << 16) | crtc_x);
		I915_WRITE_FW(PRIMSIZE(i9xx_plane),
			      ((crtc_h - 1) << 16) | (crtc_w - 1));
		I915_WRITE_FW(PRIMCNSTALPHA(i9xx_plane), 0);
	}

	if (IS_HASWELL(dev_priv) || IS_BROADWELL(dev_priv)) {
		I915_WRITE_FW(DSPOFFSET(i9xx_plane), (y << 16) | x);
	} else if (INTEL_GEN(dev_priv) >= 4) {
		I915_WRITE_FW(DSPLINOFF(i9xx_plane), linear_offset);
		I915_WRITE_FW(DSPTILEOFF(i9xx_plane), (y << 16) | x);
	}

	/*
	 * The control register self-arms if the plane was previously
	 * disabled. Try to make the plane enable atomic by writing
	 * the control register just before the surface register.
	 */
	I915_WRITE_FW(DSPCNTR(i9xx_plane), dspcntr);
	if (INTEL_GEN(dev_priv) >= 4)
		I915_WRITE_FW(DSPSURF(i9xx_plane),
			      intel_plane_ggtt_offset(plane_state) +
			      dspaddr_offset);
	else
		I915_WRITE_FW(DSPADDR(i9xx_plane),
			      intel_plane_ggtt_offset(plane_state) +
			      dspaddr_offset);

	spin_unlock_irqrestore(&dev_priv->uncore.lock, irqflags);
}