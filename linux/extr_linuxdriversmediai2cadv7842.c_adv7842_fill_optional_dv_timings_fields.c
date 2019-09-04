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

/* Variables and functions */
 int /*<<< orphan*/  adv7842_check_dv_timings ; 
 int /*<<< orphan*/  adv7842_get_dv_timings_cap (struct v4l2_subdev*) ; 
 scalar_t__ is_digital_input (struct v4l2_subdev*) ; 
 int /*<<< orphan*/  v4l2_find_dv_timings_cap (struct v4l2_dv_timings*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void adv7842_fill_optional_dv_timings_fields(struct v4l2_subdev *sd,
		struct v4l2_dv_timings *timings)
{
	v4l2_find_dv_timings_cap(timings, adv7842_get_dv_timings_cap(sd),
			is_digital_input(sd) ? 250000 : 1000000,
			adv7842_check_dv_timings, NULL);
}