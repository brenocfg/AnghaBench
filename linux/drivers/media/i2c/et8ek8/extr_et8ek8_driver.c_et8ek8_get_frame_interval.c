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
struct v4l2_subdev_frame_interval {int /*<<< orphan*/  interval; } ;
struct v4l2_subdev {int dummy; } ;
struct et8ek8_sensor {TYPE_2__* current_reglist; } ;
struct TYPE_3__ {int /*<<< orphan*/  timeperframe; } ;
struct TYPE_4__ {TYPE_1__ mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct v4l2_subdev_frame_interval*,int /*<<< orphan*/ ,int) ; 
 struct et8ek8_sensor* to_et8ek8_sensor (struct v4l2_subdev*) ; 

__attribute__((used)) static int et8ek8_get_frame_interval(struct v4l2_subdev *subdev,
				     struct v4l2_subdev_frame_interval *fi)
{
	struct et8ek8_sensor *sensor = to_et8ek8_sensor(subdev);

	memset(fi, 0, sizeof(*fi));
	fi->interval = sensor->current_reglist->mode.timeperframe;

	return 0;
}