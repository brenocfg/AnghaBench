#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  u32 ;
struct fimd_context {TYPE_4__* driver_data; struct exynos_drm_plane* planes; } ;
struct TYPE_7__ {unsigned int alpha; unsigned int pixel_blend_mode; } ;
struct exynos_drm_plane_state {TYPE_3__ base; } ;
struct TYPE_5__ {int /*<<< orphan*/  state; } ;
struct exynos_drm_plane {TYPE_1__ base; } ;
struct drm_framebuffer {TYPE_2__* format; } ;
struct TYPE_8__ {scalar_t__ has_limited_fmt; } ;
struct TYPE_6__ {int format; scalar_t__ has_alpha; } ;

/* Variables and functions */
#define  DRM_FORMAT_ARGB8888 132 
#define  DRM_FORMAT_C8 131 
#define  DRM_FORMAT_RGB565 130 
#define  DRM_FORMAT_XRGB1555 129 
#define  DRM_FORMAT_XRGB8888 128 
 unsigned int DRM_MODE_BLEND_PIXEL_NONE ; 
 int MIN_FB_WIDTH_FOR_16WORD_BURST ; 
 int /*<<< orphan*/  WINCON (unsigned int) ; 
 int /*<<< orphan*/  WINCON0_BPPMODE_16BPP_1555 ; 
 int /*<<< orphan*/  WINCON0_BPPMODE_16BPP_565 ; 
 int /*<<< orphan*/  WINCON0_BPPMODE_24BPP_888 ; 
 int /*<<< orphan*/  WINCON0_BPPMODE_8BPP_PALETTE ; 
 int /*<<< orphan*/  WINCON1_BPPMODE_25BPP_A1888 ; 
 int /*<<< orphan*/  WINCONx_BLEND_MODE_MASK ; 
 int /*<<< orphan*/  WINCONx_BURSTLEN_16WORD ; 
 int /*<<< orphan*/  WINCONx_BURSTLEN_4WORD ; 
 int /*<<< orphan*/  WINCONx_BURSTLEN_8WORD ; 
 int /*<<< orphan*/  WINCONx_BURSTLEN_MASK ; 
 int /*<<< orphan*/  WINCONx_BYTSWP ; 
 int /*<<< orphan*/  WINCONx_ENWIN ; 
 int /*<<< orphan*/  WINCONx_HAWSWP ; 
 int /*<<< orphan*/  WINCONx_WSWP ; 
 int /*<<< orphan*/  fimd_set_bits (struct fimd_context*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fimd_win_set_bldeq (struct fimd_context*,unsigned int,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  fimd_win_set_bldmod (struct fimd_context*,unsigned int,unsigned int,unsigned int) ; 
 struct exynos_drm_plane_state* to_exynos_plane_state (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fimd_win_set_pixfmt(struct fimd_context *ctx, unsigned int win,
				struct drm_framebuffer *fb, int width)
{
	struct exynos_drm_plane plane = ctx->planes[win];
	struct exynos_drm_plane_state *state =
		to_exynos_plane_state(plane.base.state);
	uint32_t pixel_format = fb->format->format;
	unsigned int alpha = state->base.alpha;
	u32 val = WINCONx_ENWIN;
	unsigned int pixel_alpha;

	if (fb->format->has_alpha)
		pixel_alpha = state->base.pixel_blend_mode;
	else
		pixel_alpha = DRM_MODE_BLEND_PIXEL_NONE;

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
		val |= WINCON1_BPPMODE_25BPP_A1888;
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
	fimd_set_bits(ctx, WINCON(win), ~WINCONx_BLEND_MODE_MASK, val);

	/* hardware window 0 doesn't support alpha channel. */
	if (win != 0) {
		fimd_win_set_bldmod(ctx, win, alpha, pixel_alpha);
		fimd_win_set_bldeq(ctx, win, alpha, pixel_alpha);
	}
}