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
struct venc_h264_inst {int dummy; } ;

/* Variables and functions */
#define  V4L2_MPEG_VIDEO_H264_PROFILE_BASELINE 132 
#define  V4L2_MPEG_VIDEO_H264_PROFILE_CONSTRAINED_BASELINE 131 
#define  V4L2_MPEG_VIDEO_H264_PROFILE_EXTENDED 130 
#define  V4L2_MPEG_VIDEO_H264_PROFILE_HIGH 129 
#define  V4L2_MPEG_VIDEO_H264_PROFILE_MAIN 128 
 int /*<<< orphan*/  mtk_vcodec_debug (struct venc_h264_inst*,char*,unsigned int) ; 
 int /*<<< orphan*/  mtk_vcodec_err (struct venc_h264_inst*,char*) ; 

__attribute__((used)) static unsigned int h264_get_profile(struct venc_h264_inst *inst,
				     unsigned int profile)
{
	switch (profile) {
	case V4L2_MPEG_VIDEO_H264_PROFILE_BASELINE:
		return 66;
	case V4L2_MPEG_VIDEO_H264_PROFILE_MAIN:
		return 77;
	case V4L2_MPEG_VIDEO_H264_PROFILE_HIGH:
		return 100;
	case V4L2_MPEG_VIDEO_H264_PROFILE_CONSTRAINED_BASELINE:
		mtk_vcodec_err(inst, "unsupported CONSTRAINED_BASELINE");
		return 0;
	case V4L2_MPEG_VIDEO_H264_PROFILE_EXTENDED:
		mtk_vcodec_err(inst, "unsupported EXTENDED");
		return 0;
	default:
		mtk_vcodec_debug(inst, "unsupported profile %d", profile);
		return 100;
	}
}