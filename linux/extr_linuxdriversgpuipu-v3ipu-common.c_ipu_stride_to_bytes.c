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
 int EINVAL ; 
#define  V4L2_PIX_FMT_BGR24 143 
#define  V4L2_PIX_FMT_BGR32 142 
#define  V4L2_PIX_FMT_NV12 141 
#define  V4L2_PIX_FMT_NV16 140 
#define  V4L2_PIX_FMT_NV21 139 
#define  V4L2_PIX_FMT_NV61 138 
#define  V4L2_PIX_FMT_RGB24 137 
#define  V4L2_PIX_FMT_RGB32 136 
#define  V4L2_PIX_FMT_RGB565 135 
#define  V4L2_PIX_FMT_UYVY 134 
#define  V4L2_PIX_FMT_XBGR32 133 
#define  V4L2_PIX_FMT_XRGB32 132 
#define  V4L2_PIX_FMT_YUV420 131 
#define  V4L2_PIX_FMT_YUV422P 130 
#define  V4L2_PIX_FMT_YUYV 129 
#define  V4L2_PIX_FMT_YVU420 128 

int ipu_stride_to_bytes(u32 pixel_stride, u32 pixelformat)
{
	switch (pixelformat) {
	case V4L2_PIX_FMT_YUV420:
	case V4L2_PIX_FMT_YVU420:
	case V4L2_PIX_FMT_YUV422P:
	case V4L2_PIX_FMT_NV12:
	case V4L2_PIX_FMT_NV21:
	case V4L2_PIX_FMT_NV16:
	case V4L2_PIX_FMT_NV61:
		/*
		 * for the planar YUV formats, the stride passed to
		 * cpmem must be the stride in bytes of the Y plane.
		 * And all the planar YUV formats have an 8-bit
		 * Y component.
		 */
		return (8 * pixel_stride) >> 3;
	case V4L2_PIX_FMT_RGB565:
	case V4L2_PIX_FMT_YUYV:
	case V4L2_PIX_FMT_UYVY:
		return (16 * pixel_stride) >> 3;
	case V4L2_PIX_FMT_BGR24:
	case V4L2_PIX_FMT_RGB24:
		return (24 * pixel_stride) >> 3;
	case V4L2_PIX_FMT_BGR32:
	case V4L2_PIX_FMT_RGB32:
	case V4L2_PIX_FMT_XBGR32:
	case V4L2_PIX_FMT_XRGB32:
		return (32 * pixel_stride) >> 3;
	default:
		break;
	}

	return -EINVAL;
}