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
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct rvin_dev {TYPE_1__ v4l2_dev; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOIOCTLCMD ; 
 int /*<<< orphan*/  core ; 
 int /*<<< orphan*/  pm_runtime_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s_power ; 
 int v4l2_subdev_call (struct v4l2_subdev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct v4l2_subdev* vin_to_source (struct rvin_dev*) ; 

__attribute__((used)) static int rvin_power_off(struct rvin_dev *vin)
{
	int ret;
	struct v4l2_subdev *sd = vin_to_source(vin);

	ret = v4l2_subdev_call(sd, core, s_power, 0);

	pm_runtime_put(vin->v4l2_dev.dev);

	if (ret < 0 && ret != -ENOIOCTLCMD && ret != -ENODEV)
		return ret;

	return 0;
}