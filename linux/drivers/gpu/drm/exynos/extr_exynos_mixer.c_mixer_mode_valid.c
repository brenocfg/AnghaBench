#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u32 ;
struct mixer_context {scalar_t__ mxr_ver; int /*<<< orphan*/  dev; } ;
struct exynos_drm_crtc {struct mixer_context* ctx; } ;
struct drm_display_mode {int hdisplay; int vdisplay; int flags; int /*<<< orphan*/  vrefresh; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEV_DEBUG_KMS (int /*<<< orphan*/ ,char*,int,int,int /*<<< orphan*/ ,int) ; 
 int DRM_MODE_FLAG_INTERLACE ; 
 int MODE_BAD ; 
 int MODE_OK ; 
 scalar_t__ MXR_VER_128_0_0_184 ; 

__attribute__((used)) static int mixer_mode_valid(struct exynos_drm_crtc *crtc,
		const struct drm_display_mode *mode)
{
	struct mixer_context *ctx = crtc->ctx;
	u32 w = mode->hdisplay, h = mode->vdisplay;

	DRM_DEV_DEBUG_KMS(ctx->dev, "xres=%d, yres=%d, refresh=%d, intl=%d\n",
			  w, h, mode->vrefresh,
			  !!(mode->flags & DRM_MODE_FLAG_INTERLACE));

	if (ctx->mxr_ver == MXR_VER_128_0_0_184)
		return MODE_OK;

	if ((w >= 464 && w <= 720 && h >= 261 && h <= 576) ||
	    (w >= 1024 && w <= 1280 && h >= 576 && h <= 720) ||
	    (w >= 1664 && w <= 1920 && h >= 936 && h <= 1080))
		return MODE_OK;

	if ((w == 1024 && h == 768) ||
	    (w == 1366 && h == 768) ||
	    (w == 1280 && h == 1024))
		return MODE_OK;

	return MODE_BAD;
}