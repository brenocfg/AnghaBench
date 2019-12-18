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
 int BM_PXP_PS_CTRL_WB_SWAP ; 
 int BV_PXP_PS_CTRL_FORMAT__RGB444 ; 
 int BV_PXP_PS_CTRL_FORMAT__RGB555 ; 
 int BV_PXP_PS_CTRL_FORMAT__RGB565 ; 
 int BV_PXP_PS_CTRL_FORMAT__RGB888 ; 
 int BV_PXP_PS_CTRL_FORMAT__UYVY1P422 ; 
 int BV_PXP_PS_CTRL_FORMAT__VYUY1P422 ; 
 int BV_PXP_PS_CTRL_FORMAT__Y4 ; 
 int BV_PXP_PS_CTRL_FORMAT__Y8 ; 
 int BV_PXP_PS_CTRL_FORMAT__YUV1P444 ; 
 int BV_PXP_PS_CTRL_FORMAT__YUV2P420 ; 
 int BV_PXP_PS_CTRL_FORMAT__YUV2P422 ; 
 int BV_PXP_PS_CTRL_FORMAT__YUV420 ; 
 int BV_PXP_PS_CTRL_FORMAT__YUV422 ; 
 int BV_PXP_PS_CTRL_FORMAT__YVU2P420 ; 
 int BV_PXP_PS_CTRL_FORMAT__YVU2P422 ; 
#define  V4L2_PIX_FMT_GREY 144 
#define  V4L2_PIX_FMT_NV12 143 
#define  V4L2_PIX_FMT_NV16 142 
#define  V4L2_PIX_FMT_NV21 141 
#define  V4L2_PIX_FMT_NV61 140 
#define  V4L2_PIX_FMT_RGB444 139 
#define  V4L2_PIX_FMT_RGB555 138 
#define  V4L2_PIX_FMT_RGB565 137 
#define  V4L2_PIX_FMT_UYVY 136 
#define  V4L2_PIX_FMT_VUYX32 135 
#define  V4L2_PIX_FMT_VYUY 134 
#define  V4L2_PIX_FMT_XBGR32 133 
#define  V4L2_PIX_FMT_Y4 132 
#define  V4L2_PIX_FMT_YUV420 131 
#define  V4L2_PIX_FMT_YUV422P 130 
#define  V4L2_PIX_FMT_YUYV 129 
#define  V4L2_PIX_FMT_YVYU 128 

__attribute__((used)) static u32 pxp_v4l2_pix_fmt_to_ps_format(u32 v4l2_pix_fmt)
{
	switch (v4l2_pix_fmt) {
	case V4L2_PIX_FMT_XBGR32:  return BV_PXP_PS_CTRL_FORMAT__RGB888;
	case V4L2_PIX_FMT_RGB555:  return BV_PXP_PS_CTRL_FORMAT__RGB555;
	case V4L2_PIX_FMT_RGB444:  return BV_PXP_PS_CTRL_FORMAT__RGB444;
	case V4L2_PIX_FMT_RGB565:  return BV_PXP_PS_CTRL_FORMAT__RGB565;
	case V4L2_PIX_FMT_VUYX32:  return BV_PXP_PS_CTRL_FORMAT__YUV1P444;
	case V4L2_PIX_FMT_UYVY:    return BV_PXP_PS_CTRL_FORMAT__UYVY1P422;
	case V4L2_PIX_FMT_YUYV:    return BM_PXP_PS_CTRL_WB_SWAP |
					  BV_PXP_PS_CTRL_FORMAT__UYVY1P422;
	case V4L2_PIX_FMT_VYUY:    return BV_PXP_PS_CTRL_FORMAT__VYUY1P422;
	case V4L2_PIX_FMT_YVYU:    return BM_PXP_PS_CTRL_WB_SWAP |
					  BV_PXP_PS_CTRL_FORMAT__VYUY1P422;
	case V4L2_PIX_FMT_GREY:    return BV_PXP_PS_CTRL_FORMAT__Y8;
	default:
	case V4L2_PIX_FMT_Y4:      return BV_PXP_PS_CTRL_FORMAT__Y4;
	case V4L2_PIX_FMT_NV16:    return BV_PXP_PS_CTRL_FORMAT__YUV2P422;
	case V4L2_PIX_FMT_NV12:    return BV_PXP_PS_CTRL_FORMAT__YUV2P420;
	case V4L2_PIX_FMT_NV21:    return BV_PXP_PS_CTRL_FORMAT__YVU2P420;
	case V4L2_PIX_FMT_NV61:    return BV_PXP_PS_CTRL_FORMAT__YVU2P422;
	case V4L2_PIX_FMT_YUV422P: return BV_PXP_PS_CTRL_FORMAT__YUV422;
	case V4L2_PIX_FMT_YUV420:  return BV_PXP_PS_CTRL_FORMAT__YUV420;
	}
}