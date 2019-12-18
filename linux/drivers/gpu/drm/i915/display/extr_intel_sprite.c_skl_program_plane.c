#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u32 ;
struct TYPE_8__ {int x1; int y1; } ;
struct TYPE_9__ {int alpha; struct drm_framebuffer* fb; int /*<<< orphan*/  src; TYPE_2__ dst; } ;
struct drm_intel_sprite_colorkey {int max_value; int channel_mask; int min_value; } ;
struct intel_plane_state {int color_ctl; scalar_t__ scaler_id; TYPE_5__* color_plane; TYPE_3__ base; struct intel_plane* linked_plane; struct drm_intel_sprite_colorkey ckey; } ;
struct TYPE_7__ {int /*<<< orphan*/  dev; } ;
struct intel_plane {int id; int pipe; TYPE_1__ base; } ;
struct intel_crtc_state {int dummy; } ;
struct TYPE_12__ {int /*<<< orphan*/  lock; } ;
struct drm_i915_private {TYPE_6__ uncore; } ;
struct drm_framebuffer {TYPE_4__* format; } ;
typedef  enum plane_id { ____Placeholder_plane_id } plane_id ;
typedef  enum pipe { ____Placeholder_pipe } pipe ;
struct TYPE_11__ {int offset; int x; int y; } ;
struct TYPE_10__ {scalar_t__ is_yuv; } ;

