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
typedef  int u16 ;
typedef  enum v4l2_mpeg_video_h264_level { ____Placeholder_v4l2_mpeg_video_h264_level } v4l2_mpeg_video_h264_level ;

/* Variables and functions */
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

__attribute__((used)) static u16 v4l2_level_to_mcu_level(enum v4l2_mpeg_video_h264_level level)
{
	switch (level) {
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
	case V4L2_MPEG_VIDEO_H264_LEVEL_5_0:
		return 50;
	case V4L2_MPEG_VIDEO_H264_LEVEL_5_1:
	default:
		return 51;
	}
}