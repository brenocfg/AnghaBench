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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int /*<<< orphan*/  regs; } ;
struct sun4i_backend {TYPE_1__ engine; } ;
struct drm_plane_state {struct drm_framebuffer* fb; } ;
struct drm_plane {struct drm_plane_state* state; } ;
struct drm_framebuffer {struct drm_format_info* format; } ;
struct drm_format_info {int /*<<< orphan*/  format; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*,int const) ; 
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
 scalar_t__ drm_format_info_is_yuv_packed (struct drm_format_info const*) ; 
 scalar_t__ drm_format_info_is_yuv_sampling_422 (struct drm_format_info const*) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * sunxi_bt601_yuv2rgb_coef ; 

__attribute__((used)) static int sun4i_backend_update_yuv_format(struct sun4i_backend *backend,
					   int layer, struct drm_plane *plane)
{
	struct drm_plane_state *state = plane->state;
	struct drm_framebuffer *fb = state->fb;
	const struct drm_format_info *format = fb->format;
	const uint32_t fmt = format->format;
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
	if (drm_format_info_is_yuv_packed(format) &&
	    drm_format_info_is_yuv_sampling_422(format))
		val |= SUN4I_BACKEND_IYUVCTL_FBFMT_PACKED_YUV422;
	else
		DRM_DEBUG_DRIVER("Unsupported YUV format (0x%x)\n", fmt);

	/*
	 * Allwinner seems to list the pixel sequence from right to left, while
	 * DRM lists it from left to right.
	 */
	switch (fmt) {
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
				 fmt);
	}

	regmap_write(backend->engine.regs, SUN4I_BACKEND_IYUVCTL_REG, val);

	return 0;
}