/* Variables and functions */
 int /*<<< orphan*/  I915_WRITE_FW (int /*<<< orphan*/ ,int) ; 
 int INTEL_GEN (struct drm_i915_private*) ; 
 scalar_t__ IS_GEMINILAKE (struct drm_i915_private*) ; 
 int /*<<< orphan*/  MISSING_CASE (scalar_t__) ; 
 int /*<<< orphan*/  PLANE_AUX_DIST (int,int) ; 
 int /*<<< orphan*/  PLANE_AUX_OFFSET (int,int) ; 
 int /*<<< orphan*/  PLANE_COLOR_CTL (int,int) ; 
 int /*<<< orphan*/  PLANE_CTL (int,int) ; 
 int /*<<< orphan*/  PLANE_CUS_CTL (int,int) ; 
 int PLANE_CUS_ENABLE ; 
 int PLANE_CUS_HPHASE_0 ; 
 int PLANE_CUS_PLANE_6 ; 
 int PLANE_CUS_PLANE_7 ; 
 int PLANE_CUS_VPHASE_0_25 ; 
 int PLANE_CUS_VPHASE_SIGN_NEGATIVE ; 
 int /*<<< orphan*/  PLANE_KEYMAX (int,int) ; 
 int PLANE_KEYMAX_ALPHA (int) ; 
 int /*<<< orphan*/  PLANE_KEYMSK (int,int) ; 
 int PLANE_KEYMSK_ALPHA_ENABLE ; 
 int /*<<< orphan*/  PLANE_KEYVAL (int,int) ; 
 int /*<<< orphan*/  PLANE_OFFSET (int,int) ; 
 int /*<<< orphan*/  PLANE_POS (int,int) ; 
 int /*<<< orphan*/  PLANE_SIZE (int,int) ; 
 scalar_t__ PLANE_SPRITE4 ; 
 scalar_t__ PLANE_SPRITE5 ; 
 int /*<<< orphan*/  PLANE_STRIDE (int,int) ; 
 int /*<<< orphan*/  PLANE_SURF (int,int) ; 
 int drm_rect_height (int /*<<< orphan*/ *) ; 
 int drm_rect_width (int /*<<< orphan*/ *) ; 
 int glk_plane_color_ctl_crtc (struct intel_crtc_state const*) ; 
 scalar_t__ icl_is_hdr_plane (struct drm_i915_private*,int) ; 
 int /*<<< orphan*/  icl_program_input_csc (struct intel_plane*,struct intel_crtc_state const*,struct intel_plane_state const*) ; 
 int intel_plane_ggtt_offset (struct intel_plane_state const*) ; 
 int skl_plane_ctl_crtc (struct intel_crtc_state const*) ; 
 int skl_plane_stride (struct intel_plane_state const*,int) ; 
 int /*<<< orphan*/  skl_program_scaler (struct intel_plane*,struct intel_crtc_state const*,struct intel_plane_state const*) ; 
 int /*<<< orphan*/  skl_write_plane_wm (struct intel_plane*,struct intel_crtc_state const*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
skl_program_plane(struct intel_plane *plane,
		  const struct intel_crtc_state *crtc_state,
		  const struct intel_plane_state *plane_state,
		  int color_plane, bool slave, u32 plane_ctl)
{
	struct drm_i915_private *dev_priv = to_i915(plane->base.dev);
	enum plane_id plane_id = plane->id;
	enum pipe pipe = plane->pipe;
	const struct drm_intel_sprite_colorkey *key = &plane_state->ckey;
	u32 surf_addr = plane_state->color_plane[color_plane].offset;
	u32 stride = skl_plane_stride(plane_state, color_plane);
	u32 aux_stride = skl_plane_stride(plane_state, 1);
	int crtc_x = plane_state->base.dst.x1;
	int crtc_y = plane_state->base.dst.y1;
	u32 x = plane_state->color_plane[color_plane].x;
	u32 y = plane_state->color_plane[color_plane].y;
	u32 src_w = drm_rect_width(&plane_state->base.src) >> 16;
	u32 src_h = drm_rect_height(&plane_state->base.src) >> 16;
	struct intel_plane *linked = plane_state->linked_plane;
	const struct drm_framebuffer *fb = plane_state->base.fb;
	u8 alpha = plane_state->base.alpha >> 8;
	u32 plane_color_ctl = 0;
	unsigned long irqflags;
	u32 keymsk, keymax;

	plane_ctl |= skl_plane_ctl_crtc(crtc_state);

	if (INTEL_GEN(dev_priv) >= 10 || IS_GEMINILAKE(dev_priv))
		plane_color_ctl = plane_state->color_ctl |
			glk_plane_color_ctl_crtc(crtc_state);

	/* Sizes are 0 based */
	src_w--;
	src_h--;

	keymax = (key->max_value & 0xffffff) | PLANE_KEYMAX_ALPHA(alpha);

	keymsk = key->channel_mask & 0x7ffffff;
	if (alpha < 0xff)
		keymsk |= PLANE_KEYMSK_ALPHA_ENABLE;

	/* The scaler will handle the output position */
	if (plane_state->scaler_id >= 0) {
		crtc_x = 0;
		crtc_y = 0;
	}

	spin_lock_irqsave(&dev_priv->uncore.lock, irqflags);

	I915_WRITE_FW(PLANE_STRIDE(pipe, plane_id), stride);
	I915_WRITE_FW(PLANE_POS(pipe, plane_id), (crtc_y << 16) | crtc_x);
	I915_WRITE_FW(PLANE_SIZE(pipe, plane_id), (src_h << 16) | src_w);
	I915_WRITE_FW(PLANE_AUX_DIST(pipe, plane_id),
		      (plane_state->color_plane[1].offset - surf_addr) | aux_stride);

	if (icl_is_hdr_plane(dev_priv, plane_id)) {
		u32 cus_ctl = 0;

		if (linked) {
			/* Enable and use MPEG-2 chroma siting */
			cus_ctl = PLANE_CUS_ENABLE |
				PLANE_CUS_HPHASE_0 |
				PLANE_CUS_VPHASE_SIGN_NEGATIVE |
				PLANE_CUS_VPHASE_0_25;

			if (linked->id == PLANE_SPRITE5)
				cus_ctl |= PLANE_CUS_PLANE_7;
			else if (linked->id == PLANE_SPRITE4)
				cus_ctl |= PLANE_CUS_PLANE_6;
			else
				MISSING_CASE(linked->id);
		}

		I915_WRITE_FW(PLANE_CUS_CTL(pipe, plane_id), cus_ctl);
	}

	if (INTEL_GEN(dev_priv) >= 10 || IS_GEMINILAKE(dev_priv))
		I915_WRITE_FW(PLANE_COLOR_CTL(pipe, plane_id), plane_color_ctl);

	if (fb->format->is_yuv && icl_is_hdr_plane(dev_priv, plane_id))
		icl_program_input_csc(plane, crtc_state, plane_state);

	skl_write_plane_wm(plane, crtc_state);

	I915_WRITE_FW(PLANE_KEYVAL(pipe, plane_id), key->min_value);
	I915_WRITE_FW(PLANE_KEYMSK(pipe, plane_id), keymsk);
	I915_WRITE_FW(PLANE_KEYMAX(pipe, plane_id), keymax);

	I915_WRITE_FW(PLANE_OFFSET(pipe, plane_id), (y << 16) | x);

	if (INTEL_GEN(dev_priv) < 11)
		I915_WRITE_FW(PLANE_AUX_OFFSET(pipe, plane_id),
			      (plane_state->color_plane[1].y << 16) |
			      plane_state->color_plane[1].x);

	/*
	 * The control register self-arms if the plane was previously
	 * disabled. Try to make the plane enable atomic by writing
	 * the control register just before the surface register.
	 */
	I915_WRITE_FW(PLANE_CTL(pipe, plane_id), plane_ctl);
	I915_WRITE_FW(PLANE_SURF(pipe, plane_id),
		      intel_plane_ggtt_offset(plane_state) + surf_addr);

	if (!slave && plane_state->scaler_id >= 0)
		skl_program_scaler(plane, crtc_state, plane_state);

	spin_unlock_irqrestore(&dev_priv->uncore.lock, irqflags);
}