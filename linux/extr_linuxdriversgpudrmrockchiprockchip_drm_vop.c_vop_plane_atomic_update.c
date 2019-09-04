#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct vop_win_data {TYPE_2__* phy; } ;
struct vop_win {struct vop_win_data* data; } ;
struct vop {int /*<<< orphan*/  reg_lock; int /*<<< orphan*/  is_enabled; } ;
struct rockchip_gem_object {int dma_addr; } ;
struct drm_rect {unsigned int x1; unsigned int y1; } ;
struct drm_plane_state {int /*<<< orphan*/  visible; struct drm_rect dst; struct drm_rect src; struct drm_framebuffer* fb; struct drm_crtc* crtc; } ;
struct drm_plane {struct drm_plane_state* state; } ;
struct drm_gem_object {int dummy; } ;
struct drm_framebuffer {int* pitches; unsigned long* offsets; TYPE_3__* format; struct drm_gem_object** obj; } ;
struct TYPE_4__ {unsigned int htotal; unsigned int hsync_start; unsigned int vtotal; unsigned int vsync_start; } ;
struct drm_crtc {TYPE_1__ mode; } ;
typedef  int dma_addr_t ;
struct TYPE_6__ {int* cpp; scalar_t__ has_alpha; int /*<<< orphan*/  format; scalar_t__ is_yuv; } ;
struct TYPE_5__ {scalar_t__ scl; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALPHA_NO_SATURATION ; 
 int /*<<< orphan*/  ALPHA_ONE ; 
 int /*<<< orphan*/  ALPHA_PER_PIX ; 
 int /*<<< orphan*/  ALPHA_SRC_INVERSE ; 
 int /*<<< orphan*/  ALPHA_SRC_PRE_MUL ; 
 int /*<<< orphan*/  ALPHA_STRAIGHT ; 
 int DIV_ROUND_UP (int,int) ; 
 int DST_FACTOR_M0 (int /*<<< orphan*/ ) ; 
 int SRC_ALPHA_CAL_M0 (int /*<<< orphan*/ ) ; 
 int SRC_ALPHA_EN (int) ; 
 int SRC_ALPHA_M0 (int /*<<< orphan*/ ) ; 
 int SRC_BLEND_M0 (int /*<<< orphan*/ ) ; 
 int SRC_COLOR_M0 (int /*<<< orphan*/ ) ; 
 int SRC_FACTOR_M0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VOP_WIN_SET (struct vop*,struct vop_win_data const*,int,int) ; 
 int VOP_WIN_TO_INDEX (struct vop_win*) ; 
 scalar_t__ WARN_ON (int) ; 
 int drm_format_horz_chroma_subsampling (int /*<<< orphan*/ ) ; 
 int drm_format_vert_chroma_subsampling (int /*<<< orphan*/ ) ; 
 int drm_rect_height (struct drm_rect*) ; 
 int drm_rect_width (struct drm_rect*) ; 
 int dst_alpha_ctl ; 
 int enable ; 
 int has_rb_swapped (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scl_vop_cal_scl_fac (struct vop*,struct vop_win_data const*,unsigned int,unsigned int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int src_alpha_ctl ; 
 struct rockchip_gem_object* to_rockchip_obj (struct drm_gem_object*) ; 
 struct vop* to_vop (struct drm_crtc*) ; 
 struct vop_win* to_vop_win (struct drm_plane*) ; 
 int uv_mst ; 
 int uv_vir ; 
 int vop_convert_format (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vop_plane_atomic_disable (struct drm_plane*,struct drm_plane_state*) ; 
 int yrgb_mst ; 
 int yrgb_vir ; 

__attribute__((used)) static void vop_plane_atomic_update(struct drm_plane *plane,
		struct drm_plane_state *old_state)
{
	struct drm_plane_state *state = plane->state;
	struct drm_crtc *crtc = state->crtc;
	struct vop_win *vop_win = to_vop_win(plane);
	const struct vop_win_data *win = vop_win->data;
	struct vop *vop = to_vop(state->crtc);
	struct drm_framebuffer *fb = state->fb;
	unsigned int actual_w, actual_h;
	unsigned int dsp_stx, dsp_sty;
	uint32_t act_info, dsp_info, dsp_st;
	struct drm_rect *src = &state->src;
	struct drm_rect *dest = &state->dst;
	struct drm_gem_object *obj, *uv_obj;
	struct rockchip_gem_object *rk_obj, *rk_uv_obj;
	unsigned long offset;
	dma_addr_t dma_addr;
	uint32_t val;
	bool rb_swap;
	int win_index = VOP_WIN_TO_INDEX(vop_win);
	int format;

	/*
	 * can't update plane when vop is disabled.
	 */
	if (WARN_ON(!crtc))
		return;

	if (WARN_ON(!vop->is_enabled))
		return;

	if (!state->visible) {
		vop_plane_atomic_disable(plane, old_state);
		return;
	}

	obj = fb->obj[0];
	rk_obj = to_rockchip_obj(obj);

	actual_w = drm_rect_width(src) >> 16;
	actual_h = drm_rect_height(src) >> 16;
	act_info = (actual_h - 1) << 16 | ((actual_w - 1) & 0xffff);

	dsp_info = (drm_rect_height(dest) - 1) << 16;
	dsp_info |= (drm_rect_width(dest) - 1) & 0xffff;

	dsp_stx = dest->x1 + crtc->mode.htotal - crtc->mode.hsync_start;
	dsp_sty = dest->y1 + crtc->mode.vtotal - crtc->mode.vsync_start;
	dsp_st = dsp_sty << 16 | (dsp_stx & 0xffff);

	offset = (src->x1 >> 16) * fb->format->cpp[0];
	offset += (src->y1 >> 16) * fb->pitches[0];
	dma_addr = rk_obj->dma_addr + offset + fb->offsets[0];

	format = vop_convert_format(fb->format->format);

	spin_lock(&vop->reg_lock);

	VOP_WIN_SET(vop, win, format, format);
	VOP_WIN_SET(vop, win, yrgb_vir, DIV_ROUND_UP(fb->pitches[0], 4));
	VOP_WIN_SET(vop, win, yrgb_mst, dma_addr);
	if (fb->format->is_yuv) {
		int hsub = drm_format_horz_chroma_subsampling(fb->format->format);
		int vsub = drm_format_vert_chroma_subsampling(fb->format->format);
		int bpp = fb->format->cpp[1];

		uv_obj = fb->obj[1];
		rk_uv_obj = to_rockchip_obj(uv_obj);

		offset = (src->x1 >> 16) * bpp / hsub;
		offset += (src->y1 >> 16) * fb->pitches[1] / vsub;

		dma_addr = rk_uv_obj->dma_addr + offset + fb->offsets[1];
		VOP_WIN_SET(vop, win, uv_vir, DIV_ROUND_UP(fb->pitches[1], 4));
		VOP_WIN_SET(vop, win, uv_mst, dma_addr);
	}

	if (win->phy->scl)
		scl_vop_cal_scl_fac(vop, win, actual_w, actual_h,
				    drm_rect_width(dest), drm_rect_height(dest),
				    fb->format->format);

	VOP_WIN_SET(vop, win, act_info, act_info);
	VOP_WIN_SET(vop, win, dsp_info, dsp_info);
	VOP_WIN_SET(vop, win, dsp_st, dsp_st);

	rb_swap = has_rb_swapped(fb->format->format);
	VOP_WIN_SET(vop, win, rb_swap, rb_swap);

	/*
	 * Blending win0 with the background color doesn't seem to work
	 * correctly. We only get the background color, no matter the contents
	 * of the win0 framebuffer.  However, blending pre-multiplied color
	 * with the default opaque black default background color is a no-op,
	 * so we can just disable blending to get the correct result.
	 */
	if (fb->format->has_alpha && win_index > 0) {
		VOP_WIN_SET(vop, win, dst_alpha_ctl,
			    DST_FACTOR_M0(ALPHA_SRC_INVERSE));
		val = SRC_ALPHA_EN(1) | SRC_COLOR_M0(ALPHA_SRC_PRE_MUL) |
			SRC_ALPHA_M0(ALPHA_STRAIGHT) |
			SRC_BLEND_M0(ALPHA_PER_PIX) |
			SRC_ALPHA_CAL_M0(ALPHA_NO_SATURATION) |
			SRC_FACTOR_M0(ALPHA_ONE);
		VOP_WIN_SET(vop, win, src_alpha_ctl, val);
	} else {
		VOP_WIN_SET(vop, win, src_alpha_ctl, SRC_ALPHA_EN(0));
	}

	VOP_WIN_SET(vop, win, enable, 1);
	spin_unlock(&vop->reg_lock);
}