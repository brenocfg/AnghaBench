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

/* Variables and functions */
#define  V4L2_CID_MPEG_MFC51_VIDEO_FORCE_FRAME_TYPE 129 
#define  V4L2_CID_MPEG_MFC51_VIDEO_FRAME_SKIP_MODE 128 

__attribute__((used)) static const char * const *mfc51_get_menu(u32 id)
{
	static const char * const mfc51_video_frame_skip[] = {
		"Disabled",
		"Level Limit",
		"VBV/CPB Limit",
		NULL,
	};
	static const char * const mfc51_video_force_frame[] = {
		"Disabled",
		"I Frame",
		"Not Coded",
		NULL,
	};
	switch (id) {
	case V4L2_CID_MPEG_MFC51_VIDEO_FRAME_SKIP_MODE:
		return mfc51_video_frame_skip;
	case V4L2_CID_MPEG_MFC51_VIDEO_FORCE_FRAME_TYPE:
		return mfc51_video_force_frame;
	}
	return NULL;
}