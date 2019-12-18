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
struct v4l2_subdev {TYPE_2__* ops; } ;
struct v4l2_dv_timings_cap {int /*<<< orphan*/  pad; } ;
struct TYPE_4__ {TYPE_1__* pad; } ;
struct TYPE_3__ {int (* dv_timings_cap ) (struct v4l2_subdev*,struct v4l2_dv_timings_cap*) ;} ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ check_pad (struct v4l2_subdev*,int /*<<< orphan*/ ) ; 
 int stub1 (struct v4l2_subdev*,struct v4l2_dv_timings_cap*) ; 

__attribute__((used)) static int call_dv_timings_cap(struct v4l2_subdev *sd,
			       struct v4l2_dv_timings_cap *cap)
{
	if (!cap)
		return -EINVAL;

	return check_pad(sd, cap->pad) ? :
	       sd->ops->pad->dv_timings_cap(sd, cap);
}