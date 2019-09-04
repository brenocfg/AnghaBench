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
 int V4L2_MPEG_VIDEO_H264_PROFILE_BASELINE ; 
 int V4L2_MPEG_VIDEO_H264_PROFILE_EXTENDED ; 
 int V4L2_MPEG_VIDEO_H264_PROFILE_HIGH ; 
 int V4L2_MPEG_VIDEO_H264_PROFILE_MAIN ; 

int coda_h264_profile(int profile_idc)
{
	switch (profile_idc) {
	case 66: return V4L2_MPEG_VIDEO_H264_PROFILE_BASELINE;
	case 77: return V4L2_MPEG_VIDEO_H264_PROFILE_MAIN;
	case 88: return V4L2_MPEG_VIDEO_H264_PROFILE_EXTENDED;
	case 100: return V4L2_MPEG_VIDEO_H264_PROFILE_HIGH;
	default: return -EINVAL;
	}
}