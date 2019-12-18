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
typedef  enum v4l2_mpeg_video_bitrate_mode { ____Placeholder_v4l2_mpeg_video_bitrate_mode } v4l2_mpeg_video_bitrate_mode ;

/* Variables and functions */
#define  V4L2_MPEG_VIDEO_BITRATE_MODE_CBR 129 
#define  V4L2_MPEG_VIDEO_BITRATE_MODE_VBR 128 

__attribute__((used)) static u32
v4l2_bitrate_mode_to_mcu_mode(enum v4l2_mpeg_video_bitrate_mode mode)
{
	switch (mode) {
	case V4L2_MPEG_VIDEO_BITRATE_MODE_VBR:
		return 2;
	case V4L2_MPEG_VIDEO_BITRATE_MODE_CBR:
	default:
		return 1;
	}
}