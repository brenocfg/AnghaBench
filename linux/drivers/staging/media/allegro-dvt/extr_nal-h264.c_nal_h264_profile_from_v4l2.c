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
typedef  enum v4l2_mpeg_video_h264_profile { ____Placeholder_v4l2_mpeg_video_h264_profile } v4l2_mpeg_video_h264_profile ;

/* Variables and functions */
 int EINVAL ; 
#define  V4L2_MPEG_VIDEO_H264_PROFILE_BASELINE 131 
#define  V4L2_MPEG_VIDEO_H264_PROFILE_EXTENDED 130 
#define  V4L2_MPEG_VIDEO_H264_PROFILE_HIGH 129 
#define  V4L2_MPEG_VIDEO_H264_PROFILE_MAIN 128 

int nal_h264_profile_from_v4l2(enum v4l2_mpeg_video_h264_profile profile)
{
	switch (profile) {
	case V4L2_MPEG_VIDEO_H264_PROFILE_BASELINE:
		return 66;
	case V4L2_MPEG_VIDEO_H264_PROFILE_MAIN:
		return 77;
	case V4L2_MPEG_VIDEO_H264_PROFILE_EXTENDED:
		return 88;
	case V4L2_MPEG_VIDEO_H264_PROFILE_HIGH:
		return 100;
	default:
		return -EINVAL;
	}
}