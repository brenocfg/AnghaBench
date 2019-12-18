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
 int V4L2_MPEG_VIDEO_MPEG4_LEVEL_0 ; 
 int V4L2_MPEG_VIDEO_MPEG4_LEVEL_1 ; 
 int V4L2_MPEG_VIDEO_MPEG4_LEVEL_2 ; 
 int V4L2_MPEG_VIDEO_MPEG4_LEVEL_3 ; 
 int V4L2_MPEG_VIDEO_MPEG4_LEVEL_4 ; 
 int V4L2_MPEG_VIDEO_MPEG4_LEVEL_5 ; 

int coda_mpeg4_level(int level_idc)
{
	switch (level_idc) {
	case 0:
		return V4L2_MPEG_VIDEO_MPEG4_LEVEL_0;
	case 1:
		return V4L2_MPEG_VIDEO_MPEG4_LEVEL_1;
	case 2:
		return V4L2_MPEG_VIDEO_MPEG4_LEVEL_2;
	case 3:
		return V4L2_MPEG_VIDEO_MPEG4_LEVEL_3;
	case 4:
		return V4L2_MPEG_VIDEO_MPEG4_LEVEL_4;
	case 5:
		return V4L2_MPEG_VIDEO_MPEG4_LEVEL_5;
	default:
		return -EINVAL;
	}
}