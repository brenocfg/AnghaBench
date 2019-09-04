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
 int BYTE_SWAP_NOSWAP ; 
 int BYTE_SWAP_SWAP2 ; 
#define  DRM_FORMAT_ABGR1555 149 
#define  DRM_FORMAT_ABGR4444 148 
#define  DRM_FORMAT_ABGR8888 147 
#define  DRM_FORMAT_ARGB1555 146 
#define  DRM_FORMAT_ARGB4444 145 
#define  DRM_FORMAT_ARGB8888 144 
#define  DRM_FORMAT_BGR565 143 
#define  DRM_FORMAT_BGRA5551 142 
#define  DRM_FORMAT_BGRA8888 141 
#define  DRM_FORMAT_BGRX5551 140 
#define  DRM_FORMAT_RGB565 139 
#define  DRM_FORMAT_RGBA5551 138 
#define  DRM_FORMAT_RGBA8888 137 
#define  DRM_FORMAT_RGBX5551 136 
#define  DRM_FORMAT_UYVY 135 
#define  DRM_FORMAT_XBGR1555 134 
#define  DRM_FORMAT_XBGR8888 133 
#define  DRM_FORMAT_XRGB1555 132 
#define  DRM_FORMAT_XRGB8888 131 
#define  DRM_FORMAT_YUV420 130 
#define  DRM_FORMAT_YUV422 129 
#define  DRM_FORMAT_YUYV 128 
 int EINVAL ; 
 int WIN_COLOR_DEPTH_A1B5G5R5 ; 
 int WIN_COLOR_DEPTH_A8B8G8R8 ; 
 int WIN_COLOR_DEPTH_A8R8G8B8 ; 
 int WIN_COLOR_DEPTH_AR5G5B5 ; 
 int WIN_COLOR_DEPTH_B4G4R4A4 ; 
 int WIN_COLOR_DEPTH_B5G5R5A1 ; 
 int WIN_COLOR_DEPTH_B5G5R5X1 ; 
 int WIN_COLOR_DEPTH_B5G6R5 ; 
 int WIN_COLOR_DEPTH_B8G8R8A8 ; 
 int WIN_COLOR_DEPTH_B8G8R8X8 ; 
 int WIN_COLOR_DEPTH_R4G4B4A4 ; 
 int WIN_COLOR_DEPTH_R5G5B5A ; 
 int WIN_COLOR_DEPTH_R5G5B5X1 ; 
 int WIN_COLOR_DEPTH_R5G6B5 ; 
 int WIN_COLOR_DEPTH_R8G8B8A8 ; 
 int WIN_COLOR_DEPTH_R8G8B8X8 ; 
 int WIN_COLOR_DEPTH_X1B5G5R5 ; 
 int WIN_COLOR_DEPTH_X1R5G5B5 ; 
 int WIN_COLOR_DEPTH_YCbCr420P ; 
 int WIN_COLOR_DEPTH_YCbCr422 ; 
 int WIN_COLOR_DEPTH_YCbCr422P ; 

int tegra_plane_format(u32 fourcc, u32 *format, u32 *swap)
{
	/* assume no swapping of fetched data */
	if (swap)
		*swap = BYTE_SWAP_NOSWAP;

	switch (fourcc) {
	case DRM_FORMAT_ARGB4444:
		*format = WIN_COLOR_DEPTH_B4G4R4A4;
		break;

	case DRM_FORMAT_ARGB1555:
		*format = WIN_COLOR_DEPTH_B5G5R5A1;
		break;

	case DRM_FORMAT_RGB565:
		*format = WIN_COLOR_DEPTH_B5G6R5;
		break;

	case DRM_FORMAT_RGBA5551:
		*format = WIN_COLOR_DEPTH_A1B5G5R5;
		break;

	case DRM_FORMAT_ARGB8888:
		*format = WIN_COLOR_DEPTH_B8G8R8A8;
		break;

	case DRM_FORMAT_ABGR8888:
		*format = WIN_COLOR_DEPTH_R8G8B8A8;
		break;

	case DRM_FORMAT_ABGR4444:
		*format = WIN_COLOR_DEPTH_R4G4B4A4;
		break;

	case DRM_FORMAT_ABGR1555:
		*format = WIN_COLOR_DEPTH_R5G5B5A;
		break;

	case DRM_FORMAT_BGRA5551:
		*format = WIN_COLOR_DEPTH_AR5G5B5;
		break;

	case DRM_FORMAT_XRGB1555:
		*format = WIN_COLOR_DEPTH_B5G5R5X1;
		break;

	case DRM_FORMAT_RGBX5551:
		*format = WIN_COLOR_DEPTH_X1B5G5R5;
		break;

	case DRM_FORMAT_XBGR1555:
		*format = WIN_COLOR_DEPTH_R5G5B5X1;
		break;

	case DRM_FORMAT_BGRX5551:
		*format = WIN_COLOR_DEPTH_X1R5G5B5;
		break;

	case DRM_FORMAT_BGR565:
		*format = WIN_COLOR_DEPTH_R5G6B5;
		break;

	case DRM_FORMAT_BGRA8888:
		*format = WIN_COLOR_DEPTH_A8R8G8B8;
		break;

	case DRM_FORMAT_RGBA8888:
		*format = WIN_COLOR_DEPTH_A8B8G8R8;
		break;

	case DRM_FORMAT_XRGB8888:
		*format = WIN_COLOR_DEPTH_B8G8R8X8;
		break;

	case DRM_FORMAT_XBGR8888:
		*format = WIN_COLOR_DEPTH_R8G8B8X8;
		break;

	case DRM_FORMAT_UYVY:
		*format = WIN_COLOR_DEPTH_YCbCr422;
		break;

	case DRM_FORMAT_YUYV:
		if (!swap)
			return -EINVAL;

		*format = WIN_COLOR_DEPTH_YCbCr422;
		*swap = BYTE_SWAP_SWAP2;
		break;

	case DRM_FORMAT_YUV420:
		*format = WIN_COLOR_DEPTH_YCbCr420P;
		break;

	case DRM_FORMAT_YUV422:
		*format = WIN_COLOR_DEPTH_YCbCr422P;
		break;

	default:
		return -EINVAL;
	}

	return 0;
}