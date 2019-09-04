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
typedef  int uint32_t ;
struct fimd_context {scalar_t__ regs; TYPE_1__* driver_data; } ;
struct TYPE_2__ {scalar_t__ has_limited_fmt; } ;

/* Variables and functions */
#define  DRM_FORMAT_ARGB8888 132 
#define  DRM_FORMAT_C8 131 
#define  DRM_FORMAT_RGB565 130 
#define  DRM_FORMAT_XRGB1555 129 
#define  DRM_FORMAT_XRGB8888 128 
 int MIN_FB_WIDTH_FOR_16WORD_BURST ; 
 unsigned long VIDISD14C_ALPHA0_B (int) ; 
 unsigned long VIDISD14C_ALPHA0_G (int) ; 
 unsigned long VIDISD14C_ALPHA0_R (int) ; 
 unsigned long VIDISD14C_ALPHA1_B (int) ; 
 unsigned long VIDISD14C_ALPHA1_G (int) ; 
 unsigned long VIDISD14C_ALPHA1_R (int) ; 
 scalar_t__ VIDOSD_C (unsigned int) ; 
 unsigned long VIDW_ALPHA_G (int) ; 
 unsigned long VIDW_ALPHA_R (int) ; 
 scalar_t__ VIDWnALPHA0 (unsigned int) ; 
 scalar_t__ VIDWnALPHA1 (unsigned int) ; 
 scalar_t__ WINCON (unsigned int) ; 
 unsigned long WINCON0_BPPMODE_16BPP_1555 ; 
 unsigned long WINCON0_BPPMODE_16BPP_565 ; 
 unsigned long WINCON0_BPPMODE_24BPP_888 ; 
 unsigned long WINCON0_BPPMODE_8BPP_PALETTE ; 
 unsigned long WINCON1_ALPHA_SEL ; 
 unsigned long WINCON1_BLD_PIX ; 
 unsigned long WINCON1_BPPMODE_25BPP_A1888 ; 
 unsigned long WINCONx_BURSTLEN_16WORD ; 
 unsigned long WINCONx_BURSTLEN_4WORD ; 
 unsigned long WINCONx_BURSTLEN_8WORD ; 
 unsigned long WINCONx_BURSTLEN_MASK ; 
 unsigned long WINCONx_BYTSWP ; 
 unsigned long WINCONx_ENWIN ; 
 unsigned long WINCONx_HAWSWP ; 
 unsigned long WINCONx_WSWP ; 
 int /*<<< orphan*/  writel (unsigned long,scalar_t__) ; 

__attribute__((used)) static void fimd_win_set_pixfmt(struct fimd_context *ctx, unsigned int win,
				uint32_t pixel_format, int width)
{
	unsigned long val;

	val = WINCONx_ENWIN;

	/*
	 * In case of s3c64xx, window 0 doesn't support alpha channel.
	 * So the request format is ARGB8888 then change it to XRGB8888.
	 */
	if (ctx->driver_data->has_limited_fmt && !win) {
		if (pixel_format == DRM_FORMAT_ARGB8888)
			pixel_format = DRM_FORMAT_XRGB8888;
	}

	switch (pixel_format) {
	case DRM_FORMAT_C8:
		val |= WINCON0_BPPMODE_8BPP_PALETTE;
		val |= WINCONx_BURSTLEN_8WORD;
		val |= WINCONx_BYTSWP;
		break;
	case DRM_FORMAT_XRGB1555:
		val |= WINCON0_BPPMODE_16BPP_1555;
		val |= WINCONx_HAWSWP;
		val |= WINCONx_BURSTLEN_16WORD;
		break;
	case DRM_FORMAT_RGB565:
		val |= WINCON0_BPPMODE_16BPP_565;
		val |= WINCONx_HAWSWP;
		val |= WINCONx_BURSTLEN_16WORD;
		break;
	case DRM_FORMAT_XRGB8888:
		val |= WINCON0_BPPMODE_24BPP_888;
		val |= WINCONx_WSWP;
		val |= WINCONx_BURSTLEN_16WORD;
		break;
	case DRM_FORMAT_ARGB8888:
	default:
		val |= WINCON1_BPPMODE_25BPP_A1888
			| WINCON1_BLD_PIX | WINCON1_ALPHA_SEL;
		val |= WINCONx_WSWP;
		val |= WINCONx_BURSTLEN_16WORD;
		break;
	}

	/*
	 * Setting dma-burst to 16Word causes permanent tearing for very small
	 * buffers, e.g. cursor buffer. Burst Mode switching which based on
	 * plane size is not recommended as plane size varies alot towards the
	 * end of the screen and rapid movement causes unstable DMA, but it is
	 * still better to change dma-burst than displaying garbage.
	 */

	if (width < MIN_FB_WIDTH_FOR_16WORD_BURST) {
		val &= ~WINCONx_BURSTLEN_MASK;
		val |= WINCONx_BURSTLEN_4WORD;
	}

	writel(val, ctx->regs + WINCON(win));

	/* hardware window 0 doesn't support alpha channel. */
	if (win != 0) {
		/* OSD alpha */
		val = VIDISD14C_ALPHA0_R(0xf) |
			VIDISD14C_ALPHA0_G(0xf) |
			VIDISD14C_ALPHA0_B(0xf) |
			VIDISD14C_ALPHA1_R(0xf) |
			VIDISD14C_ALPHA1_G(0xf) |
			VIDISD14C_ALPHA1_B(0xf);

		writel(val, ctx->regs + VIDOSD_C(win));

		val = VIDW_ALPHA_R(0xf) | VIDW_ALPHA_G(0xf) |
			VIDW_ALPHA_G(0xf);
		writel(val, ctx->regs + VIDWnALPHA0(win));
		writel(val, ctx->regs + VIDWnALPHA1(win));
	}
}