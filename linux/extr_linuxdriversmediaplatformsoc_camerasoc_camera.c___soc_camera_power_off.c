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
struct soc_camera_device {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOIOCTLCMD ; 
 int /*<<< orphan*/  core ; 
 int /*<<< orphan*/  s_power ; 
 struct v4l2_subdev* soc_camera_to_subdev (struct soc_camera_device*) ; 
 int v4l2_subdev_call (struct v4l2_subdev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int __soc_camera_power_off(struct soc_camera_device *icd)
{
	struct v4l2_subdev *sd = soc_camera_to_subdev(icd);
	int ret;

	ret = v4l2_subdev_call(sd, core, s_power, 0);
	if (ret < 0 && ret != -ENOIOCTLCMD && ret != -ENODEV)
		return ret;

	return 0;
}