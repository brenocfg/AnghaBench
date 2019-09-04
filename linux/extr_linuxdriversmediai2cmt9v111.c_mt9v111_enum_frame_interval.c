#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct v4l2_subdev_pad_config {int dummy; } ;
struct TYPE_6__ {scalar_t__ width; scalar_t__ height; } ;
struct TYPE_5__ {int numerator; TYPE_2__ denominator; } ;
struct v4l2_subdev_frame_interval_enum {unsigned int index; scalar_t__ width; scalar_t__ height; TYPE_1__ interval; scalar_t__ pad; } ;
struct v4l2_subdev {int dummy; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (TYPE_2__*) ; 
 int EINVAL ; 
 TYPE_2__* mt9v111_frame_intervals ; 
 TYPE_2__* mt9v111_frame_sizes ; 

__attribute__((used)) static int mt9v111_enum_frame_interval(struct v4l2_subdev *sd,
				struct v4l2_subdev_pad_config *cfg,
				struct v4l2_subdev_frame_interval_enum *fie)
{
	unsigned int i;

	if (fie->pad || fie->index >= ARRAY_SIZE(mt9v111_frame_intervals))
		return -EINVAL;

	for (i = 0; i < ARRAY_SIZE(mt9v111_frame_sizes); i++)
		if (fie->width == mt9v111_frame_sizes[i].width &&
		    fie->height == mt9v111_frame_sizes[i].height)
			break;

	if (i == ARRAY_SIZE(mt9v111_frame_sizes))
		return -EINVAL;

	fie->interval.numerator = 1;
	fie->interval.denominator = mt9v111_frame_intervals[fie->index];

	return 0;
}