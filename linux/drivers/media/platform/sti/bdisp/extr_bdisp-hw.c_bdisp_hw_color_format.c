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
 int BDISP_ARGB8888 ; 
 int BDISP_NV12 ; 
 int BDISP_RGB565 ; 
 int BDISP_RGB888 ; 
 int BDISP_XRGB8888 ; 
 int BDISP_YUV_3B ; 
 int BLT_TTY_ALPHA_R ; 
 int BLT_TTY_BIG_END ; 
 int BLT_TTY_COL_SHIFT ; 
#define  V4L2_PIX_FMT_ABGR32 133 
#define  V4L2_PIX_FMT_NV12 132 
#define  V4L2_PIX_FMT_RGB24 131 
#define  V4L2_PIX_FMT_RGB565 130 
#define  V4L2_PIX_FMT_XBGR32 129 
#define  V4L2_PIX_FMT_YUV420 128 

__attribute__((used)) static u32 bdisp_hw_color_format(u32 pixelformat)
{
	u32 ret;

	switch (pixelformat) {
	case V4L2_PIX_FMT_YUV420:
		ret = (BDISP_YUV_3B << BLT_TTY_COL_SHIFT);
		break;
	case V4L2_PIX_FMT_NV12:
		ret = (BDISP_NV12 << BLT_TTY_COL_SHIFT) | BLT_TTY_BIG_END;
		break;
	case V4L2_PIX_FMT_RGB565:
		ret = (BDISP_RGB565 << BLT_TTY_COL_SHIFT);
		break;
	case V4L2_PIX_FMT_XBGR32: /* This V4L format actually refers to xRGB */
		ret = (BDISP_XRGB8888 << BLT_TTY_COL_SHIFT);
		break;
	case V4L2_PIX_FMT_RGB24:  /* RGB888 format */
		ret = (BDISP_RGB888 << BLT_TTY_COL_SHIFT) | BLT_TTY_BIG_END;
		break;
	case V4L2_PIX_FMT_ABGR32: /* This V4L format actually refers to ARGB */

	default:
		ret = (BDISP_ARGB8888 << BLT_TTY_COL_SHIFT) | BLT_TTY_ALPHA_R;
		break;
	}

	return ret;
}