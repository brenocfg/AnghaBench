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
struct v4l2_subdev {int dummy; } ;
struct v4l2_dv_timings {int dummy; } ;
struct tvp7002 {TYPE_1__* current_timings; } ;
struct TYPE_2__ {struct v4l2_dv_timings timings; } ;

/* Variables and functions */
 struct tvp7002* to_tvp7002 (struct v4l2_subdev*) ; 

__attribute__((used)) static int tvp7002_g_dv_timings(struct v4l2_subdev *sd,
					struct v4l2_dv_timings *dv_timings)
{
	struct tvp7002 *device = to_tvp7002(sd);

	*dv_timings = device->current_timings->timings;
	return 0;
}