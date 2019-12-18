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
 int /*<<< orphan*/  DVSCNTR (int) ; 
 int /*<<< orphan*/  DVSKEYMAX (int) ; 
 int /*<<< orphan*/  DVSKEYMSK (int) ; 
 int /*<<< orphan*/  DVSKEYVAL (int) ; 
 int /*<<< orphan*/  DVSLINOFF (int) ; 
 int /*<<< orphan*/  DVSPOS (int) ; 
 int /*<<< orphan*/  DVSSCALE (int) ; 
 int /*<<< orphan*/  DVSSIZE (int) ; 
 int /*<<< orphan*/  DVSSTRIDE (int) ; 
 int /*<<< orphan*/  DVSSURF (int) ; 
 int /*<<< orphan*/  DVSTILEOFF (int) ; 
 int DVS_SCALE_ENABLE ; 
 int /*<<< orphan*/  I915_WRITE_FW (int /*<<< orphan*/ ,int) ; 
 scalar_t__ IS_G4X (struct drm_i915_private*) ; 
 int drm_rect_height (TYPE_5__*) ; 
 int drm_rect_width (TYPE_5__*) ; 
 int g4x_sprite_ctl_crtc (struct intel_crtc_state const*) ; 
 int /*<<< orphan*/  g4x_update_gamma (struct intel_plane_state const*) ; 
 int /*<<< orphan*/  ilk_update_gamma (struct intel_plane_state const*) ; 
 int intel_fb_xy_to_linear (int,int,struct intel_plane_state const*,int /*<<< orphan*/ ) ; 
 int intel_plane_ggtt_offset (struct intel_plane_state const*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
g4x_update_plane(struct intel_plane *plane,
		 const struct intel_crtc_state *crtc_state,
		 const struct intel_plane_state *plane_state)
{
	struct drm_i915_private *dev_priv = to_i915(plane->base.dev);
	enum pipe pipe = plane->pipe;
	u32 dvssurf_offset = plane_state->color_plane[0].offset;
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
	u32 dvscntr, dvsscale = 0;
	unsigned long irqflags;

	dvscntr = plane_state->ctl | g4x_sprite_ctl_crtc(crtc_state);

	/* Sizes are 0 based */
	src_w--;
	src_h--;
	crtc_w--;
	crtc_h--;

	if (crtc_w != src_w || crtc_h != src_h)
		dvsscale = DVS_SCALE_ENABLE | (src_w << 16) | src_h;

	linear_offset = intel_fb_xy_to_linear(x, y, plane_state, 0);

	spin_lock_irqsave(&dev_priv->uncore.lock, irqflags);

	I915_WRITE_FW(DVSSTRIDE(pipe), plane_state->color_plane[0].stride);
	I915_WRITE_FW(DVSPOS(pipe), (crtc_y << 16) | crtc_x);
	I915_WRITE_FW(DVSSIZE(pipe), (crtc_h << 16) | crtc_w);
	I915_WRITE_FW(DVSSCALE(pipe), dvsscale);

	if (key->flags) {
		I915_WRITE_FW(DVSKEYVAL(pipe), key->min_value);
		I915_WRITE_FW(DVSKEYMSK(pipe), key->channel_mask);
		I915_WRITE_FW(DVSKEYMAX(pipe), key->max_value);
	}

	I915_WRITE_FW(DVSLINOFF(pipe), linear_offset);
	I915_WRITE_FW(DVSTILEOFF(pipe), (y << 16) | x);

	/*
	 * The control register self-arms if the plane was previously
	 * disabled. Try to make the plane enable atomic by writing
	 * the control register just before the surface register.
	 */
	I915_WRITE_FW(DVSCNTR(pipe), dvscntr);
	I915_WRITE_FW(DVSSURF(pipe),
		      intel_plane_ggtt_offset(plane_state) + dvssurf_offset);

	if (IS_G4X(dev_priv))
		g4x_update_gamma(plane_state);
	else
		ilk_update_gamma(plane_state);

	spin_unlock_irqrestore(&dev_priv->uncore.lock, irqflags);
}