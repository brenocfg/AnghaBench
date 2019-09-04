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
struct v4l2_enum_dv_timings {scalar_t__ pad; size_t index; int /*<<< orphan*/  timings; } ;
struct TYPE_2__ {int /*<<< orphan*/  timings; } ;

/* Variables and functions */
 int EINVAL ; 
 size_t NUM_TIMINGS ; 
 TYPE_1__* tvp7002_timings ; 

__attribute__((used)) static int tvp7002_enum_dv_timings(struct v4l2_subdev *sd,
		struct v4l2_enum_dv_timings *timings)
{
	if (timings->pad != 0)
		return -EINVAL;

	/* Check requested format index is within range */
	if (timings->index >= NUM_TIMINGS)
		return -EINVAL;

	timings->timings = tvp7002_timings[timings->index].timings;
	return 0;
}