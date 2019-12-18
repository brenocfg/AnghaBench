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
struct pxa_camera_dev {int dummy; } ;

/* Variables and functions */
 int ENOIOCTLCMD ; 
 int /*<<< orphan*/  core ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,char*,int) ; 
 int /*<<< orphan*/  pcdev_to_dev (struct pxa_camera_dev*) ; 
 int /*<<< orphan*/  s_power ; 
 int sensor_call (struct pxa_camera_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int pxac_sensor_set_power(struct pxa_camera_dev *pcdev, int on)
{
	int ret;

	ret = sensor_call(pcdev, core, s_power, on);
	if (ret == -ENOIOCTLCMD)
		ret = 0;
	if (ret) {
		dev_warn(pcdev_to_dev(pcdev),
			 "Failed to put subdevice in %s mode: %d\n",
			 on ? "normal operation" : "power saving", ret);
	}

	return ret;
}