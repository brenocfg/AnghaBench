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
typedef  scalar_t__ u32 ;
struct fimd_context {int /*<<< orphan*/  win_updated; scalar_t__ i80_if; TYPE_6__* driver_data; int /*<<< orphan*/  dev; scalar_t__ regs; scalar_t__ suspended; } ;
struct TYPE_11__ {unsigned int x; unsigned int y; int /*<<< orphan*/  w; } ;
struct TYPE_10__ {unsigned int h; unsigned int w; unsigned int x; unsigned int y; } ;
struct TYPE_8__ {struct drm_framebuffer* fb; } ;
struct exynos_drm_plane_state {TYPE_5__ src; TYPE_4__ crtc; TYPE_2__ base; } ;
struct TYPE_7__ {int /*<<< orphan*/  state; } ;
struct exynos_drm_plane {unsigned int index; TYPE_1__ base; } ;
struct exynos_drm_crtc {struct fimd_context* ctx; } ;
struct drm_framebuffer {unsigned int* pitches; TYPE_3__* format; } ;
typedef  scalar_t__ dma_addr_t ;
struct TYPE_12__ {scalar_t__ has_shadowcon; } ;
struct TYPE_9__ {unsigned int* cpp; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEV_DEBUG_KMS (int /*<<< orphan*/ ,char*,unsigned int,...) ; 
 scalar_t__ VIDOSD_A (unsigned int) ; 
 scalar_t__ VIDOSD_B (unsigned int) ; 
 scalar_t__ VIDOSD_C (unsigned int) ; 
 scalar_t__ VIDOSD_D (unsigned int) ; 
 unsigned long VIDOSDxA_TOPLEFT_X (unsigned int) ; 
 unsigned long VIDOSDxA_TOPLEFT_X_E (unsigned int) ; 
 unsigned long VIDOSDxA_TOPLEFT_Y (unsigned int) ; 
 unsigned long VIDOSDxA_TOPLEFT_Y_E (unsigned int) ; 
 unsigned long VIDOSDxB_BOTRIGHT_X (unsigned int) ; 
 unsigned long VIDOSDxB_BOTRIGHT_X_E (unsigned int) ; 
 unsigned long VIDOSDxB_BOTRIGHT_Y (unsigned int) ; 
 unsigned long VIDOSDxB_BOTRIGHT_Y_E (unsigned int) ; 
 unsigned long VIDW_BUF_SIZE_OFFSET (unsigned int) ; 
 unsigned long VIDW_BUF_SIZE_OFFSET_E (unsigned int) ; 
 unsigned long VIDW_BUF_SIZE_PAGEWIDTH (unsigned int) ; 
 unsigned long VIDW_BUF_SIZE_PAGEWIDTH_E (unsigned int) ; 
 scalar_t__ VIDWx_BUF_END (unsigned int,int /*<<< orphan*/ ) ; 
 scalar_t__ VIDWx_BUF_SIZE (unsigned int,int /*<<< orphan*/ ) ; 
 scalar_t__ VIDWx_BUF_START (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 scalar_t__ exynos_drm_fb_dma_addr (struct drm_framebuffer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fimd_enable_shadow_channel_path (struct fimd_context*,unsigned int,int) ; 
 int /*<<< orphan*/  fimd_enable_video_output (struct fimd_context*,unsigned int,int) ; 
 int /*<<< orphan*/  fimd_win_set_colkey (struct fimd_context*,unsigned int) ; 
 int /*<<< orphan*/  fimd_win_set_pixfmt (struct fimd_context*,unsigned int,struct drm_framebuffer*,int /*<<< orphan*/ ) ; 
 struct exynos_drm_plane_state* to_exynos_plane_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (unsigned long,scalar_t__) ; 

__attribute__((used)) static void fimd_update_plane(struct exynos_drm_crtc *crtc,
			      struct exynos_drm_plane *plane)
{
	struct exynos_drm_plane_state *state =
				to_exynos_plane_state(plane->base.state);
	struct fimd_context *ctx = crtc->ctx;
	struct drm_framebuffer *fb = state->base.fb;
	dma_addr_t dma_addr;
	unsigned long val, size, offset;
	unsigned int last_x, last_y, buf_offsize, line_size;
	unsigned int win = plane->index;
	unsigned int cpp = fb->format->cpp[0];
	unsigned int pitch = fb->pitches[0];

	if (ctx->suspended)
		return;

	offset = state->src.x * cpp;
	offset += state->src.y * pitch;

	/* buffer start address */
	dma_addr = exynos_drm_fb_dma_addr(fb, 0) + offset;
	val = (unsigned long)dma_addr;
	writel(val, ctx->regs + VIDWx_BUF_START(win, 0));

	/* buffer end address */
	size = pitch * state->crtc.h;
	val = (unsigned long)(dma_addr + size);
	writel(val, ctx->regs + VIDWx_BUF_END(win, 0));

	DRM_DEV_DEBUG_KMS(ctx->dev,
			  "start addr = 0x%lx, end addr = 0x%lx, size = 0x%lx\n",
			  (unsigned long)dma_addr, val, size);
	DRM_DEV_DEBUG_KMS(ctx->dev, "ovl_width = %d, ovl_height = %d\n",
			  state->crtc.w, state->crtc.h);

	/* buffer size */
	buf_offsize = pitch - (state->crtc.w * cpp);
	line_size = state->crtc.w * cpp;
	val = VIDW_BUF_SIZE_OFFSET(buf_offsize) |
		VIDW_BUF_SIZE_PAGEWIDTH(line_size) |
		VIDW_BUF_SIZE_OFFSET_E(buf_offsize) |
		VIDW_BUF_SIZE_PAGEWIDTH_E(line_size);
	writel(val, ctx->regs + VIDWx_BUF_SIZE(win, 0));

	/* OSD position */
	val = VIDOSDxA_TOPLEFT_X(state->crtc.x) |
		VIDOSDxA_TOPLEFT_Y(state->crtc.y) |
		VIDOSDxA_TOPLEFT_X_E(state->crtc.x) |
		VIDOSDxA_TOPLEFT_Y_E(state->crtc.y);
	writel(val, ctx->regs + VIDOSD_A(win));

	last_x = state->crtc.x + state->crtc.w;
	if (last_x)
		last_x--;
	last_y = state->crtc.y + state->crtc.h;
	if (last_y)
		last_y--;

	val = VIDOSDxB_BOTRIGHT_X(last_x) | VIDOSDxB_BOTRIGHT_Y(last_y) |
		VIDOSDxB_BOTRIGHT_X_E(last_x) | VIDOSDxB_BOTRIGHT_Y_E(last_y);

	writel(val, ctx->regs + VIDOSD_B(win));

	DRM_DEV_DEBUG_KMS(ctx->dev,
			  "osd pos: tx = %d, ty = %d, bx = %d, by = %d\n",
			  state->crtc.x, state->crtc.y, last_x, last_y);

	/* OSD size */
	if (win != 3 && win != 4) {
		u32 offset = VIDOSD_D(win);
		if (win == 0)
			offset = VIDOSD_C(win);
		val = state->crtc.w * state->crtc.h;
		writel(val, ctx->regs + offset);

		DRM_DEV_DEBUG_KMS(ctx->dev, "osd size = 0x%x\n",
				  (unsigned int)val);
	}

	fimd_win_set_pixfmt(ctx, win, fb, state->src.w);

	/* hardware window 0 doesn't support color key. */
	if (win != 0)
		fimd_win_set_colkey(ctx, win);

	fimd_enable_video_output(ctx, win, true);

	if (ctx->driver_data->has_shadowcon)
		fimd_enable_shadow_channel_path(ctx, win, true);

	if (ctx->i80_if)
		atomic_set(&ctx->win_updated, 1);
}