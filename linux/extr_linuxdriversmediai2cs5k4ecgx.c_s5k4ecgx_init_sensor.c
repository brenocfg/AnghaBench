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

/* Variables and functions */
 int /*<<< orphan*/  msleep (int) ; 
 int s5k4ecgx_load_firmware (struct v4l2_subdev*) ; 
 int s5k4ecgx_set_ahb_address (struct v4l2_subdev*) ; 
 int /*<<< orphan*/  v4l2_err (struct v4l2_subdev*,char*) ; 

__attribute__((used)) static int s5k4ecgx_init_sensor(struct v4l2_subdev *sd)
{
	int ret;

	ret = s5k4ecgx_set_ahb_address(sd);

	/* The delay is from manufacturer's settings */
	msleep(100);

	if (!ret)
		ret = s5k4ecgx_load_firmware(sd);
	if (ret)
		v4l2_err(sd, "Failed to write initial settings\n");

	return ret;
}