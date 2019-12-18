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
struct drm_intel_sprite_colorkey {int min_value; int channel_mask; int max_value; scalar_t__ flags; } ;
struct intel_plane_state {int ctl; TYPE_3__* color_plane; TYPE_2__ base; struct drm_intel_sprite_colorkey ckey; } ;
struct TYPE_7__ {int /*<<< orphan*/  dev; } ;
struct intel_plane {int pipe; int id; TYPE_1__ base; } ;
struct intel_crtc_state {int dummy; } ;
struct TYPE_10__ {int /*<<< orphan*/  lock; } ;
struct drm_i915_private {TYPE_4__ uncore; } ;
typedef  enum plane_id { ____Placeholder_plane_id } plane_id ;
typedef  enum pipe { ____Placeholder_pipe } pipe ;
struct TYPE_9__ {int offset; int x; int y; int stride; } ;

/* Variables and functions */
 int /*<<< orphan*/  I915_WRITE_FW (int /*<<< orphan*/ ,int) ; 
 scalar_t__ IS_CHERRYVIEW (struct drm_i915_private*) ; 
 int PIPE_B ; 
 int /*<<< orphan*/  SPCNTR (int,int) ; 
 int /*<<< orphan*/  SPCONSTALPHA (int,int) ; 
 int /*<<< orphan*/  SPKEYMAXVAL (int,int) ; 
 int /*<<< orphan*/  SPKEYMINVAL (int,int) ; 
 int /*<<< orphan*/  SPKEYMSK (int,int) ; 
 int /*<<< orphan*/  SPLINOFF (int,int) ; 
 int /*<<< orphan*/  SPPOS (int,int) ; 
 int /*<<< orphan*/  SPSIZE (int,int) ; 
 int /*<<< orphan*/  SPSTRIDE (int,int) ; 
 int /*<<< orphan*/  SPSURF (int,int) ; 
 int /*<<< orphan*/  SPTILEOFF (int,int) ; 
 int /*<<< orphan*/  chv_update_csc (struct intel_plane_state const*) ; 
 int drm_rect_height (TYPE_5__*) ; 
 int drm_rect_width (TYPE_5__*) ; 
 int intel_fb_xy_to_linear (int,int,struct intel_plane_state const*,int /*<<< orphan*/ ) ; 
 int intel_plane_ggtt_offset (struct intel_plane_state const*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 
 int vlv_sprite_ctl_crtc (struct intel_crtc_state const*) ; 
 int /*<<< orphan*/  vlv_update_clrc (struct intel_plane_state const*) ; 
 int /*<<< orphan*/  vlv_update_gamma (struct intel_plane_state const*) ; 

__attribute__((used)) static void
vlv_update_plane(struct intel_plane *plane,
		 const struct intel_crtc_state *crtc_state,
		 const struct intel_plane_state *plane_state)
{
	struct drm_i915_private *dev_priv = to_i915(plane->base.dev);
	enum pipe pipe = plane->pipe;
	enum plane_id plane_id = plane->id;
	u32 sprsurf_offset = plane_state->color_plane[0].offset;
	u32 linear_offset;
	const struct drm_intel_sprite_colorkey *key = &plane_state->ckey;
	int crtc_x = plane_state->base.dst.x1;
	int crtc_y = plane_state->base.dst.y1;
	u32 crtc_w = drm_rect_width(&plane_state->base.dst);
	u32 crtc_h = drm_rect_height(&plane_state->base.dst);
	u32 x = plane_state->color_plane[0].x;
	u32 y = plane_state->color_plane[0].y;
	unsigned long irqflags;
	u32 sprctl;

	sprctl = plane_state->ctl | vlv_sprite_ctl_crtc(crtc_state);

	/* Sizes are 0 based */
	crtc_w--;
	crtc_h--;

	linear_offset = intel_fb_xy_to_linear(x, y, plane_state, 0);

	spin_lock_irqsave(&dev_priv->uncore.lock, irqflags);

	I915_WRITE_FW(SPSTRIDE(pipe, plane_id),
		      plane_state->color_plane[0].stride);
	I915_WRITE_FW(SPPOS(pipe, plane_id), (crtc_y << 16) | crtc_x);
	I915_WRITE_FW(SPSIZE(pipe, plane_id), (crtc_h << 16) | crtc_w);
	I915_WRITE_FW(SPCONSTALPHA(pipe, plane_id), 0);

	if (IS_CHERRYVIEW(dev_priv) && pipe == PIPE_B)
		chv_update_csc(plane_state);

	if (key->flags) {
		I915_WRITE_FW(SPKEYMINVAL(pipe, plane_id), key->min_value);
		I915_WRITE_FW(SPKEYMSK(pipe, plane_id), key->channel_mask);
		I915_WRITE_FW(SPKEYMAXVAL(pipe, plane_id), key->max_value);
	}

	I915_WRITE_FW(SPLINOFF(pipe, plane_id), linear_offset);
	I915_WRITE_FW(SPTILEOFF(pipe, plane_id), (y << 16) | x);

	/*
	 * The control register self-arms if the plane was previously
	 * disabled. Try to make the plane enable atomic by writing
	 * the control register just before the surface register.
	 */
	I915_WRITE_FW(SPCNTR(pipe, plane_id), sprctl);
	I915_WRITE_FW(SPSURF(pipe, plane_id),
		      intel_plane_ggtt_offset(plane_state) + sprsurf_offset);

	vlv_update_clrc(plane_state);
	vlv_update_gamma(plane_state);

	spin_unlock_irqrestore(&dev_priv->uncore.lock, irqflags);
}