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
typedef  int u64 ;
typedef  int u32 ;

/* Variables and functions */
 int AFBC_FORMAT_MOD_SPARSE ; 
#define  DRM_FORMAT_ABGR1555 149 
#define  DRM_FORMAT_ABGR2101010 148 
#define  DRM_FORMAT_ABGR8888 147 
#define  DRM_FORMAT_ARGB2101010 146 
#define  DRM_FORMAT_ARGB8888 145 
#define  DRM_FORMAT_BGR565 144 
#define  DRM_FORMAT_BGR888 143 
#define  DRM_FORMAT_BGRA1010102 142 
#define  DRM_FORMAT_BGRA8888 141 
#define  DRM_FORMAT_BGRX8888 140 
 int DRM_FORMAT_MOD_ARM_AFBC (int /*<<< orphan*/ ) ; 
#define  DRM_FORMAT_NV12 139 
#define  DRM_FORMAT_RGB565 138 
#define  DRM_FORMAT_RGB888 137 
#define  DRM_FORMAT_RGBA1010102 136 
#define  DRM_FORMAT_RGBA5551 135 
#define  DRM_FORMAT_RGBA8888 134 
#define  DRM_FORMAT_RGBX8888 133 
#define  DRM_FORMAT_UYVY 132 
#define  DRM_FORMAT_XBGR8888 131 
#define  DRM_FORMAT_XRGB8888 130 
#define  DRM_FORMAT_YUV420 129 
#define  DRM_FORMAT_YUYV 128 
 unsigned int DRM_MODE_REFLECT_X ; 
 unsigned int DRM_MODE_ROTATE_180 ; 
 unsigned int DRM_MODE_ROTATE_270 ; 
 unsigned int DRM_MODE_ROTATE_90 ; 

__attribute__((used)) static bool malidp_partial_prefetch_supported(u32 format, u64 modifier,
					      unsigned int rotation)
{
	bool afbc, sparse;

	/* rotation and horizontal flip not supported for partial prefetch */
	if (rotation & (DRM_MODE_ROTATE_90 | DRM_MODE_ROTATE_180 |
			DRM_MODE_ROTATE_270 | DRM_MODE_REFLECT_X))
		return false;

	afbc = modifier & DRM_FORMAT_MOD_ARM_AFBC(0);
	sparse = modifier & AFBC_FORMAT_MOD_SPARSE;

	switch (format) {
	case DRM_FORMAT_ARGB2101010:
	case DRM_FORMAT_RGBA1010102:
	case DRM_FORMAT_BGRA1010102:
	case DRM_FORMAT_ARGB8888:
	case DRM_FORMAT_RGBA8888:
	case DRM_FORMAT_BGRA8888:
	case DRM_FORMAT_XRGB8888:
	case DRM_FORMAT_XBGR8888:
	case DRM_FORMAT_RGBX8888:
	case DRM_FORMAT_BGRX8888:
	case DRM_FORMAT_RGB888:
	case DRM_FORMAT_RGBA5551:
	case DRM_FORMAT_RGB565:
		/* always supported */
		return true;

	case DRM_FORMAT_ABGR2101010:
	case DRM_FORMAT_ABGR8888:
	case DRM_FORMAT_ABGR1555:
	case DRM_FORMAT_BGR565:
		/* supported, but if AFBC then must be sparse mode */
		return (!afbc) || (afbc && sparse);

	case DRM_FORMAT_BGR888:
		/* supported, but not for AFBC */
		return !afbc;

	case DRM_FORMAT_YUYV:
	case DRM_FORMAT_UYVY:
	case DRM_FORMAT_NV12:
	case DRM_FORMAT_YUV420:
		/* not supported */
		return false;

	default:
		return false;
	}
}