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
struct TYPE_8__ {TYPE_5__ src; TYPE_5__ dst; } ;
struct drm_intel_sprite_colorkey {int min_value; int channel_mask; int max_value; scalar_t__ flags; } ;
struct intel_plane_state {int ctl; TYPE_3__* color_plane; TYPE_2__ base; struct drm_intel_sprite_colorkey ckey; } ;
struct TYPE_7__ {int /*<<< orphan*/  dev; } ;
struct intel_plane {int pipe; TYPE_1__ base; } ;
struct intel_crtc_state {int dummy; } ;
struct TYPE_10__ {int /*<<< orphan*/  lock; } ;
struct drm_i915_private {TYPE_4__ uncore; } ;
typedef  enum pipe { ____Placeholder_pipe } pipe ;
struct TYPE_9__ {int offset; int x; int y; int stride; } ;

/* Variables and functions */
 int /*<<< orphan*/  I915_WRITE_FW (int /*<<< orphan*/ ,int) ; 
 scalar_t__ IS_BROADWELL (struct drm_i915_private*) ; 
 scalar_t__ IS_HASWELL (struct drm_i915_private*) ; 
 scalar_t__ IS_IVYBRIDGE (struct drm_i915_private*) ; 
 int /*<<< orphan*/  SPRCTL (int) ; 
 int SPRITE_SCALE_ENABLE ; 
 int /*<<< orphan*/  SPRKEYMAX (int) ; 
 int /*<<< orphan*/  SPRKEYMSK (int) ; 
 int /*<<< orphan*/  SPRKEYVAL (int) ; 
 int /*<<< orphan*/  SPRLINOFF (int) ; 
 int /*<<< orphan*/  SPROFFSET (int) ; 
 int /*<<< orphan*/  SPRPOS (int) ; 
 int /*<<< orphan*/  SPRSCALE (int) ; 
 int /*<<< orphan*/  SPRSIZE (int) ; 
 int /*<<< orphan*/  SPRSTRIDE (int) ; 
 int /*<<< orphan*/  SPRSURF (int) ; 
 int /*<<< orphan*/  SPRTILEOFF (int) ; 
 int drm_rect_height (TYPE_5__*) ; 
 int drm_rect_width (TYPE_5__*) ; 
 int intel_fb_xy_to_linear (int,int,struct intel_plane_state const*,int /*<<< orphan*/ ) ; 
 int intel_plane_ggtt_offset (struct intel_plane_state const*) ; 
 int ivb_sprite_ctl_crtc (struct intel_crtc_state const*) ; 
 int /*<<< orphan*/  ivb_update_gamma (struct intel_plane_state const*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ivb_update_plane(struct intel_plane *plane,
		 const struct intel_crtc_state *crtc_state,
		 const struct intel_plane_state *plane_state)
{
	struct drm_i915_private *dev_priv = to_i915(plane->base.dev);
	enum pipe pipe = plane->pipe;
	u32 sprsurf_offset = plane_state->color_plane[0].offset;
	u32 linear_offset;
	const struct drm_intel_sprite_colorkey *key = &plane_state->ckey;
	int crtc_x = plane_state->base.dst.x1;
	int crtc_y = plane_state->base.dst.y1;
	u32 crtc_w = drm_rect_width(&plane_state->base.dst);
	u32 crtc_h = drm_rect_height(&plane_state->base.dst);
	u32 x = plane_state->color_plane[0].x;
	u32 y = plane_state->color_plane[0].y;
	u32 src_w = drm_rect_width(&plane_state->base.src) >> 16;
	u32 src_h = drm_rect_height(&plane_state->base.src) >> 16;
	u32 sprctl, sprscale = 0;
	unsigned long irqflags;

	sprctl = plane_state->ctl | ivb_sprite_ctl_crtc(crtc_state);

	/* Sizes are 0 based */
	src_w--;
	src_h--;
	crtc_w--;
	crtc_h--;

	if (crtc_w != src_w || crtc_h != src_h)
		sprscale = SPRITE_SCALE_ENABLE | (src_w << 16) | src_h;

	linear_offset = intel_fb_xy_to_linear(x, y, plane_state, 0);

	spin_lock_irqsave(&dev_priv->uncore.lock, irqflags);

	I915_WRITE_FW(SPRSTRIDE(pipe), plane_state->color_plane[0].stride);
	I915_WRITE_FW(SPRPOS(pipe), (crtc_y << 16) | crtc_x);
	I915_WRITE_FW(SPRSIZE(pipe), (crtc_h << 16) | crtc_w);
	if (IS_IVYBRIDGE(dev_priv))
		I915_WRITE_FW(SPRSCALE(pipe), sprscale);

	if (key->flags) {
		I915_WRITE_FW(SPRKEYVAL(pipe), key->min_value);
		I915_WRITE_FW(SPRKEYMSK(pipe), key->channel_mask);
		I915_WRITE_FW(SPRKEYMAX(pipe), key->max_value);
	}

	/* HSW consolidates SPRTILEOFF and SPRLINOFF into a single SPROFFSET
	 * register */
	if (IS_HASWELL(dev_priv) || IS_BROADWELL(dev_priv)) {
		I915_WRITE_FW(SPROFFSET(pipe), (y << 16) | x);
	} else {
		I915_WRITE_FW(SPRLINOFF(pipe), linear_offset);
		I915_WRITE_FW(SPRTILEOFF(pipe), (y << 16) | x);
	}

	/*
	 * The control register self-arms if the plane was previously
	 * disabled. Try to make the plane enable atomic by writing
	 * the control register just before the surface register.
	 */
	I915_WRITE_FW(SPRCTL(pipe), sprctl);
	I915_WRITE_FW(SPRSURF(pipe),
		      intel_plane_ggtt_offset(plane_state) + sprsurf_offset);

	ivb_update_gamma(plane_state);

	spin_unlock_irqrestore(&dev_priv->uncore.lock, irqflags);
}