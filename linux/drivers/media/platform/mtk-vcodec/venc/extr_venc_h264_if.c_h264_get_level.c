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
#define  V4L2_MPEG_VIDEO_H264_LEVEL_1B 141 
#define  V4L2_MPEG_VIDEO_H264_LEVEL_1_0 140 
#define  V4L2_MPEG_VIDEO_H264_LEVEL_1_1 139 
#define  V4L2_MPEG_VIDEO_H264_LEVEL_1_2 138 
#define  V4L2_MPEG_VIDEO_H264_LEVEL_1_3 137 
#define  V4L2_MPEG_VIDEO_H264_LEVEL_2_0 136 
#define  V4L2_MPEG_VIDEO_H264_LEVEL_2_1 135 
#define  V4L2_MPEG_VIDEO_H264_LEVEL_2_2 134 
#define  V4L2_MPEG_VIDEO_H264_LEVEL_3_0 133 
#define  V4L2_MPEG_VIDEO_H264_LEVEL_3_1 132 
#define  V4L2_MPEG_VIDEO_H264_LEVEL_3_2 131 
#define  V4L2_MPEG_VIDEO_H264_LEVEL_4_0 130 
#define  V4L2_MPEG_VIDEO_H264_LEVEL_4_1 129 
#define  V4L2_MPEG_VIDEO_H264_LEVEL_4_2 128 
 int /*<<< orphan*/  mtk_vcodec_debug (struct venc_h264_inst*,char*,unsigned int) ; 
 int /*<<< orphan*/  mtk_vcodec_err (struct venc_h264_inst*,char*) ; 

__attribute__((used)) static unsigned int h264_get_level(struct venc_h264_inst *inst,
				   unsigned int level)
{
	switch (level) {
	case V4L2_MPEG_VIDEO_H264_LEVEL_1B:
		mtk_vcodec_err(inst, "unsupported 1B");
		return 0;
	case V4L2_MPEG_VIDEO_H264_LEVEL_1_0:
		return 10;
	case V4L2_MPEG_VIDEO_H264_LEVEL_1_1:
		return 11;
	case V4L2_MPEG_VIDEO_H264_LEVEL_1_2:
		return 12;
	case V4L2_MPEG_VIDEO_H264_LEVEL_1_3:
		return 13;
	case V4L2_MPEG_VIDEO_H264_LEVEL_2_0:
		return 20;
	case V4L2_MPEG_VIDEO_H264_LEVEL_2_1:
		return 21;
	case V4L2_MPEG_VIDEO_H264_LEVEL_2_2:
		return 22;
	case V4L2_MPEG_VIDEO_H264_LEVEL_3_0:
		return 30;
	case V4L2_MPEG_VIDEO_H264_LEVEL_3_1:
		return 31;
	case V4L2_MPEG_VIDEO_H264_LEVEL_3_2:
		return 32;
	case V4L2_MPEG_VIDEO_H264_LEVEL_4_0:
		return 40;
	case V4L2_MPEG_VIDEO_H264_LEVEL_4_1:
		return 41;
	case V4L2_MPEG_VIDEO_H264_LEVEL_4_2:
		return 42;
	default:
		mtk_vcodec_debug(inst, "unsupported level %d", level);
		return 31;
	}
}