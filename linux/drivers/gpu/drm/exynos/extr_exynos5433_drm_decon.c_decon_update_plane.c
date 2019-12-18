#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned int u32 ;
struct TYPE_14__ {int y; unsigned int w; int h; scalar_t__ x; } ;
struct TYPE_13__ {unsigned int h; } ;
struct TYPE_9__ {struct drm_framebuffer* fb; } ;
struct exynos_drm_plane_state {TYPE_7__ crtc; TYPE_6__ src; TYPE_2__ base; } ;
struct TYPE_8__ {int /*<<< orphan*/  state; } ;
struct exynos_drm_plane {unsigned int index; TYPE_1__ base; } ;
struct TYPE_11__ {int flags; } ;
struct TYPE_12__ {TYPE_4__ mode; } ;
struct exynos_drm_crtc {TYPE_5__ base; struct decon_context* ctx; } ;
struct drm_framebuffer {unsigned int* pitches; TYPE_3__* format; } ;
struct decon_context {int out_type; scalar_t__ addr; } ;
typedef  unsigned int dma_addr_t ;
struct TYPE_10__ {unsigned int* cpp; } ;

/* Variables and functions */
 unsigned int BIT_VAL (unsigned int,int,int) ; 
 unsigned int COORDINATE_X (scalar_t__) ; 
 unsigned int COORDINATE_Y (int) ; 
 scalar_t__ DECON_VIDOSDxA (unsigned int) ; 
 scalar_t__ DECON_VIDOSDxB (unsigned int) ; 
 scalar_t__ DECON_VIDOSDxC (unsigned int) ; 
 scalar_t__ DECON_VIDOSDxD (unsigned int) ; 
 scalar_t__ DECON_VIDW0xADD0B0 (unsigned int) ; 
 scalar_t__ DECON_VIDW0xADD1B0 (unsigned int) ; 
 scalar_t__ DECON_VIDW0xADD2 (unsigned int) ; 
 int /*<<< orphan*/  DECON_WINCONx (unsigned int) ; 
 int DRM_MODE_FLAG_INTERLACE ; 
 int IFTYPE_HDMI ; 
 unsigned int VIDOSD_Wx_ALPHA_B_F (int) ; 
 unsigned int VIDOSD_Wx_ALPHA_G_F (int) ; 
 unsigned int VIDOSD_Wx_ALPHA_R_F (int) ; 
 int /*<<< orphan*/  WINCONx_ENWIN_F ; 
 int /*<<< orphan*/  decon_set_bits (struct decon_context*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  decon_win_set_pixfmt (struct decon_context*,unsigned int,struct drm_framebuffer*) ; 
 unsigned int exynos_drm_fb_dma_addr (struct drm_framebuffer*,int /*<<< orphan*/ ) ; 
 struct exynos_drm_plane_state* to_exynos_plane_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (unsigned int,scalar_t__) ; 

__attribute__((used)) static void decon_update_plane(struct exynos_drm_crtc *crtc,
			       struct exynos_drm_plane *plane)
{
	struct exynos_drm_plane_state *state =
				to_exynos_plane_state(plane->base.state);
	struct decon_context *ctx = crtc->ctx;
	struct drm_framebuffer *fb = state->base.fb;
	unsigned int win = plane->index;
	unsigned int cpp = fb->format->cpp[0];
	unsigned int pitch = fb->pitches[0];
	dma_addr_t dma_addr = exynos_drm_fb_dma_addr(fb, 0);
	u32 val;

	if (crtc->base.mode.flags & DRM_MODE_FLAG_INTERLACE) {
		val = COORDINATE_X(state->crtc.x) |
			COORDINATE_Y(state->crtc.y / 2);
		writel(val, ctx->addr + DECON_VIDOSDxA(win));

		val = COORDINATE_X(state->crtc.x + state->crtc.w - 1) |
			COORDINATE_Y((state->crtc.y + state->crtc.h) / 2 - 1);
		writel(val, ctx->addr + DECON_VIDOSDxB(win));
	} else {
		val = COORDINATE_X(state->crtc.x) | COORDINATE_Y(state->crtc.y);
		writel(val, ctx->addr + DECON_VIDOSDxA(win));

		val = COORDINATE_X(state->crtc.x + state->crtc.w - 1) |
				COORDINATE_Y(state->crtc.y + state->crtc.h - 1);
		writel(val, ctx->addr + DECON_VIDOSDxB(win));
	}

	val = VIDOSD_Wx_ALPHA_R_F(0xff) | VIDOSD_Wx_ALPHA_G_F(0xff) |
		VIDOSD_Wx_ALPHA_B_F(0xff);
	writel(val, ctx->addr + DECON_VIDOSDxC(win));

	val = VIDOSD_Wx_ALPHA_R_F(0x0) | VIDOSD_Wx_ALPHA_G_F(0x0) |
		VIDOSD_Wx_ALPHA_B_F(0x0);
	writel(val, ctx->addr + DECON_VIDOSDxD(win));

	writel(dma_addr, ctx->addr + DECON_VIDW0xADD0B0(win));

	val = dma_addr + pitch * state->src.h;
	writel(val, ctx->addr + DECON_VIDW0xADD1B0(win));

	if (!(ctx->out_type & IFTYPE_HDMI))
		val = BIT_VAL(pitch - state->crtc.w * cpp, 27, 14)
			| BIT_VAL(state->crtc.w * cpp, 13, 0);
	else
		val = BIT_VAL(pitch - state->crtc.w * cpp, 29, 15)
			| BIT_VAL(state->crtc.w * cpp, 14, 0);
	writel(val, ctx->addr + DECON_VIDW0xADD2(win));

	decon_win_set_pixfmt(ctx, win, fb);

	/* window enable */
	decon_set_bits(ctx, DECON_WINCONx(win), WINCONx_ENWIN_F, ~0);
}