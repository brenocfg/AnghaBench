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
struct v4l2_fract {int numerator; int denominator; } ;

/* Variables and functions */
 int V4L2_STD_525_60 ; 

void v4l2_video_std_frame_period(int id, struct v4l2_fract *frameperiod)
{
	if (id & V4L2_STD_525_60) {
		frameperiod->numerator = 1001;
		frameperiod->denominator = 30000;
	} else {
		frameperiod->numerator = 1;
		frameperiod->denominator = 25;
	}
}