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
 int HFI_VIDEO_CODEC_DIVX ; 
 int HFI_VIDEO_CODEC_H263 ; 
 int HFI_VIDEO_CODEC_H264 ; 
 int HFI_VIDEO_CODEC_HEVC ; 
 int HFI_VIDEO_CODEC_MPEG1 ; 
 int HFI_VIDEO_CODEC_MPEG2 ; 
 int HFI_VIDEO_CODEC_MPEG4 ; 
 int HFI_VIDEO_CODEC_VC1 ; 
 int HFI_VIDEO_CODEC_VP8 ; 
 int HFI_VIDEO_CODEC_VP9 ; 
#define  V4L2_PIX_FMT_H263 139 
#define  V4L2_PIX_FMT_H264 138 
#define  V4L2_PIX_FMT_H264_NO_SC 137 
#define  V4L2_PIX_FMT_HEVC 136 
#define  V4L2_PIX_FMT_MPEG1 135 
#define  V4L2_PIX_FMT_MPEG2 134 
#define  V4L2_PIX_FMT_MPEG4 133 
#define  V4L2_PIX_FMT_VC1_ANNEX_G 132 
#define  V4L2_PIX_FMT_VC1_ANNEX_L 131 
#define  V4L2_PIX_FMT_VP8 130 
#define  V4L2_PIX_FMT_VP9 129 
#define  V4L2_PIX_FMT_XVID 128 

__attribute__((used)) static u32 to_codec_type(u32 pixfmt)
{
	switch (pixfmt) {
	case V4L2_PIX_FMT_H264:
	case V4L2_PIX_FMT_H264_NO_SC:
		return HFI_VIDEO_CODEC_H264;
	case V4L2_PIX_FMT_H263:
		return HFI_VIDEO_CODEC_H263;
	case V4L2_PIX_FMT_MPEG1:
		return HFI_VIDEO_CODEC_MPEG1;
	case V4L2_PIX_FMT_MPEG2:
		return HFI_VIDEO_CODEC_MPEG2;
	case V4L2_PIX_FMT_MPEG4:
		return HFI_VIDEO_CODEC_MPEG4;
	case V4L2_PIX_FMT_VC1_ANNEX_G:
	case V4L2_PIX_FMT_VC1_ANNEX_L:
		return HFI_VIDEO_CODEC_VC1;
	case V4L2_PIX_FMT_VP8:
		return HFI_VIDEO_CODEC_VP8;
	case V4L2_PIX_FMT_VP9:
		return HFI_VIDEO_CODEC_VP9;
	case V4L2_PIX_FMT_XVID:
		return HFI_VIDEO_CODEC_DIVX;
	case V4L2_PIX_FMT_HEVC:
		return HFI_VIDEO_CODEC_HEVC;
	default:
		return 0;
	}
}