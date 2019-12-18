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
typedef  enum v4l2_mpeg_video_h264_level { ____Placeholder_v4l2_mpeg_video_h264_level } v4l2_mpeg_video_h264_level ;

/* Variables and functions */
#define  V4L2_MPEG_VIDEO_H264_LEVEL_1B 143 
#define  V4L2_MPEG_VIDEO_H264_LEVEL_1_0 142 
#define  V4L2_MPEG_VIDEO_H264_LEVEL_1_1 141 
#define  V4L2_MPEG_VIDEO_H264_LEVEL_1_2 140 
#define  V4L2_MPEG_VIDEO_H264_LEVEL_1_3 139 
#define  V4L2_MPEG_VIDEO_H264_LEVEL_2_0 138 
#define  V4L2_MPEG_VIDEO_H264_LEVEL_2_1 137 
#define  V4L2_MPEG_VIDEO_H264_LEVEL_2_2 136 
#define  V4L2_MPEG_VIDEO_H264_LEVEL_3_0 135 
#define  V4L2_MPEG_VIDEO_H264_LEVEL_3_1 134 
#define  V4L2_MPEG_VIDEO_H264_LEVEL_3_2 133 
#define  V4L2_MPEG_VIDEO_H264_LEVEL_4_0 132 
#define  V4L2_MPEG_VIDEO_H264_LEVEL_4_1 131 
#define  V4L2_MPEG_VIDEO_H264_LEVEL_4_2 130 
#define  V4L2_MPEG_VIDEO_H264_LEVEL_5_0 129 
#define  V4L2_MPEG_VIDEO_H264_LEVEL_5_1 128 

__attribute__((used)) static unsigned int maximum_bitrate(enum v4l2_mpeg_video_h264_level level)
{
	switch (level) {
	case V4L2_MPEG_VIDEO_H264_LEVEL_1_0:
		return 64000;
	case V4L2_MPEG_VIDEO_H264_LEVEL_1B:
		return 128000;
	case V4L2_MPEG_VIDEO_H264_LEVEL_1_1:
		return 192000;
	case V4L2_MPEG_VIDEO_H264_LEVEL_1_2:
		return 384000;
	case V4L2_MPEG_VIDEO_H264_LEVEL_1_3:
		return 768000;
	case V4L2_MPEG_VIDEO_H264_LEVEL_2_0:
		return 2000000;
	case V4L2_MPEG_VIDEO_H264_LEVEL_2_1:
		return 4000000;
	case V4L2_MPEG_VIDEO_H264_LEVEL_2_2:
		return 4000000;
	case V4L2_MPEG_VIDEO_H264_LEVEL_3_0:
		return 10000000;
	case V4L2_MPEG_VIDEO_H264_LEVEL_3_1:
		return 14000000;
	case V4L2_MPEG_VIDEO_H264_LEVEL_3_2:
		return 20000000;
	case V4L2_MPEG_VIDEO_H264_LEVEL_4_0:
		return 20000000;
	case V4L2_MPEG_VIDEO_H264_LEVEL_4_1:
		return 50000000;
	case V4L2_MPEG_VIDEO_H264_LEVEL_4_2:
		return 50000000;
	case V4L2_MPEG_VIDEO_H264_LEVEL_5_0:
		return 135000000;
	case V4L2_MPEG_VIDEO_H264_LEVEL_5_1:
	default:
		return 240000000;
	}
}