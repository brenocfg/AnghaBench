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
struct v4l2_dv_timings {int dummy; } ;
struct gs {struct v4l2_dv_timings current_timings; } ;

/* Variables and functions */
 int EINVAL ; 
 int get_register_timings (struct v4l2_dv_timings*) ; 
 struct gs* to_gs (struct v4l2_subdev*) ; 

__attribute__((used)) static int gs_s_dv_timings(struct v4l2_subdev *sd,
		    struct v4l2_dv_timings *timings)
{
	struct gs *gs = to_gs(sd);
	int reg_value;

	reg_value = get_register_timings(timings);
	if (reg_value == 0x0)
		return -EINVAL;

	gs->current_timings = *timings;
	return 0;
}