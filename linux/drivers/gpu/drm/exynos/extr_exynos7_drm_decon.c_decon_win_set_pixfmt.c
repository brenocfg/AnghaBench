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
struct drm_framebuffer {int* pitches; int width; TYPE_1__* format; } ;
struct decon_context {scalar_t__ regs; int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int format; int* cpp; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEV_DEBUG_KMS (int /*<<< orphan*/ ,char*,int) ; 
#define  DRM_FORMAT_ABGR8888 136 
#define  DRM_FORMAT_ARGB8888 135 
#define  DRM_FORMAT_BGRA8888 134 
#define  DRM_FORMAT_BGRX8888 133 
#define  DRM_FORMAT_RGB565 132 
#define  DRM_FORMAT_RGBA8888 131 
#define  DRM_FORMAT_RGBX8888 130 
#define  DRM_FORMAT_XBGR8888 129 
#define  DRM_FORMAT_XRGB8888 128 
 int MIN_FB_WIDTH_FOR_16WORD_BURST ; 
 scalar_t__ WINCON (unsigned int) ; 
 unsigned long WINCONx_ALPHA_SEL ; 
 unsigned long WINCONx_BLD_PIX ; 
 unsigned long WINCONx_BPPMODE_16BPP_565 ; 
 unsigned long WINCONx_BPPMODE_24BPP_BGRx ; 
 unsigned long WINCONx_BPPMODE_24BPP_RGBx ; 
 unsigned long WINCONx_BPPMODE_24BPP_xBGR ; 
 unsigned long WINCONx_BPPMODE_24BPP_xRGB ; 
 unsigned long WINCONx_BPPMODE_32BPP_ABGR ; 
 unsigned long WINCONx_BPPMODE_32BPP_ARGB ; 
 unsigned long WINCONx_BPPMODE_32BPP_BGRA ; 
 unsigned long WINCONx_BPPMODE_32BPP_RGBA ; 
 unsigned long WINCONx_BPPMODE_MASK ; 
 unsigned long WINCONx_BURSTLEN_16WORD ; 
 unsigned long WINCONx_BURSTLEN_8WORD ; 
 unsigned long WINCONx_BURSTLEN_MASK ; 
 unsigned long readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (unsigned long,scalar_t__) ; 

__attribute__((used)) static void decon_win_set_pixfmt(struct decon_context *ctx, unsigned int win,
				 struct drm_framebuffer *fb)
{
	unsigned long val;
	int padding;

	val = readl(ctx->regs + WINCON(win));
	val &= ~WINCONx_BPPMODE_MASK;

	switch (fb->format->format) {
	case DRM_FORMAT_RGB565:
		val |= WINCONx_BPPMODE_16BPP_565;
		val |= WINCONx_BURSTLEN_16WORD;
		break;
	case DRM_FORMAT_XRGB8888:
		val |= WINCONx_BPPMODE_24BPP_xRGB;
		val |= WINCONx_BURSTLEN_16WORD;
		break;
	case DRM_FORMAT_XBGR8888:
		val |= WINCONx_BPPMODE_24BPP_xBGR;
		val |= WINCONx_BURSTLEN_16WORD;
		break;
	case DRM_FORMAT_RGBX8888:
		val |= WINCONx_BPPMODE_24BPP_RGBx;
		val |= WINCONx_BURSTLEN_16WORD;
		break;
	case DRM_FORMAT_BGRX8888:
		val |= WINCONx_BPPMODE_24BPP_BGRx;
		val |= WINCONx_BURSTLEN_16WORD;
		break;
	case DRM_FORMAT_ARGB8888:
		val |= WINCONx_BPPMODE_32BPP_ARGB | WINCONx_BLD_PIX |
			WINCONx_ALPHA_SEL;
		val |= WINCONx_BURSTLEN_16WORD;
		break;
	case DRM_FORMAT_ABGR8888:
		val |= WINCONx_BPPMODE_32BPP_ABGR | WINCONx_BLD_PIX |
			WINCONx_ALPHA_SEL;
		val |= WINCONx_BURSTLEN_16WORD;
		break;
	case DRM_FORMAT_RGBA8888:
		val |= WINCONx_BPPMODE_32BPP_RGBA | WINCONx_BLD_PIX |
			WINCONx_ALPHA_SEL;
		val |= WINCONx_BURSTLEN_16WORD;
		break;
	case DRM_FORMAT_BGRA8888:
	default:
		val |= WINCONx_BPPMODE_32BPP_BGRA | WINCONx_BLD_PIX |
			WINCONx_ALPHA_SEL;
		val |= WINCONx_BURSTLEN_16WORD;
		break;
	}

	DRM_DEV_DEBUG_KMS(ctx->dev, "cpp = %d\n", fb->format->cpp[0]);

	/*
	 * In case of exynos, setting dma-burst to 16Word causes permanent
	 * tearing for very small buffers, e.g. cursor buffer. Burst Mode
	 * switching which is based on plane size is not recommended as
	 * plane size varies a lot towards the end of the screen and rapid
	 * movement causes unstable DMA which results into iommu crash/tear.
	 */

	padding = (fb->pitches[0] / fb->format->cpp[0]) - fb->width;
	if (fb->width + padding < MIN_FB_WIDTH_FOR_16WORD_BURST) {
		val &= ~WINCONx_BURSTLEN_MASK;
		val |= WINCONx_BURSTLEN_8WORD;
	}

	writel(val, ctx->regs + WINCON(win));
}