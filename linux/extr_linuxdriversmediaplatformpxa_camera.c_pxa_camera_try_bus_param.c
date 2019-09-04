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
struct v4l2_mbus_config {int /*<<< orphan*/  flags; int /*<<< orphan*/  type; } ;
struct pxa_camera_dev {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOIOCTLCMD ; 
 int /*<<< orphan*/  V4L2_MBUS_PARALLEL ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  g_mbus_config ; 
 int /*<<< orphan*/  pcdev_to_dev (struct pxa_camera_dev*) ; 
 unsigned long pxa_mbus_config_compatible (struct v4l2_mbus_config*,unsigned long) ; 
 int sensor_call (struct pxa_camera_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct v4l2_mbus_config*) ; 
 int test_platform_param (struct pxa_camera_dev*,unsigned char,unsigned long*) ; 
 int /*<<< orphan*/  video ; 

__attribute__((used)) static int pxa_camera_try_bus_param(struct pxa_camera_dev *pcdev,
				    unsigned char buswidth)
{
	struct v4l2_mbus_config cfg = {.type = V4L2_MBUS_PARALLEL,};
	unsigned long bus_flags, common_flags;
	int ret = test_platform_param(pcdev, buswidth, &bus_flags);

	if (ret < 0)
		return ret;

	ret = sensor_call(pcdev, video, g_mbus_config, &cfg);
	if (!ret) {
		common_flags = pxa_mbus_config_compatible(&cfg,
							  bus_flags);
		if (!common_flags) {
			dev_warn(pcdev_to_dev(pcdev),
				 "Flags incompatible: camera 0x%x, host 0x%lx\n",
				 cfg.flags, bus_flags);
			return -EINVAL;
		}
	} else if (ret == -ENOIOCTLCMD) {
		ret = 0;
	}

	return ret;
}