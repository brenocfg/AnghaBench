#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_4__ {int /*<<< orphan*/  regs; } ;
struct sun4i_backend {TYPE_2__ engine; } ;
struct drm_plane_state {struct drm_framebuffer* fb; } ;
struct drm_plane {struct drm_plane_state* state; } ;
struct drm_framebuffer {TYPE_1__* format; } ;
struct TYPE_3__ {int format; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*,int) ; 
#define  DRM_FORMAT_UYVY 131 
#define  DRM_FORMAT_VYUY 130 
#define  DRM_FORMAT_YUYV 129 
#define  DRM_FORMAT_YVYU 128 
 int /*<<< orphan*/  SUN4I_BACKEND_ATTCTL_REG0 (int) ; 
 int /*<<< orphan*/  SUN4I_BACKEND_ATTCTL_REG0_LAY_YUVEN ; 
 int /*<<< orphan*/  SUN4I_BACKEND_IYUVCTL_EN ; 
 int /*<<< orphan*/  SUN4I_BACKEND_IYUVCTL_FBFMT_PACKED_YUV422 ; 
 int /*<<< orphan*/  SUN4I_BACKEND_IYUVCTL_FBPS_UYVY ; 
 int /*<<< orphan*/  SUN4I_BACKEND_IYUVCTL_FBPS_VYUY ; 
 int /*<<< orphan*/  SUN4I_BACKEND_IYUVCTL_FBPS_YUYV ; 
 int /*<<< orphan*/  SUN4I_BACKEND_IYUVCTL_FBPS_YVYU ; 
 int /*<<< orphan*/  SUN4I_BACKEND_IYUVCTL_REG ; 
 int /*<<< orphan*/  SUN4I_BACKEND_YGCOEF_REG (int) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ sun4i_backend_format_is_packed_yuv422 (int) ; 
 int /*<<< orphan*/ * sunxi_bt601_yuv2rgb_coef ; 

__attribute__((used)) static int sun4i_backend_update_yuv_format(struct sun4i_backend *backend,
					   int layer, struct drm_plane *plane)
{
	struct drm_plane_state *state = plane->state;
	struct drm_framebuffer *fb = state->fb;
	uint32_t format = fb->format->format;
	u32 val = SUN4I_BACKEND_IYUVCTL_EN;
	int i;

	for (i = 0; i < ARRAY_SIZE(sunxi_bt601_yuv2rgb_coef); i++)
		regmap_write(backend->engine.regs,
			     SUN4I_BACKEND_YGCOEF_REG(i),
			     sunxi_bt601_yuv2rgb_coef[i]);

	/*
	 * We should do that only for a single plane, but the
	 * framebuffer's atomic_check has our back on this.
	 */
	regmap_update_bits(backend->engine.regs, SUN4I_BACKEND_ATTCTL_REG0(layer),
			   SUN4I_BACKEND_ATTCTL_REG0_LAY_YUVEN,
			   SUN4I_BACKEND_ATTCTL_REG0_LAY_YUVEN);

	/* TODO: Add support for the multi-planar YUV formats */
	if (sun4i_backend_format_is_packed_yuv422(format))
		val |= SUN4I_BACKEND_IYUVCTL_FBFMT_PACKED_YUV422;
	else
		DRM_DEBUG_DRIVER("Unsupported YUV format (0x%x)\n", format);

	/*
	 * Allwinner seems to list the pixel sequence from right to left, while
	 * DRM lists it from left to right.
	 */
	switch (format) {
	case DRM_FORMAT_YUYV:
		val |= SUN4I_BACKEND_IYUVCTL_FBPS_VYUY;
		break;
	case DRM_FORMAT_YVYU:
		val |= SUN4I_BACKEND_IYUVCTL_FBPS_UYVY;
		break;
	case DRM_FORMAT_UYVY:
		val |= SUN4I_BACKEND_IYUVCTL_FBPS_YVYU;
		break;
	case DRM_FORMAT_VYUY:
		val |= SUN4I_BACKEND_IYUVCTL_FBPS_YUYV;
		break;
	default:
		DRM_DEBUG_DRIVER("Unsupported YUV pixel sequence (0x%x)\n",
				 format);
	}

	regmap_write(backend->engine.regs, SUN4I_BACKEND_IYUVCTL_REG, val);

	return 0;
}