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

/* Variables and functions */
#define  DRM_FORMAT_ARGB1555 148 
#define  DRM_FORMAT_ARGB4444 147 
#define  DRM_FORMAT_ARGB8888 146 
#define  DRM_FORMAT_NV12 145 
#define  DRM_FORMAT_NV16 144 
#define  DRM_FORMAT_NV21 143 
#define  DRM_FORMAT_NV24 142 
#define  DRM_FORMAT_NV42 141 
#define  DRM_FORMAT_NV61 140 
#define  DRM_FORMAT_RGB565 139 
#define  DRM_FORMAT_RGBA8888 138 
#define  DRM_FORMAT_RGBX8888 137 
#define  DRM_FORMAT_UYVY 136 
#define  DRM_FORMAT_XRGB1555 135 
#define  DRM_FORMAT_XRGB4444 134 
#define  DRM_FORMAT_XRGB8888 133 
#define  DRM_FORMAT_YUV420 132 
#define  DRM_FORMAT_YUV422 131 
#define  DRM_FORMAT_YUV444 130 
#define  DRM_FORMAT_YUYV 129 
#define  DRM_FORMAT_YVYU 128 
 int SCALER_ARGB1555 ; 
 int SCALER_ARGB4444 ; 
 int SCALER_ARGB8888 ; 
 int SCALER_RGBA8888 ; 
 int SCALER_RGB_565 ; 
 int SCALER_YUV420_2P_UV ; 
 int SCALER_YUV420_2P_VU ; 
 int SCALER_YUV420_3P ; 
 int SCALER_YUV422_1P_UYVY ; 
 int SCALER_YUV422_1P_YUYV ; 
 int SCALER_YUV422_1P_YVYU ; 
 int SCALER_YUV422_2P_UV ; 
 int SCALER_YUV422_2P_VU ; 
 int SCALER_YUV422_3P ; 
 int SCALER_YUV444_2P_UV ; 
 int SCALER_YUV444_2P_VU ; 
 int SCALER_YUV444_3P ; 

__attribute__((used)) static u32 scaler_get_format(u32 drm_fmt)
{
	switch (drm_fmt) {
	case DRM_FORMAT_NV12:
		return SCALER_YUV420_2P_UV;
	case DRM_FORMAT_NV21:
		return SCALER_YUV420_2P_VU;
	case DRM_FORMAT_YUV420:
		return SCALER_YUV420_3P;
	case DRM_FORMAT_YUYV:
		return SCALER_YUV422_1P_YUYV;
	case DRM_FORMAT_UYVY:
		return SCALER_YUV422_1P_UYVY;
	case DRM_FORMAT_YVYU:
		return SCALER_YUV422_1P_YVYU;
	case DRM_FORMAT_NV16:
		return SCALER_YUV422_2P_UV;
	case DRM_FORMAT_NV61:
		return SCALER_YUV422_2P_VU;
	case DRM_FORMAT_YUV422:
		return SCALER_YUV422_3P;
	case DRM_FORMAT_NV24:
		return SCALER_YUV444_2P_UV;
	case DRM_FORMAT_NV42:
		return SCALER_YUV444_2P_VU;
	case DRM_FORMAT_YUV444:
		return SCALER_YUV444_3P;
	case DRM_FORMAT_RGB565:
		return SCALER_RGB_565;
	case DRM_FORMAT_XRGB1555:
		return SCALER_ARGB1555;
	case DRM_FORMAT_ARGB1555:
		return SCALER_ARGB1555;
	case DRM_FORMAT_XRGB4444:
		return SCALER_ARGB4444;
	case DRM_FORMAT_ARGB4444:
		return SCALER_ARGB4444;
	case DRM_FORMAT_XRGB8888:
		return SCALER_ARGB8888;
	case DRM_FORMAT_ARGB8888:
		return SCALER_ARGB8888;
	case DRM_FORMAT_RGBX8888:
		return SCALER_RGBA8888;
	case DRM_FORMAT_RGBA8888:
		return SCALER_RGBA8888;
	default:
		break;
	}

	return 0;
}