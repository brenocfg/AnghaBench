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
typedef  int u64 ;
struct TYPE_2__ {int denominator; scalar_t__ numerator; } ;
struct vivid_dev {scalar_t__ field_cap; int cap_frame_eof_offset; int cap_frame_period; TYPE_1__ timeperframe_vid_cap; } ;

/* Variables and functions */
 scalar_t__ V4L2_FIELD_ALTERNATE ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  do_div (int,int) ; 

__attribute__((used)) static void vivid_cap_update_frame_period(struct vivid_dev *dev)
{
	u64 f_period;

	f_period = (u64)dev->timeperframe_vid_cap.numerator * 1000000000;
	if (WARN_ON(dev->timeperframe_vid_cap.denominator == 0))
		dev->timeperframe_vid_cap.denominator = 1;
	do_div(f_period, dev->timeperframe_vid_cap.denominator);
	if (dev->field_cap == V4L2_FIELD_ALTERNATE)
		f_period >>= 1;
	/*
	 * If "End of Frame", then offset the exposure time by 0.9
	 * of the frame period.
	 */
	dev->cap_frame_eof_offset = f_period * 9;
	do_div(dev->cap_frame_eof_offset, 10);
	dev->cap_frame_period = f_period;
}