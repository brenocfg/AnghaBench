#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_2__ {int /*<<< orphan*/  polarities; } ;
struct aspeed_video {TYPE_1__ detected_timings; } ;

/* Variables and functions */
 int NUM_POLARITY_CHECKS ; 
 int /*<<< orphan*/  V4L2_DV_HSYNC_POS_POL ; 
 int /*<<< orphan*/  V4L2_DV_VSYNC_POS_POL ; 
 int /*<<< orphan*/  VE_CTRL ; 
 int VE_CTRL_HSYNC_POL ; 
 int VE_CTRL_VSYNC_POL ; 
 int /*<<< orphan*/  VE_MODE_DETECT_STATUS ; 
 int VE_MODE_DETECT_STATUS_HSYNC ; 
 int VE_MODE_DETECT_STATUS_VSYNC ; 
 int aspeed_video_read (struct aspeed_video*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aspeed_video_update (struct aspeed_video*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void aspeed_video_check_and_set_polarity(struct aspeed_video *video)
{
	int i;
	int hsync_counter = 0;
	int vsync_counter = 0;
	u32 sts;

	for (i = 0; i < NUM_POLARITY_CHECKS; ++i) {
		sts = aspeed_video_read(video, VE_MODE_DETECT_STATUS);
		if (sts & VE_MODE_DETECT_STATUS_VSYNC)
			vsync_counter--;
		else
			vsync_counter++;

		if (sts & VE_MODE_DETECT_STATUS_HSYNC)
			hsync_counter--;
		else
			hsync_counter++;
	}

	if (hsync_counter < 0 || vsync_counter < 0) {
		u32 ctrl = 0;

		if (hsync_counter < 0) {
			ctrl = VE_CTRL_HSYNC_POL;
			video->detected_timings.polarities &=
				~V4L2_DV_HSYNC_POS_POL;
		} else {
			video->detected_timings.polarities |=
				V4L2_DV_HSYNC_POS_POL;
		}

		if (vsync_counter < 0) {
			ctrl = VE_CTRL_VSYNC_POL;
			video->detected_timings.polarities &=
				~V4L2_DV_VSYNC_POS_POL;
		} else {
			video->detected_timings.polarities |=
				V4L2_DV_VSYNC_POS_POL;
		}

		if (ctrl)
			aspeed_video_update(video, VE_CTRL, 0, ctrl);
	}
}