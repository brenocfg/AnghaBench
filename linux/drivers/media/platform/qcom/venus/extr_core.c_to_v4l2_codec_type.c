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
#define  HFI_VIDEO_CODEC_DIVX 137 
#define  HFI_VIDEO_CODEC_DIVX_311 136 
#define  HFI_VIDEO_CODEC_H263 135 
#define  HFI_VIDEO_CODEC_H264 134 
#define  HFI_VIDEO_CODEC_MPEG1 133 
#define  HFI_VIDEO_CODEC_MPEG2 132 
#define  HFI_VIDEO_CODEC_MPEG4 131 
#define  HFI_VIDEO_CODEC_VC1 130 
#define  HFI_VIDEO_CODEC_VP8 129 
#define  HFI_VIDEO_CODEC_VP9 128 
 int V4L2_PIX_FMT_H263 ; 
 int V4L2_PIX_FMT_H264 ; 
 int V4L2_PIX_FMT_MPEG1 ; 
 int V4L2_PIX_FMT_MPEG2 ; 
 int V4L2_PIX_FMT_MPEG4 ; 
 int V4L2_PIX_FMT_VC1_ANNEX_G ; 
 int V4L2_PIX_FMT_VP8 ; 
 int V4L2_PIX_FMT_VP9 ; 
 int V4L2_PIX_FMT_XVID ; 

__attribute__((used)) static u32 to_v4l2_codec_type(u32 codec)
{
	switch (codec) {
	case HFI_VIDEO_CODEC_H264:
		return V4L2_PIX_FMT_H264;
	case HFI_VIDEO_CODEC_H263:
		return V4L2_PIX_FMT_H263;
	case HFI_VIDEO_CODEC_MPEG1:
		return V4L2_PIX_FMT_MPEG1;
	case HFI_VIDEO_CODEC_MPEG2:
		return V4L2_PIX_FMT_MPEG2;
	case HFI_VIDEO_CODEC_MPEG4:
		return V4L2_PIX_FMT_MPEG4;
	case HFI_VIDEO_CODEC_VC1:
		return V4L2_PIX_FMT_VC1_ANNEX_G;
	case HFI_VIDEO_CODEC_VP8:
		return V4L2_PIX_FMT_VP8;
	case HFI_VIDEO_CODEC_VP9:
		return V4L2_PIX_FMT_VP9;
	case HFI_VIDEO_CODEC_DIVX:
	case HFI_VIDEO_CODEC_DIVX_311:
		return V4L2_PIX_FMT_XVID;
	default:
		return 0;
	}
}