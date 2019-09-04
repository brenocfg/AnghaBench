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
struct TYPE_2__ {struct v4l2_dv_timings timings; } ;

/* Variables and functions */
 int tvp7002_query_dv (struct v4l2_subdev*,int*) ; 
 TYPE_1__* tvp7002_timings ; 

__attribute__((used)) static int tvp7002_query_dv_timings(struct v4l2_subdev *sd,
					struct v4l2_dv_timings *timings)
{
	int index;
	int err = tvp7002_query_dv(sd, &index);

	if (err)
		return err;
	*timings = tvp7002_timings[index].timings;
	return 0;
}