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
typedef  enum v4l2_mpeg_video_hevc_level { ____Placeholder_v4l2_mpeg_video_hevc_level } v4l2_mpeg_video_hevc_level ;

/* Variables and functions */

__attribute__((used)) static inline int hevc_level(enum v4l2_mpeg_video_hevc_level lvl)
{
	static unsigned int t[] = {
		/* V4L2_MPEG_VIDEO_HEVC_LEVEL_1    */ 10,
		/* V4L2_MPEG_VIDEO_HEVC_LEVEL_2    */ 20,
		/* V4L2_MPEG_VIDEO_HEVC_LEVEL_2_1  */ 21,
		/* V4L2_MPEG_VIDEO_HEVC_LEVEL_3    */ 30,
		/* V4L2_MPEG_VIDEO_HEVC_LEVEL_3_1  */ 31,
		/* V4L2_MPEG_VIDEO_HEVC_LEVEL_4    */ 40,
		/* V4L2_MPEG_VIDEO_HEVC_LEVEL_4_1  */ 41,
		/* V4L2_MPEG_VIDEO_HEVC_LEVEL_5    */ 50,
		/* V4L2_MPEG_VIDEO_HEVC_LEVEL_5_1  */ 51,
		/* V4L2_MPEG_VIDEO_HEVC_LEVEL_5_2  */ 52,
		/* V4L2_MPEG_VIDEO_HEVC_LEVEL_6    */ 60,
		/* V4L2_MPEG_VIDEO_HEVC_LEVEL_6_1  */ 61,
		/* V4L2_MPEG_VIDEO_HEVC_LEVEL_6_2  */ 62,
	};
	return t[lvl];
}