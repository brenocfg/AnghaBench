#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  int u32 ;
typedef  scalar_t__ u16 ;
struct intel_scaler {int mode; } ;
struct TYPE_13__ {int offset; int y; int x; } ;
struct TYPE_17__ {int x1; int y1; } ;
struct TYPE_12__ {unsigned int rotation; TYPE_8__ src; TYPE_8__ dst; struct drm_framebuffer* fb; } ;
struct TYPE_11__ {int offset; int x; int y; } ;
struct drm_intel_sprite_colorkey {int min_value; int max_value; int channel_mask; scalar_t__ flags; } ;
struct intel_plane_state {int ctl; int color_ctl; int scaler_id; TYPE_4__ aux; TYPE_3__ base; TYPE_2__ main; struct drm_intel_sprite_colorkey ckey; } ;
struct TYPE_10__ {int /*<<< orphan*/  dev; } ;
struct intel_plane {int id; int pipe; TYPE_1__ base; } ;
struct TYPE_14__ {struct intel_scaler* scalers; } ;
struct intel_crtc_state {TYPE_5__ scaler_state; } ;
struct TYPE_16__ {int /*<<< orphan*/  lock; } ;
struct drm_i915_private {TYPE_7__ uncore; } ;
struct drm_framebuffer {TYPE_6__* format; } ;
typedef  enum plane_id { ____Placeholder_plane_id } plane_id ;
typedef  enum pipe { ____Placeholder_pipe } pipe ;
struct TYPE_15__ {scalar_t__ format; } ;

