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
 int ALIGN (int,int) ; 
 int SZ_4K ; 
#define  V4L2_PIX_FMT_H263 141 
#define  V4L2_PIX_FMT_H264 140 
#define  V4L2_PIX_FMT_H264_MVC 139 
#define  V4L2_PIX_FMT_H264_NO_SC 138 
#define  V4L2_PIX_FMT_HEVC 137 
#define  V4L2_PIX_FMT_MPEG 136 
#define  V4L2_PIX_FMT_MPEG1 135 
#define  V4L2_PIX_FMT_MPEG2 134 
#define  V4L2_PIX_FMT_MPEG4 133 
#define  V4L2_PIX_FMT_VC1_ANNEX_G 132 
#define  V4L2_PIX_FMT_VC1_ANNEX_L 131 
#define  V4L2_PIX_FMT_VP8 130 
#define  V4L2_PIX_FMT_VP9 129 
#define  V4L2_PIX_FMT_XVID 128 
 int to_hfi_raw_fmt (int) ; 
 int venus_helper_get_framesz_raw (int,int,int) ; 

u32 venus_helper_get_framesz(u32 v4l2_fmt, u32 width, u32 height)
{
	u32 hfi_fmt, sz;
	bool compressed;

	switch (v4l2_fmt) {
	case V4L2_PIX_FMT_MPEG:
	case V4L2_PIX_FMT_H264:
	case V4L2_PIX_FMT_H264_NO_SC:
	case V4L2_PIX_FMT_H264_MVC:
	case V4L2_PIX_FMT_H263:
	case V4L2_PIX_FMT_MPEG1:
	case V4L2_PIX_FMT_MPEG2:
	case V4L2_PIX_FMT_MPEG4:
	case V4L2_PIX_FMT_XVID:
	case V4L2_PIX_FMT_VC1_ANNEX_G:
	case V4L2_PIX_FMT_VC1_ANNEX_L:
	case V4L2_PIX_FMT_VP8:
	case V4L2_PIX_FMT_VP9:
	case V4L2_PIX_FMT_HEVC:
		compressed = true;
		break;
	default:
		compressed = false;
		break;
	}

	if (compressed) {
		sz = ALIGN(height, 32) * ALIGN(width, 32) * 3 / 2 / 2;
		return ALIGN(sz, SZ_4K);
	}

	hfi_fmt = to_hfi_raw_fmt(v4l2_fmt);
	if (!hfi_fmt)
		return 0;

	return venus_helper_get_framesz_raw(hfi_fmt, width, height);
}