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
struct TYPE_10__ {unsigned int w; unsigned int h; unsigned int x; unsigned int y; } ;
struct TYPE_9__ {unsigned long x; unsigned long y; } ;
struct TYPE_7__ {struct drm_framebuffer* fb; } ;
struct exynos_drm_plane_state {TYPE_5__ crtc; TYPE_4__ src; TYPE_2__ base; } ;
struct TYPE_6__ {int /*<<< orphan*/  state; } ;
struct exynos_drm_plane {unsigned int index; TYPE_1__ base; } ;
struct exynos_drm_crtc {struct decon_context* ctx; } ;
struct drm_framebuffer {unsigned int* pitches; unsigned int width; unsigned long height; TYPE_3__* format; } ;
struct decon_context {scalar_t__ regs; int /*<<< orphan*/  dev; scalar_t__ suspended; } ;
struct TYPE_8__ {unsigned int* cpp; } ;

/* Variables and functions */
 scalar_t__ DECON_UPDATE ; 
 unsigned long DECON_UPDATE_STANDALONE_F ; 
 int /*<<< orphan*/  DRM_DEV_DEBUG_KMS (int /*<<< orphan*/ ,char*,unsigned int,...) ; 
 scalar_t__ VIDOSD_A (unsigned int) ; 
 scalar_t__ VIDOSD_B (unsigned int) ; 
 scalar_t__ VIDOSD_C (unsigned int) ; 
 scalar_t__ VIDOSD_D (unsigned int) ; 
 unsigned long VIDOSDxA_TOPLEFT_X (unsigned int) ; 
 unsigned long VIDOSDxA_TOPLEFT_Y (unsigned int) ; 
 unsigned long VIDOSDxB_BOTRIGHT_X (unsigned int) ; 
 unsigned long VIDOSDxB_BOTRIGHT_Y (unsigned int) ; 
 unsigned long VIDOSDxC_ALPHA0_B_F (int) ; 
 unsigned long VIDOSDxC_ALPHA0_G_F (int) ; 
 unsigned long VIDOSDxC_ALPHA0_R_F (int) ; 
 unsigned long VIDOSDxD_ALPHA1_B_F (int) ; 
 unsigned long VIDOSDxD_ALPHA1_G_F (int) ; 
 unsigned long VIDOSDxD_ALPHA1_R_F (int) ; 
 scalar_t__ VIDW_BUF_START (unsigned int) ; 
 scalar_t__ VIDW_OFFSET_X (unsigned int) ; 
 scalar_t__ VIDW_OFFSET_Y (unsigned int) ; 
 scalar_t__ VIDW_WHOLE_X (unsigned int) ; 
 scalar_t__ VIDW_WHOLE_Y (unsigned int) ; 
 scalar_t__ WINCON (unsigned int) ; 
 unsigned long WINCONx_ENWIN ; 
 unsigned long WINCONx_TRIPLE_BUF_MODE ; 
 int /*<<< orphan*/  decon_shadow_protect_win (struct decon_context*,unsigned int,int) ; 
 int /*<<< orphan*/  decon_win_set_colkey (struct decon_context*,unsigned int) ; 
 int /*<<< orphan*/  decon_win_set_pixfmt (struct decon_context*,unsigned int,struct drm_framebuffer*) ; 
 scalar_t__ exynos_drm_fb_dma_addr (struct drm_framebuffer*,int /*<<< orphan*/ ) ; 
 unsigned long readl (scalar_t__) ; 
 struct exynos_drm_plane_state* to_exynos_plane_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (unsigned long,scalar_t__) ; 

__attribute__((used)) static void decon_update_plane(struct exynos_drm_crtc *crtc,
			       struct exynos_drm_plane *plane)
{
	struct exynos_drm_plane_state *state =
				to_exynos_plane_state(plane->base.state);
	struct decon_context *ctx = crtc->ctx;
	struct drm_framebuffer *fb = state->base.fb;
	int padding;
	unsigned long val, alpha;
	unsigned int last_x;
	unsigned int last_y;
	unsigned int win = plane->index;
	unsigned int cpp = fb->format->cpp[0];
	unsigned int pitch = fb->pitches[0];

	if (ctx->suspended)
		return;

	/*
	 * SHADOWCON/PRTCON register is used for enabling timing.
	 *
	 * for example, once only width value of a register is set,
	 * if the dma is started then decon hardware could malfunction so
	 * with protect window setting, the register fields with prefix '_F'
	 * wouldn't be updated at vsync also but updated once unprotect window
	 * is set.
	 */

	/* buffer start address */
	val = (unsigned long)exynos_drm_fb_dma_addr(fb, 0);
	writel(val, ctx->regs + VIDW_BUF_START(win));

	padding = (pitch / cpp) - fb->width;

	/* buffer size */
	writel(fb->width + padding, ctx->regs + VIDW_WHOLE_X(win));
	writel(fb->height, ctx->regs + VIDW_WHOLE_Y(win));

	/* offset from the start of the buffer to read */
	writel(state->src.x, ctx->regs + VIDW_OFFSET_X(win));
	writel(state->src.y, ctx->regs + VIDW_OFFSET_Y(win));

	DRM_DEV_DEBUG_KMS(ctx->dev, "start addr = 0x%lx\n",
			(unsigned long)val);
	DRM_DEV_DEBUG_KMS(ctx->dev, "ovl_width = %d, ovl_height = %d\n",
			state->crtc.w, state->crtc.h);

	val = VIDOSDxA_TOPLEFT_X(state->crtc.x) |
		VIDOSDxA_TOPLEFT_Y(state->crtc.y);
	writel(val, ctx->regs + VIDOSD_A(win));

	last_x = state->crtc.x + state->crtc.w;
	if (last_x)
		last_x--;
	last_y = state->crtc.y + state->crtc.h;
	if (last_y)
		last_y--;

	val = VIDOSDxB_BOTRIGHT_X(last_x) | VIDOSDxB_BOTRIGHT_Y(last_y);

	writel(val, ctx->regs + VIDOSD_B(win));

	DRM_DEV_DEBUG_KMS(ctx->dev, "osd pos: tx = %d, ty = %d, bx = %d, by = %d\n",
			state->crtc.x, state->crtc.y, last_x, last_y);

	/* OSD alpha */
	alpha = VIDOSDxC_ALPHA0_R_F(0x0) |
			VIDOSDxC_ALPHA0_G_F(0x0) |
			VIDOSDxC_ALPHA0_B_F(0x0);

	writel(alpha, ctx->regs + VIDOSD_C(win));

	alpha = VIDOSDxD_ALPHA1_R_F(0xff) |
			VIDOSDxD_ALPHA1_G_F(0xff) |
			VIDOSDxD_ALPHA1_B_F(0xff);

	writel(alpha, ctx->regs + VIDOSD_D(win));

	decon_win_set_pixfmt(ctx, win, fb);

	/* hardware window 0 doesn't support color key. */
	if (win != 0)
		decon_win_set_colkey(ctx, win);

	/* wincon */
	val = readl(ctx->regs + WINCON(win));
	val |= WINCONx_TRIPLE_BUF_MODE;
	val |= WINCONx_ENWIN;
	writel(val, ctx->regs + WINCON(win));

	/* Enable DMA channel and unprotect windows */
	decon_shadow_protect_win(ctx, win, false);

	val = readl(ctx->regs + DECON_UPDATE);
	val |= DECON_UPDATE_STANDALONE_F;
	writel(val, ctx->regs + DECON_UPDATE);
}