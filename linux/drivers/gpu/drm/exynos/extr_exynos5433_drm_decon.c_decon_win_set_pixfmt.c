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
struct TYPE_5__ {unsigned int alpha; unsigned int pixel_blend_mode; } ;
struct exynos_drm_plane_state {TYPE_2__ base; } ;
struct TYPE_4__ {int /*<<< orphan*/  state; } ;
struct exynos_drm_plane {TYPE_1__ base; } ;
struct drm_framebuffer {scalar_t__ width; TYPE_3__* format; } ;
struct decon_context {int /*<<< orphan*/  dev; scalar_t__ addr; struct exynos_drm_plane* planes; } ;
struct TYPE_6__ {int format; int /*<<< orphan*/ * cpp; scalar_t__ has_alpha; } ;

/* Variables and functions */
 scalar_t__ DECON_WINCONx (unsigned int) ; 
 int /*<<< orphan*/  DRM_DEV_DEBUG_KMS (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
#define  DRM_FORMAT_ARGB8888 131 
#define  DRM_FORMAT_RGB565 130 
#define  DRM_FORMAT_XRGB1555 129 
#define  DRM_FORMAT_XRGB8888 128 
 unsigned int DRM_MODE_BLEND_PIXEL_NONE ; 
 scalar_t__ MIN_FB_WIDTH_FOR_16WORD_BURST ; 
 int /*<<< orphan*/  WINCONx_BLEND_MODE_MASK ; 
 unsigned long WINCONx_BPPMODE_16BPP_565 ; 
 unsigned long WINCONx_BPPMODE_16BPP_I1555 ; 
 unsigned long WINCONx_BPPMODE_24BPP_888 ; 
 unsigned long WINCONx_BPPMODE_32BPP_A8888 ; 
 unsigned long WINCONx_BURSTLEN_16WORD ; 
 unsigned long WINCONx_BURSTLEN_8WORD ; 
 unsigned long WINCONx_BURSTLEN_MASK ; 
 unsigned long WINCONx_ENWIN_F ; 
 unsigned long WINCONx_HAWSWP_F ; 
 unsigned long WINCONx_WSWP_F ; 
 int /*<<< orphan*/  decon_set_bits (struct decon_context*,scalar_t__,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  decon_win_set_bldeq (struct decon_context*,unsigned int,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  decon_win_set_bldmod (struct decon_context*,unsigned int,unsigned int,unsigned int) ; 
 unsigned long readl (scalar_t__) ; 
 struct exynos_drm_plane_state* to_exynos_plane_state (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void decon_win_set_pixfmt(struct decon_context *ctx, unsigned int win,
				 struct drm_framebuffer *fb)
{
	struct exynos_drm_plane plane = ctx->planes[win];
	struct exynos_drm_plane_state *state =
		to_exynos_plane_state(plane.base.state);
	unsigned int alpha = state->base.alpha;
	unsigned int pixel_alpha;
	unsigned long val;

	if (fb->format->has_alpha)
		pixel_alpha = state->base.pixel_blend_mode;
	else
		pixel_alpha = DRM_MODE_BLEND_PIXEL_NONE;

	val = readl(ctx->addr + DECON_WINCONx(win));
	val &= WINCONx_ENWIN_F;

	switch (fb->format->format) {
	case DRM_FORMAT_XRGB1555:
		val |= WINCONx_BPPMODE_16BPP_I1555;
		val |= WINCONx_HAWSWP_F;
		val |= WINCONx_BURSTLEN_16WORD;
		break;
	case DRM_FORMAT_RGB565:
		val |= WINCONx_BPPMODE_16BPP_565;
		val |= WINCONx_HAWSWP_F;
		val |= WINCONx_BURSTLEN_16WORD;
		break;
	case DRM_FORMAT_XRGB8888:
		val |= WINCONx_BPPMODE_24BPP_888;
		val |= WINCONx_WSWP_F;
		val |= WINCONx_BURSTLEN_16WORD;
		break;
	case DRM_FORMAT_ARGB8888:
	default:
		val |= WINCONx_BPPMODE_32BPP_A8888;
		val |= WINCONx_WSWP_F;
		val |= WINCONx_BURSTLEN_16WORD;
		break;
	}

	DRM_DEV_DEBUG_KMS(ctx->dev, "cpp = %u\n", fb->format->cpp[0]);

	/*
	 * In case of exynos, setting dma-burst to 16Word causes permanent
	 * tearing for very small buffers, e.g. cursor buffer. Burst Mode
	 * switching which is based on plane size is not recommended as
	 * plane size varies a lot towards the end of the screen and rapid
	 * movement causes unstable DMA which results into iommu crash/tear.
	 */

	if (fb->width < MIN_FB_WIDTH_FOR_16WORD_BURST) {
		val &= ~WINCONx_BURSTLEN_MASK;
		val |= WINCONx_BURSTLEN_8WORD;
	}
	decon_set_bits(ctx, DECON_WINCONx(win), ~WINCONx_BLEND_MODE_MASK, val);

	if (win > 0) {
		decon_win_set_bldmod(ctx, win, alpha, pixel_alpha);
		decon_win_set_bldeq(ctx, win, alpha, pixel_alpha);
	}
}