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
struct v4l2_mbus_config {int /*<<< orphan*/  type; } ;
struct soc_camera_device {int dummy; } ;

/* Variables and functions */
 unsigned long CEU_BUS_FLAGS ; 
 int EINVAL ; 
 int ENOIOCTLCMD ; 
 int /*<<< orphan*/  V4L2_MBUS_PARALLEL ; 
 int /*<<< orphan*/  g_mbus_config ; 
 struct v4l2_subdev* soc_camera_to_subdev (struct soc_camera_device*) ; 
 unsigned long soc_mbus_config_compatible (struct v4l2_mbus_config*,unsigned long) ; 
 int v4l2_subdev_call (struct v4l2_subdev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct v4l2_mbus_config*) ; 
 int /*<<< orphan*/  video ; 

__attribute__((used)) static int sh_mobile_ceu_try_bus_param(struct soc_camera_device *icd,
				       unsigned char buswidth)
{
	struct v4l2_subdev *sd = soc_camera_to_subdev(icd);
	unsigned long common_flags = CEU_BUS_FLAGS;
	struct v4l2_mbus_config cfg = {.type = V4L2_MBUS_PARALLEL,};
	int ret;

	ret = v4l2_subdev_call(sd, video, g_mbus_config, &cfg);
	if (!ret)
		common_flags = soc_mbus_config_compatible(&cfg,
							  common_flags);
	else if (ret != -ENOIOCTLCMD)
		return ret;

	if (!common_flags || buswidth > 16)
		return -EINVAL;

	return 0;
}