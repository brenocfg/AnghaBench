#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  numerator; int /*<<< orphan*/  denominator; } ;
struct vs6624 {TYPE_2__ frame_rate; } ;
struct TYPE_3__ {int /*<<< orphan*/  denominator; int /*<<< orphan*/  numerator; } ;
struct v4l2_subdev_frame_interval {TYPE_1__ interval; } ;
struct v4l2_subdev {int dummy; } ;

/* Variables and functions */
 struct vs6624* to_vs6624 (struct v4l2_subdev*) ; 

__attribute__((used)) static int vs6624_g_frame_interval(struct v4l2_subdev *sd,
				   struct v4l2_subdev_frame_interval *ival)
{
	struct vs6624 *sensor = to_vs6624(sd);

	ival->interval.numerator = sensor->frame_rate.denominator;
	ival->interval.denominator = sensor->frame_rate.numerator;
	return 0;
}