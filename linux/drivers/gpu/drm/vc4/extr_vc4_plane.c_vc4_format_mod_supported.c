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
typedef  int const uint64_t ;
typedef  int uint32_t ;
struct drm_plane {int dummy; } ;

/* Variables and functions */
#define  DRM_FORMAT_ABGR8888 148 
#define  DRM_FORMAT_ARGB1555 147 
#define  DRM_FORMAT_ARGB8888 146 
#define  DRM_FORMAT_BGR565 145 
#define  DRM_FORMAT_MOD_BROADCOM_SAND128 144 
#define  DRM_FORMAT_MOD_BROADCOM_SAND256 143 
#define  DRM_FORMAT_MOD_BROADCOM_SAND64 142 
#define  DRM_FORMAT_MOD_BROADCOM_VC4_T_TILED 141 
#define  DRM_FORMAT_MOD_LINEAR 140 
#define  DRM_FORMAT_NV12 139 
#define  DRM_FORMAT_NV16 138 
#define  DRM_FORMAT_NV21 137 
#define  DRM_FORMAT_NV61 136 
#define  DRM_FORMAT_RGB565 135 
#define  DRM_FORMAT_XBGR8888 134 
#define  DRM_FORMAT_XRGB1555 133 
#define  DRM_FORMAT_XRGB8888 132 
#define  DRM_FORMAT_YUV420 131 
#define  DRM_FORMAT_YUV422 130 
#define  DRM_FORMAT_YVU420 129 
#define  DRM_FORMAT_YVU422 128 
 int /*<<< orphan*/  fourcc_mod_broadcom_mod (int const) ; 

__attribute__((used)) static bool vc4_format_mod_supported(struct drm_plane *plane,
				     uint32_t format,
				     uint64_t modifier)
{
	/* Support T_TILING for RGB formats only. */
	switch (format) {
	case DRM_FORMAT_XRGB8888:
	case DRM_FORMAT_ARGB8888:
	case DRM_FORMAT_ABGR8888:
	case DRM_FORMAT_XBGR8888:
	case DRM_FORMAT_RGB565:
	case DRM_FORMAT_BGR565:
	case DRM_FORMAT_ARGB1555:
	case DRM_FORMAT_XRGB1555:
		switch (fourcc_mod_broadcom_mod(modifier)) {
		case DRM_FORMAT_MOD_LINEAR:
		case DRM_FORMAT_MOD_BROADCOM_VC4_T_TILED:
			return true;
		default:
			return false;
		}
	case DRM_FORMAT_NV12:
	case DRM_FORMAT_NV21:
		switch (fourcc_mod_broadcom_mod(modifier)) {
		case DRM_FORMAT_MOD_LINEAR:
		case DRM_FORMAT_MOD_BROADCOM_SAND64:
		case DRM_FORMAT_MOD_BROADCOM_SAND128:
		case DRM_FORMAT_MOD_BROADCOM_SAND256:
			return true;
		default:
			return false;
		}
	case DRM_FORMAT_YUV422:
	case DRM_FORMAT_YVU422:
	case DRM_FORMAT_YUV420:
	case DRM_FORMAT_YVU420:
	case DRM_FORMAT_NV16:
	case DRM_FORMAT_NV61:
	default:
		return (modifier == DRM_FORMAT_MOD_LINEAR);
	}
}