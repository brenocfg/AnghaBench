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
 int /*<<< orphan*/  adv748x_hdmi_check_dv_timings ; 
 int /*<<< orphan*/  adv748x_hdmi_timings_cap ; 
 int v4l2_enum_dv_timings_cap (struct v4l2_enum_dv_timings*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int adv748x_hdmi_enum_dv_timings(struct v4l2_subdev *sd,
					struct v4l2_enum_dv_timings *timings)
{
	return v4l2_enum_dv_timings_cap(timings, &adv748x_hdmi_timings_cap,
					adv748x_hdmi_check_dv_timings, NULL);
}