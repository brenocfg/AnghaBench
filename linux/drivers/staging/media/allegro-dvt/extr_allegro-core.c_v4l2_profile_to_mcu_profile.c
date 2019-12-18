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
typedef  int u8 ;
typedef  enum v4l2_mpeg_video_h264_profile { ____Placeholder_v4l2_mpeg_video_h264_profile } v4l2_mpeg_video_h264_profile ;

/* Variables and functions */
#define  V4L2_MPEG_VIDEO_H264_PROFILE_BASELINE 128 

__attribute__((used)) static u8 v4l2_profile_to_mcu_profile(enum v4l2_mpeg_video_h264_profile profile)
{
	switch (profile) {
	case V4L2_MPEG_VIDEO_H264_PROFILE_BASELINE:
	default:
		return 66;
	}
}