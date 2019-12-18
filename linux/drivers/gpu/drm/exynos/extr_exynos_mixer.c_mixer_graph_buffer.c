#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct mixer_context {int /*<<< orphan*/  reg_slock; } ;
struct TYPE_10__ {int normalized_zpos; unsigned int pixel_blend_mode; int /*<<< orphan*/  alpha; struct drm_framebuffer* fb; } ;
struct TYPE_9__ {int x; int y; int /*<<< orphan*/  h; int /*<<< orphan*/  w; } ;
struct TYPE_7__ {unsigned int x; unsigned int y; } ;
struct exynos_drm_plane_state {int h_ratio; int v_ratio; TYPE_5__ base; TYPE_4__ src; TYPE_2__ crtc; } ;
struct TYPE_6__ {int /*<<< orphan*/  state; } ;
struct exynos_drm_plane {unsigned int index; TYPE_1__ base; } ;
struct drm_framebuffer {int* pitches; TYPE_3__* format; } ;
typedef  int dma_addr_t ;
struct TYPE_8__ {int format; int* cpp; scalar_t__ has_alpha; } ;

/* Variables and functions */
#define  DRM_FORMAT_ARGB1555 134 
#define  DRM_FORMAT_ARGB4444 133 
#define  DRM_FORMAT_ARGB8888 132 
#define  DRM_FORMAT_RGB565 131 
#define  DRM_FORMAT_XRGB1555 130 
#define  DRM_FORMAT_XRGB4444 129 
#define  DRM_FORMAT_XRGB8888 128 
 unsigned int DRM_MODE_BLEND_PIXEL_NONE ; 
 unsigned int MXR_FORMAT_ARGB1555 ; 
 unsigned int MXR_FORMAT_ARGB4444 ; 
 unsigned int MXR_FORMAT_ARGB8888 ; 
 unsigned int MXR_FORMAT_RGB565 ; 
 int /*<<< orphan*/  MXR_GRAPHIC_BASE (unsigned int) ; 
 int /*<<< orphan*/  MXR_GRAPHIC_CFG (unsigned int) ; 
 int /*<<< orphan*/  MXR_GRAPHIC_DXY (unsigned int) ; 
 int /*<<< orphan*/  MXR_GRAPHIC_SPAN (unsigned int) ; 
 int /*<<< orphan*/  MXR_GRAPHIC_WH (unsigned int) ; 
 int /*<<< orphan*/  MXR_GRP_CFG_FORMAT_MASK ; 
 int /*<<< orphan*/  MXR_GRP_CFG_FORMAT_VAL (unsigned int) ; 
 int MXR_GRP_DXY_DX (unsigned int) ; 
 int MXR_GRP_DXY_DY (unsigned int) ; 
 int MXR_GRP_WH_HEIGHT (int /*<<< orphan*/ ) ; 
 int MXR_GRP_WH_H_SCALE (unsigned int) ; 
 int MXR_GRP_WH_V_SCALE (unsigned int) ; 
 int MXR_GRP_WH_WIDTH (int /*<<< orphan*/ ) ; 
 int exynos_drm_fb_dma_addr (struct drm_framebuffer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mixer_cfg_gfx_blend (struct mixer_context*,unsigned int,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mixer_cfg_layer (struct mixer_context*,unsigned int,unsigned int,int) ; 
 int /*<<< orphan*/  mixer_reg_write (struct mixer_context*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mixer_reg_writemask (struct mixer_context*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mixer_regs_dump (struct mixer_context*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct exynos_drm_plane_state* to_exynos_plane_state (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mixer_graph_buffer(struct mixer_context *ctx,
			       struct exynos_drm_plane *plane)
{
	struct exynos_drm_plane_state *state =
				to_exynos_plane_state(plane->base.state);
	struct drm_framebuffer *fb = state->base.fb;
	unsigned int priority = state->base.normalized_zpos + 1;
	unsigned long flags;
	unsigned int win = plane->index;
	unsigned int x_ratio = 0, y_ratio = 0;
	unsigned int dst_x_offset, dst_y_offset;
	unsigned int pixel_alpha;
	dma_addr_t dma_addr;
	unsigned int fmt;
	u32 val;

	if (fb->format->has_alpha)
		pixel_alpha = state->base.pixel_blend_mode;
	else
		pixel_alpha = DRM_MODE_BLEND_PIXEL_NONE;

	switch (fb->format->format) {
	case DRM_FORMAT_XRGB4444:
	case DRM_FORMAT_ARGB4444:
		fmt = MXR_FORMAT_ARGB4444;
		break;

	case DRM_FORMAT_XRGB1555:
	case DRM_FORMAT_ARGB1555:
		fmt = MXR_FORMAT_ARGB1555;
		break;

	case DRM_FORMAT_RGB565:
		fmt = MXR_FORMAT_RGB565;
		break;

	case DRM_FORMAT_XRGB8888:
	case DRM_FORMAT_ARGB8888:
	default:
		fmt = MXR_FORMAT_ARGB8888;
		break;
	}

	/* ratio is already checked by common plane code */
	x_ratio = state->h_ratio == (1 << 15);
	y_ratio = state->v_ratio == (1 << 15);

	dst_x_offset = state->crtc.x;
	dst_y_offset = state->crtc.y;

	/* translate dma address base s.t. the source image offset is zero */
	dma_addr = exynos_drm_fb_dma_addr(fb, 0)
		+ (state->src.x * fb->format->cpp[0])
		+ (state->src.y * fb->pitches[0]);

	spin_lock_irqsave(&ctx->reg_slock, flags);

	/* setup format */
	mixer_reg_writemask(ctx, MXR_GRAPHIC_CFG(win),
		MXR_GRP_CFG_FORMAT_VAL(fmt), MXR_GRP_CFG_FORMAT_MASK);

	/* setup geometry */
	mixer_reg_write(ctx, MXR_GRAPHIC_SPAN(win),
			fb->pitches[0] / fb->format->cpp[0]);

	val  = MXR_GRP_WH_WIDTH(state->src.w);
	val |= MXR_GRP_WH_HEIGHT(state->src.h);
	val |= MXR_GRP_WH_H_SCALE(x_ratio);
	val |= MXR_GRP_WH_V_SCALE(y_ratio);
	mixer_reg_write(ctx, MXR_GRAPHIC_WH(win), val);

	/* setup offsets in display image */
	val  = MXR_GRP_DXY_DX(dst_x_offset);
	val |= MXR_GRP_DXY_DY(dst_y_offset);
	mixer_reg_write(ctx, MXR_GRAPHIC_DXY(win), val);

	/* set buffer address to mixer */
	mixer_reg_write(ctx, MXR_GRAPHIC_BASE(win), dma_addr);

	mixer_cfg_layer(ctx, win, priority, true);
	mixer_cfg_gfx_blend(ctx, win, pixel_alpha, state->base.alpha);

	spin_unlock_irqrestore(&ctx->reg_slock, flags);

	mixer_regs_dump(ctx);
}