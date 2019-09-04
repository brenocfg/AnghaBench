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
struct v4l2_enum_dv_timings {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  tda1997x_dv_timings_cap ; 
 int v4l2_enum_dv_timings_cap (struct v4l2_enum_dv_timings*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int tda1997x_enum_dv_timings(struct v4l2_subdev *sd,
				    struct v4l2_enum_dv_timings *timings)
{
	return v4l2_enum_dv_timings_cap(timings, &tda1997x_dv_timings_cap,
					NULL, NULL);
}