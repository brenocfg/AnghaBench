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
struct v4l2_subdev_pad_config {int dummy; } ;
struct TYPE_2__ {int numerator; int denominator; } ;
struct v4l2_subdev_frame_interval_enum {int index; scalar_t__ width; scalar_t__ height; TYPE_1__ interval; scalar_t__ pad; } ;
struct v4l2_subdev {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ VGA_HEIGHT ; 
 scalar_t__ VGA_WIDTH ; 

__attribute__((used)) static int ov7740_enum_frame_interval(struct v4l2_subdev *sd,
				struct v4l2_subdev_pad_config *cfg,
				struct v4l2_subdev_frame_interval_enum *fie)
{
	if (fie->pad)
		return -EINVAL;

	if (fie->index >= 1)
		return -EINVAL;

	if ((fie->width != VGA_WIDTH) || (fie->height != VGA_HEIGHT))
		return -EINVAL;

	fie->interval.numerator = 1;
	fie->interval.denominator = 60;

	return 0;
}