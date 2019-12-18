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
struct tw9903 {int norm; } ;

/* Variables and functions */
 int V4L2_STD_525_60 ; 
 struct tw9903* to_state (struct v4l2_subdev*) ; 
 int /*<<< orphan*/  v4l2_ctrl_subdev_log_status (struct v4l2_subdev*) ; 
 int /*<<< orphan*/  v4l2_info (struct v4l2_subdev*,char*,int) ; 

__attribute__((used)) static int tw9903_log_status(struct v4l2_subdev *sd)
{
	struct tw9903 *dec = to_state(sd);
	bool is_60hz = dec->norm & V4L2_STD_525_60;

	v4l2_info(sd, "Standard: %d Hz\n", is_60hz ? 60 : 50);
	v4l2_ctrl_subdev_log_status(sd);
	return 0;
}