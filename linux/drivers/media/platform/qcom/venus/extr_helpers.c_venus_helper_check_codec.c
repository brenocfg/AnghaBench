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
struct venus_inst {int session_type; struct venus_core* core; } ;
struct venus_core {int enc_codecs; int dec_codecs; } ;

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
#define  V4L2_PIX_FMT_H263 138 
#define  V4L2_PIX_FMT_H264 137 
#define  V4L2_PIX_FMT_HEVC 136 
#define  V4L2_PIX_FMT_MPEG1 135 
#define  V4L2_PIX_FMT_MPEG2 134 
#define  V4L2_PIX_FMT_MPEG4 133 
#define  V4L2_PIX_FMT_VC1_ANNEX_G 132 
#define  V4L2_PIX_FMT_VC1_ANNEX_L 131 
#define  V4L2_PIX_FMT_VP8 130 
#define  V4L2_PIX_FMT_VP9 129 
#define  V4L2_PIX_FMT_XVID 128 
 int VIDC_SESSION_TYPE_DEC ; 
 int VIDC_SESSION_TYPE_ENC ; 

bool venus_helper_check_codec(struct venus_inst *inst, u32 v4l2_pixfmt)
{
	struct venus_core *core = inst->core;
	u32 session_type = inst->session_type;
	u32 codec;

	switch (v4l2_pixfmt) {
	case V4L2_PIX_FMT_H264:
		codec = HFI_VIDEO_CODEC_H264;
		break;
	case V4L2_PIX_FMT_H263:
		codec = HFI_VIDEO_CODEC_H263;
		break;
	case V4L2_PIX_FMT_MPEG1:
		codec = HFI_VIDEO_CODEC_MPEG1;
		break;
	case V4L2_PIX_FMT_MPEG2:
		codec = HFI_VIDEO_CODEC_MPEG2;
		break;
	case V4L2_PIX_FMT_MPEG4:
		codec = HFI_VIDEO_CODEC_MPEG4;
		break;
	case V4L2_PIX_FMT_VC1_ANNEX_G:
	case V4L2_PIX_FMT_VC1_ANNEX_L:
		codec = HFI_VIDEO_CODEC_VC1;
		break;
	case V4L2_PIX_FMT_VP8:
		codec = HFI_VIDEO_CODEC_VP8;
		break;
	case V4L2_PIX_FMT_VP9:
		codec = HFI_VIDEO_CODEC_VP9;
		break;
	case V4L2_PIX_FMT_XVID:
		codec = HFI_VIDEO_CODEC_DIVX;
		break;
	case V4L2_PIX_FMT_HEVC:
		codec = HFI_VIDEO_CODEC_HEVC;
		break;
	default:
		return false;
	}

	if (session_type == VIDC_SESSION_TYPE_ENC && core->enc_codecs & codec)
		return true;

	if (session_type == VIDC_SESSION_TYPE_DEC && core->dec_codecs & codec)
		return true;

	return false;
}