/* Variables and functions */
 scalar_t__ DRM_FORMAT_NV12 ; 
 int /*<<< orphan*/  I915_WRITE_FW (int /*<<< orphan*/ ,int) ; 
 int INTEL_GEN (struct drm_i915_private*) ; 
 scalar_t__ IS_GEMINILAKE (struct drm_i915_private*) ; 
 int /*<<< orphan*/  PLANE_AUX_DIST (int,int) ; 
 int /*<<< orphan*/  PLANE_AUX_OFFSET (int,int) ; 
 int /*<<< orphan*/  PLANE_COLOR_CTL (int,int) ; 
 int /*<<< orphan*/  PLANE_CTL (int,int) ; 
 int /*<<< orphan*/  PLANE_KEYMAX (int,int) ; 
 int /*<<< orphan*/  PLANE_KEYMSK (int,int) ; 
 int /*<<< orphan*/  PLANE_KEYVAL (int,int) ; 
 int /*<<< orphan*/  PLANE_OFFSET (int,int) ; 
 int /*<<< orphan*/  PLANE_POS (int,int) ; 
 int /*<<< orphan*/  PLANE_SIZE (int,int) ; 
 int /*<<< orphan*/  PLANE_STRIDE (int,int) ; 
 int /*<<< orphan*/  PLANE_SURF (int,int) ; 
 int /*<<< orphan*/  POSTING_READ_FW (int /*<<< orphan*/ ) ; 
 int PS_PLANE_SEL (int) ; 
 int PS_SCALER_EN ; 
 int PS_UV_RGB_PHASE (scalar_t__) ; 
 int PS_Y_PHASE (scalar_t__) ; 
 int /*<<< orphan*/  SKL_PS_CTRL (int,int) ; 
 int /*<<< orphan*/  SKL_PS_HPHASE (int,int) ; 
 int /*<<< orphan*/  SKL_PS_PWR_GATE (int,int) ; 
 int /*<<< orphan*/  SKL_PS_VPHASE (int,int) ; 
 int /*<<< orphan*/  SKL_PS_WIN_POS (int,int) ; 
 int /*<<< orphan*/  SKL_PS_WIN_SZ (int,int) ; 
 int drm_rect_height (TYPE_8__*) ; 
 int drm_rect_width (TYPE_8__*) ; 
 int intel_plane_ggtt_offset (struct intel_plane_state const*) ; 
 int skl_plane_stride (struct drm_framebuffer const*,int,unsigned int) ; 
 scalar_t__ skl_scaler_calc_phase (int,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 

void
skl_update_plane(struct intel_plane *plane,
		 const struct intel_crtc_state *crtc_state,
		 const struct intel_plane_state *plane_state)
{
	struct drm_i915_private *dev_priv = to_i915(plane->base.dev);
	const struct drm_framebuffer *fb = plane_state->base.fb;
	enum plane_id plane_id = plane->id;
	enum pipe pipe = plane->pipe;
	u32 plane_ctl = plane_state->ctl;
	const struct drm_intel_sprite_colorkey *key = &plane_state->ckey;
	u32 surf_addr = plane_state->main.offset;
	unsigned int rotation = plane_state->base.rotation;
	u32 stride = skl_plane_stride(fb, 0, rotation);
	u32 aux_stride = skl_plane_stride(fb, 1, rotation);
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

	spin_lock_irqsave(&dev_priv->uncore.lock, irqflags);

	if (INTEL_GEN(dev_priv) >= 10 || IS_GEMINILAKE(dev_priv))
		I915_WRITE_FW(PLANE_COLOR_CTL(pipe, plane_id),
			      plane_state->color_ctl);

	if (key->flags) {
		I915_WRITE_FW(PLANE_KEYVAL(pipe, plane_id), key->min_value);
		I915_WRITE_FW(PLANE_KEYMAX(pipe, plane_id), key->max_value);
		I915_WRITE_FW(PLANE_KEYMSK(pipe, plane_id), key->channel_mask);
	}

	I915_WRITE_FW(PLANE_OFFSET(pipe, plane_id), (y << 16) | x);
	I915_WRITE_FW(PLANE_STRIDE(pipe, plane_id), stride);
	I915_WRITE_FW(PLANE_SIZE(pipe, plane_id), (src_h << 16) | src_w);
	I915_WRITE_FW(PLANE_AUX_DIST(pipe, plane_id),
		      (plane_state->aux.offset - surf_addr) | aux_stride);
	I915_WRITE_FW(PLANE_AUX_OFFSET(pipe, plane_id),
		      (plane_state->aux.y << 16) | plane_state->aux.x);

	/* program plane scaler */
	if (plane_state->scaler_id >= 0) {
		int scaler_id = plane_state->scaler_id;
		const struct intel_scaler *scaler =
			&crtc_state->scaler_state.scalers[scaler_id];
		u16 y_hphase, uv_rgb_hphase;
		u16 y_vphase, uv_rgb_vphase;

		/* TODO: handle sub-pixel coordinates */
		if (fb->format->format == DRM_FORMAT_NV12) {
			y_hphase = skl_scaler_calc_phase(1, false);
			y_vphase = skl_scaler_calc_phase(1, false);

			/* MPEG2 chroma siting convention */
			uv_rgb_hphase = skl_scaler_calc_phase(2, true);
			uv_rgb_vphase = skl_scaler_calc_phase(2, false);
		} else {
			/* not used */
			y_hphase = 0;
			y_vphase = 0;

			uv_rgb_hphase = skl_scaler_calc_phase(1, false);
			uv_rgb_vphase = skl_scaler_calc_phase(1, false);
		}

		I915_WRITE_FW(SKL_PS_CTRL(pipe, scaler_id),
			      PS_SCALER_EN | PS_PLANE_SEL(plane_id) | scaler->mode);
		I915_WRITE_FW(SKL_PS_PWR_GATE(pipe, scaler_id), 0);
		I915_WRITE_FW(SKL_PS_VPHASE(pipe, scaler_id),
			      PS_Y_PHASE(y_vphase) | PS_UV_RGB_PHASE(uv_rgb_vphase));
		I915_WRITE_FW(SKL_PS_HPHASE(pipe, scaler_id),
			      PS_Y_PHASE(y_hphase) | PS_UV_RGB_PHASE(uv_rgb_hphase));
		I915_WRITE_FW(SKL_PS_WIN_POS(pipe, scaler_id), (crtc_x << 16) | crtc_y);
		I915_WRITE_FW(SKL_PS_WIN_SZ(pipe, scaler_id),
			      ((crtc_w + 1) << 16)|(crtc_h + 1));

		I915_WRITE_FW(PLANE_POS(pipe, plane_id), 0);
	} else {
		I915_WRITE_FW(PLANE_POS(pipe, plane_id), (crtc_y << 16) | crtc_x);
	}

	I915_WRITE_FW(PLANE_CTL(pipe, plane_id), plane_ctl);
	I915_WRITE_FW(PLANE_SURF(pipe, plane_id),
		      intel_plane_ggtt_offset(plane_state) + surf_addr);
	POSTING_READ_FW(PLANE_SURF(pipe, plane_id));

	spin_unlock_irqrestore(&dev_priv->uncore.lock, irqflags);
}