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
 int V4L2_MPEG_VIDEO_MPEG4_PROFILE_ADVANCED_CODING_EFFICIENCY ; 
 int V4L2_MPEG_VIDEO_MPEG4_PROFILE_ADVANCED_SIMPLE ; 
 int V4L2_MPEG_VIDEO_MPEG4_PROFILE_CORE ; 
 int V4L2_MPEG_VIDEO_MPEG4_PROFILE_SIMPLE ; 
 int V4L2_MPEG_VIDEO_MPEG4_PROFILE_SIMPLE_SCALABLE ; 

int coda_mpeg4_profile(int profile_idc)
{
	switch (profile_idc) {
	case 0:
		return V4L2_MPEG_VIDEO_MPEG4_PROFILE_SIMPLE;
	case 15:
		return V4L2_MPEG_VIDEO_MPEG4_PROFILE_ADVANCED_SIMPLE;
	case 2:
		return V4L2_MPEG_VIDEO_MPEG4_PROFILE_CORE;
	case 1:
		return V4L2_MPEG_VIDEO_MPEG4_PROFILE_SIMPLE_SCALABLE;
	case 11:
		return V4L2_MPEG_VIDEO_MPEG4_PROFILE_ADVANCED_CODING_EFFICIENCY;
	default:
		return -EINVAL;
	}
}