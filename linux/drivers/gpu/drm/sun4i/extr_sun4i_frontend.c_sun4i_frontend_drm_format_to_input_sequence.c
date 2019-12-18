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
typedef  scalar_t__ u32 ;
struct drm_format_info {int format; } ;

/* Variables and functions */
#define  DRM_FORMAT_BGRX8888 137 
#define  DRM_FORMAT_NV12 136 
#define  DRM_FORMAT_NV16 135 
#define  DRM_FORMAT_NV21 134 
#define  DRM_FORMAT_NV61 133 
#define  DRM_FORMAT_UYVY 132 
#define  DRM_FORMAT_VYUY 131 
#define  DRM_FORMAT_XRGB8888 130 
#define  DRM_FORMAT_YUYV 129 
#define  DRM_FORMAT_YVYU 128 
 int EINVAL ; 
 scalar_t__ SUN4I_FRONTEND_INPUT_FMT_DATA_PS_BGRX ; 
 scalar_t__ SUN4I_FRONTEND_INPUT_FMT_DATA_PS_UV ; 
 scalar_t__ SUN4I_FRONTEND_INPUT_FMT_DATA_PS_UYVY ; 
 scalar_t__ SUN4I_FRONTEND_INPUT_FMT_DATA_PS_VU ; 
 scalar_t__ SUN4I_FRONTEND_INPUT_FMT_DATA_PS_VYUY ; 
 scalar_t__ SUN4I_FRONTEND_INPUT_FMT_DATA_PS_XRGB ; 
 scalar_t__ SUN4I_FRONTEND_INPUT_FMT_DATA_PS_YUYV ; 
 scalar_t__ SUN4I_FRONTEND_INPUT_FMT_DATA_PS_YVYU ; 
 scalar_t__ drm_format_info_is_yuv_planar (struct drm_format_info const*) ; 

__attribute__((used)) static int
sun4i_frontend_drm_format_to_input_sequence(const struct drm_format_info *format,
					    u32 *val)
{
	/* Planar formats have an explicit input sequence. */
	if (drm_format_info_is_yuv_planar(format)) {
		*val = 0;
		return 0;
	}

	switch (format->format) {
	case DRM_FORMAT_BGRX8888:
		*val = SUN4I_FRONTEND_INPUT_FMT_DATA_PS_BGRX;
		return 0;

	case DRM_FORMAT_NV12:
		*val = SUN4I_FRONTEND_INPUT_FMT_DATA_PS_UV;
		return 0;

	case DRM_FORMAT_NV16:
		*val = SUN4I_FRONTEND_INPUT_FMT_DATA_PS_UV;
		return 0;

	case DRM_FORMAT_NV21:
		*val = SUN4I_FRONTEND_INPUT_FMT_DATA_PS_VU;
		return 0;

	case DRM_FORMAT_NV61:
		*val = SUN4I_FRONTEND_INPUT_FMT_DATA_PS_VU;
		return 0;

	case DRM_FORMAT_UYVY:
		*val = SUN4I_FRONTEND_INPUT_FMT_DATA_PS_UYVY;
		return 0;

	case DRM_FORMAT_VYUY:
		*val = SUN4I_FRONTEND_INPUT_FMT_DATA_PS_VYUY;
		return 0;

	case DRM_FORMAT_XRGB8888:
		*val = SUN4I_FRONTEND_INPUT_FMT_DATA_PS_XRGB;
		return 0;

	case DRM_FORMAT_YUYV:
		*val = SUN4I_FRONTEND_INPUT_FMT_DATA_PS_YUYV;
		return 0;

	case DRM_FORMAT_YVYU:
		*val = SUN4I_FRONTEND_INPUT_FMT_DATA_PS_YVYU;
		return 0;

	default:
		return -EINVAL;
	}
}