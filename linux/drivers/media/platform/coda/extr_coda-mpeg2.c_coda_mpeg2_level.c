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
 int V4L2_MPEG_VIDEO_MPEG2_LEVEL_HIGH ; 
 int V4L2_MPEG_VIDEO_MPEG2_LEVEL_HIGH_1440 ; 
 int V4L2_MPEG_VIDEO_MPEG2_LEVEL_LOW ; 
 int V4L2_MPEG_VIDEO_MPEG2_LEVEL_MAIN ; 

int coda_mpeg2_level(int level_idc)
{
	switch (level_idc) {
	case 10:
		return V4L2_MPEG_VIDEO_MPEG2_LEVEL_LOW;
	case 8:
		return V4L2_MPEG_VIDEO_MPEG2_LEVEL_MAIN;
	case 6:
		return V4L2_MPEG_VIDEO_MPEG2_LEVEL_HIGH_1440;
	case 4:
		return V4L2_MPEG_VIDEO_MPEG2_LEVEL_HIGH;
	default:
		return -EINVAL;
	}
}