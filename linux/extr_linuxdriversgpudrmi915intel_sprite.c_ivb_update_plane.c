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
typedef  int uint32_t ;
typedef  int u32 ;
struct TYPE_11__ {int x1; int y1; } ;
struct TYPE_9__ {TYPE_5__ src; TYPE_5__ dst; struct drm_framebuffer* fb; } ;
struct TYPE_8__ {int offset; int x; int y; } ;
struct drm_intel_sprite_colorkey {int min_value; int max_value; int channel_mask; scalar_t__ flags; } ;
struct intel_plane_state {int ctl; TYPE_3__ base; TYPE_2__ main; struct drm_intel_sprite_colorkey ckey; } ;
struct TYPE_7__ {int /*<<< orphan*/  dev; } ;
struct intel_plane {int pipe; scalar_t__ can_scale; TYPE_1__ base; } ;
struct intel_crtc_state {int dummy; } ;
struct TYPE_10__ {int /*<<< orphan*/  lock; } ;
struct drm_i915_private {TYPE_4__ uncore; } ;
struct drm_framebuffer {int* pitches; scalar_t__ modifier; } ;
typedef  enum pipe { ____Placeholder_pipe } pipe ;

/* Variables and functions */
 scalar_t__ I915_FORMAT_MOD_X_TILED ; 
 int /*<<< orphan*/  I915_WRITE_FW (int /*<<< orphan*/ ,int) ; 
 scalar_t__ IS_BROADWELL (struct drm_i915_private*) ; 
 scalar_t__ IS_HASWELL (struct drm_i915_private*) ; 
 int /*<<< orphan*/  POSTING_READ_FW (int /*<<< orphan*/ ) ; 
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
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ivb_update_plane(struct intel_plane *plane,
		 const struct intel_crtc_state *crtc_state,
		 const struct intel_plane_state *plane_state)
{
	struct drm_i915_private *dev_priv = to_i915(plane->base.dev);
	const struct drm_framebuffer *fb = plane_state->base.fb;
	enum pipe pipe = plane->pipe;
	u32 sprctl = plane_state->ctl, sprscale = 0;
	u32 sprsurf_offset = plane_state->main.offset;
	u32 linear_offset;
	const struct drm_intel_sprite_colorkey *key = &plane_state->ckey;
	int crtc_x = plane_state->base.dst.x1;
	int crtc_y = plane_state->base.dst.y1;
	uint32_t crtc_w = drm_rect_width(&plane_state->base.dst);
	uint32_t crtc_h = drm_rect_height(&plane_state->base.dst);
	uint32_t x = plane_state->main.x;
	uint32_t y = plane_state->main.y;
	uint32_t src_w = drm_rect_width(&plane_state->base.src) >> 16;
	uint32_t src_h = drm_rect_height(&plane_state->base.src) >> 16;
	unsigned long irqflags;

	/* Sizes are 0 based */
	src_w--;
	src_h--;
	crtc_w--;
	crtc_h--;

	if (crtc_w != src_w || crtc_h != src_h)
		sprscale = SPRITE_SCALE_ENABLE | (src_w << 16) | src_h;

	linear_offset = intel_fb_xy_to_linear(x, y, plane_state, 0);

	spin_lock_irqsave(&dev_priv->uncore.lock, irqflags);

	if (key->flags) {
		I915_WRITE_FW(SPRKEYVAL(pipe), key->min_value);
		I915_WRITE_FW(SPRKEYMAX(pipe), key->max_value);
		I915_WRITE_FW(SPRKEYMSK(pipe), key->channel_mask);
	}

	I915_WRITE_FW(SPRSTRIDE(pipe), fb->pitches[0]);
	I915_WRITE_FW(SPRPOS(pipe), (crtc_y << 16) | crtc_x);

	/* HSW consolidates SPRTILEOFF and SPRLINOFF into a single SPROFFSET
	 * register */
	if (IS_HASWELL(dev_priv) || IS_BROADWELL(dev_priv))
		I915_WRITE_FW(SPROFFSET(pipe), (y << 16) | x);
	else if (fb->modifier == I915_FORMAT_MOD_X_TILED)
		I915_WRITE_FW(SPRTILEOFF(pipe), (y << 16) | x);
	else
		I915_WRITE_FW(SPRLINOFF(pipe), linear_offset);

	I915_WRITE_FW(SPRSIZE(pipe), (crtc_h << 16) | crtc_w);
	if (plane->can_scale)
		I915_WRITE_FW(SPRSCALE(pipe), sprscale);
	I915_WRITE_FW(SPRCTL(pipe), sprctl);
	I915_WRITE_FW(SPRSURF(pipe),
		      intel_plane_ggtt_offset(plane_state) + sprsurf_offset);
	POSTING_READ_FW(SPRSURF(pipe));

	spin_unlock_irqrestore(&dev_priv->uncore.lock, irqflags);
}