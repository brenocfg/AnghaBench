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

/* Variables and functions */
 int EINVAL ; 
 int V4L2_MPEG_VIDEO_H264_LEVEL_1B ; 
 int V4L2_MPEG_VIDEO_H264_LEVEL_1_0 ; 
 int V4L2_MPEG_VIDEO_H264_LEVEL_1_1 ; 
 int V4L2_MPEG_VIDEO_H264_LEVEL_1_2 ; 
 int V4L2_MPEG_VIDEO_H264_LEVEL_1_3 ; 
 int V4L2_MPEG_VIDEO_H264_LEVEL_2_0 ; 
 int V4L2_MPEG_VIDEO_H264_LEVEL_2_1 ; 
 int V4L2_MPEG_VIDEO_H264_LEVEL_2_2 ; 
 int V4L2_MPEG_VIDEO_H264_LEVEL_3_0 ; 
 int V4L2_MPEG_VIDEO_H264_LEVEL_3_1 ; 
 int V4L2_MPEG_VIDEO_H264_LEVEL_3_2 ; 
 int V4L2_MPEG_VIDEO_H264_LEVEL_4_0 ; 
 int V4L2_MPEG_VIDEO_H264_LEVEL_4_1 ; 
 int V4L2_MPEG_VIDEO_H264_LEVEL_4_2 ; 
 int V4L2_MPEG_VIDEO_H264_LEVEL_5_0 ; 
 int V4L2_MPEG_VIDEO_H264_LEVEL_5_1 ; 

int coda_h264_level(int level_idc)
{
	switch (level_idc) {
	case 10: return V4L2_MPEG_VIDEO_H264_LEVEL_1_0;
	case 9:  return V4L2_MPEG_VIDEO_H264_LEVEL_1B;
	case 11: return V4L2_MPEG_VIDEO_H264_LEVEL_1_1;
	case 12: return V4L2_MPEG_VIDEO_H264_LEVEL_1_2;
	case 13: return V4L2_MPEG_VIDEO_H264_LEVEL_1_3;
	case 20: return V4L2_MPEG_VIDEO_H264_LEVEL_2_0;
	case 21: return V4L2_MPEG_VIDEO_H264_LEVEL_2_1;
	case 22: return V4L2_MPEG_VIDEO_H264_LEVEL_2_2;
	case 30: return V4L2_MPEG_VIDEO_H264_LEVEL_3_0;
	case 31: return V4L2_MPEG_VIDEO_H264_LEVEL_3_1;
	case 32: return V4L2_MPEG_VIDEO_H264_LEVEL_3_2;
	case 40: return V4L2_MPEG_VIDEO_H264_LEVEL_4_0;
	case 41: return V4L2_MPEG_VIDEO_H264_LEVEL_4_1;
	case 42: return V4L2_MPEG_VIDEO_H264_LEVEL_4_2;
	case 50: return V4L2_MPEG_VIDEO_H264_LEVEL_5_0;
	case 51: return V4L2_MPEG_VIDEO_H264_LEVEL_5_1;
	default: return -EINVAL;
	}
}