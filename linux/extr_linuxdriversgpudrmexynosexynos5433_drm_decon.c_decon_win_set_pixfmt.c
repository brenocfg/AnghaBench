#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct drm_framebuffer {scalar_t__ width; TYPE_1__* format; } ;
struct decon_context {scalar_t__ addr; } ;
struct TYPE_2__ {int format; int /*<<< orphan*/ * cpp; } ;

/* Variables and functions */
 scalar_t__ DECON_WINCONx (unsigned int) ; 
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,int /*<<< orphan*/ ) ; 
#define  DRM_FORMAT_ARGB8888 131 
#define  DRM_FORMAT_RGB565 130 
#define  DRM_FORMAT_XRGB1555 129 
#define  DRM_FORMAT_XRGB8888 128 
 scalar_t__ MIN_FB_WIDTH_FOR_16WORD_BURST ; 
 unsigned long WINCONx_ALPHA_SEL_F ; 
 unsigned long WINCONx_BLD_PIX_F ; 
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
 unsigned long readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (unsigned long,scalar_t__) ; 

__attribute__((used)) static void decon_win_set_pixfmt(struct decon_context *ctx, unsigned int win,
				 struct drm_framebuffer *fb)
{
	unsigned long val;

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
		val |= WINCONx_WSWP_F | WINCONx_BLD_PIX_F | WINCONx_ALPHA_SEL_F;
		val |= WINCONx_BURSTLEN_16WORD;
		break;
	}

	DRM_DEBUG_KMS("cpp = %u\n", fb->format->cpp[0]);

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

	writel(val, ctx->addr + DECON_WINCONx(win));
}