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
struct v4l2_subdev {int dummy; } ;
struct tvp5150 {scalar_t__ mbus_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  TVP5150_MISC_CTL ; 
 int TVP5150_MISC_CTL_CLOCK_OE ; 
 int TVP5150_MISC_CTL_SYNC_OE ; 
 int TVP5150_MISC_CTL_YCBCR_OE ; 
 scalar_t__ V4L2_MBUS_PARALLEL ; 
 struct tvp5150* to_tvp5150 (struct v4l2_subdev*) ; 
 int tvp5150_read (struct v4l2_subdev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tvp5150_write (struct v4l2_subdev*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int tvp5150_s_stream(struct v4l2_subdev *sd, int enable)
{
	struct tvp5150 *decoder = to_tvp5150(sd);
	int val;

	/* Enable or disable the video output signals. */
	val = tvp5150_read(sd, TVP5150_MISC_CTL);
	if (val < 0)
		return val;

	val &= ~(TVP5150_MISC_CTL_YCBCR_OE | TVP5150_MISC_CTL_SYNC_OE |
		 TVP5150_MISC_CTL_CLOCK_OE);

	if (enable) {
		/*
		 * Enable the YCbCr and clock outputs. In discrete sync mode
		 * (non-BT.656) additionally enable the the sync outputs.
		 */
		val |= TVP5150_MISC_CTL_YCBCR_OE | TVP5150_MISC_CTL_CLOCK_OE;
		if (decoder->mbus_type == V4L2_MBUS_PARALLEL)
			val |= TVP5150_MISC_CTL_SYNC_OE;
	}

	tvp5150_write(sd, TVP5150_MISC_CTL, val);

	return 0;
}