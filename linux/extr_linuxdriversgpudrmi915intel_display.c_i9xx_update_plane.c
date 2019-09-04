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
typedef  int u32 ;
struct TYPE_7__ {int x; int y; int offset; } ;
struct TYPE_6__ {struct drm_framebuffer* fb; } ;
struct intel_plane_state {int ctl; TYPE_3__ main; TYPE_2__ base; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;
struct intel_plane {int i9xx_plane; TYPE_1__ base; } ;
struct intel_crtc_state {int pipe_src_h; int pipe_src_w; } ;
struct TYPE_8__ {int /*<<< orphan*/  lock; } ;
struct drm_i915_private {TYPE_4__ uncore; } ;
struct drm_framebuffer {int* pitches; } ;
typedef  int /*<<< orphan*/  i915_reg_t ;
typedef  enum i9xx_plane_id { ____Placeholder_i9xx_plane_id } i9xx_plane_id ;

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
 int /*<<< orphan*/  POSTING_READ_FW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PRIMCNSTALPHA (int) ; 
 int /*<<< orphan*/  PRIMPOS (int) ; 
 int /*<<< orphan*/  PRIMSIZE (int) ; 
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
	const struct drm_framebuffer *fb = plane_state->base.fb;
	enum i9xx_plane_id i9xx_plane = plane->i9xx_plane;
	u32 linear_offset;
	u32 dspcntr = plane_state->ctl;
	i915_reg_t reg = DSPCNTR(i9xx_plane);
	int x = plane_state->main.x;
	int y = plane_state->main.y;
	unsigned long irqflags;
	u32 dspaddr_offset;

	linear_offset = intel_fb_xy_to_linear(x, y, plane_state, 0);

	if (INTEL_GEN(dev_priv) >= 4)
		dspaddr_offset = plane_state->main.offset;
	else
		dspaddr_offset = linear_offset;

	spin_lock_irqsave(&dev_priv->uncore.lock, irqflags);

	if (INTEL_GEN(dev_priv) < 4) {
		/* pipesrc and dspsize control the size that is scaled from,
		 * which should always be the user's requested size.
		 */
		I915_WRITE_FW(DSPSIZE(i9xx_plane),
			      ((crtc_state->pipe_src_h - 1) << 16) |
			      (crtc_state->pipe_src_w - 1));
		I915_WRITE_FW(DSPPOS(i9xx_plane), 0);
	} else if (IS_CHERRYVIEW(dev_priv) && i9xx_plane == PLANE_B) {
		I915_WRITE_FW(PRIMSIZE(i9xx_plane),
			      ((crtc_state->pipe_src_h - 1) << 16) |
			      (crtc_state->pipe_src_w - 1));
		I915_WRITE_FW(PRIMPOS(i9xx_plane), 0);
		I915_WRITE_FW(PRIMCNSTALPHA(i9xx_plane), 0);
	}

	I915_WRITE_FW(reg, dspcntr);

	I915_WRITE_FW(DSPSTRIDE(i9xx_plane), fb->pitches[0]);
	if (IS_HASWELL(dev_priv) || IS_BROADWELL(dev_priv)) {
		I915_WRITE_FW(DSPSURF(i9xx_plane),
			      intel_plane_ggtt_offset(plane_state) +
			      dspaddr_offset);
		I915_WRITE_FW(DSPOFFSET(i9xx_plane), (y << 16) | x);
	} else if (INTEL_GEN(dev_priv) >= 4) {
		I915_WRITE_FW(DSPSURF(i9xx_plane),
			      intel_plane_ggtt_offset(plane_state) +
			      dspaddr_offset);
		I915_WRITE_FW(DSPTILEOFF(i9xx_plane), (y << 16) | x);
		I915_WRITE_FW(DSPLINOFF(i9xx_plane), linear_offset);
	} else {
		I915_WRITE_FW(DSPADDR(i9xx_plane),
			      intel_plane_ggtt_offset(plane_state) +
			      dspaddr_offset);
	}
	POSTING_READ_FW(reg);

	spin_unlock_irqrestore(&dev_priv->uncore.lock, irqflags);
}