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
#define  V4L2_PIX_FMT_GREY 141 
#define  V4L2_PIX_FMT_NV12 140 
#define  V4L2_PIX_FMT_NV16 139 
#define  V4L2_PIX_FMT_NV21 138 
#define  V4L2_PIX_FMT_NV61 137 
#define  V4L2_PIX_FMT_UYVY 136 
#define  V4L2_PIX_FMT_VUYA32 135 
#define  V4L2_PIX_FMT_VUYX32 134 
#define  V4L2_PIX_FMT_VYUY 133 
#define  V4L2_PIX_FMT_Y4 132 
#define  V4L2_PIX_FMT_YUV420 131 
#define  V4L2_PIX_FMT_YUV422P 130 
#define  V4L2_PIX_FMT_YUYV 129 
#define  V4L2_PIX_FMT_YVYU 128 

__attribute__((used)) static bool pxp_v4l2_pix_fmt_is_yuv(u32 v4l2_pix_fmt)
{
	switch (v4l2_pix_fmt) {
	case V4L2_PIX_FMT_VUYA32:
	case V4L2_PIX_FMT_VUYX32:
	case V4L2_PIX_FMT_UYVY:
	case V4L2_PIX_FMT_YUYV:
	case V4L2_PIX_FMT_VYUY:
	case V4L2_PIX_FMT_YVYU:
	case V4L2_PIX_FMT_NV16:
	case V4L2_PIX_FMT_NV12:
	case V4L2_PIX_FMT_NV61:
	case V4L2_PIX_FMT_NV21:
	case V4L2_PIX_FMT_YUV420:
	case V4L2_PIX_FMT_YUV422P:
	case V4L2_PIX_FMT_GREY:
	case V4L2_PIX_FMT_Y4:
		return true;
	default:
		return false;
	}
}