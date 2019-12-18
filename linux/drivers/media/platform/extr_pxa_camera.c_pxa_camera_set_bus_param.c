#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct v4l2_mbus_config {unsigned long flags; int /*<<< orphan*/  type; } ;
struct pxa_camera_dev {int channels; int platform_flags; TYPE_2__* current_fmt; } ;
struct TYPE_4__ {TYPE_1__* host_fmt; } ;
struct TYPE_3__ {int /*<<< orphan*/  bits_per_sample; int /*<<< orphan*/  fourcc; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOIOCTLCMD ; 
 int PXA_CAMERA_HSP ; 
 int PXA_CAMERA_PCP ; 
 int PXA_CAMERA_VSP ; 
 unsigned long V4L2_MBUS_HSYNC_ACTIVE_HIGH ; 
 unsigned long V4L2_MBUS_HSYNC_ACTIVE_LOW ; 
 int /*<<< orphan*/  V4L2_MBUS_PARALLEL ; 
 unsigned long V4L2_MBUS_PCLK_SAMPLE_FALLING ; 
 unsigned long V4L2_MBUS_PCLK_SAMPLE_RISING ; 
 unsigned long V4L2_MBUS_VSYNC_ACTIVE_HIGH ; 
 unsigned long V4L2_MBUS_VSYNC_ACTIVE_LOW ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,unsigned long,int) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  g_mbus_config ; 
 int /*<<< orphan*/  pcdev_to_dev (struct pxa_camera_dev*) ; 
 int /*<<< orphan*/  pxa_camera_setup_cicr (struct pxa_camera_dev*,unsigned long,int /*<<< orphan*/ ) ; 
 unsigned long pxa_mbus_config_compatible (struct v4l2_mbus_config*,unsigned long) ; 
 int /*<<< orphan*/  s_mbus_config ; 
 int sensor_call (struct pxa_camera_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct v4l2_mbus_config*) ; 
 int test_platform_param (struct pxa_camera_dev*,int /*<<< orphan*/ ,unsigned long*) ; 
 int /*<<< orphan*/  video ; 

__attribute__((used)) static int pxa_camera_set_bus_param(struct pxa_camera_dev *pcdev)
{
	struct v4l2_mbus_config cfg = {.type = V4L2_MBUS_PARALLEL,};
	u32 pixfmt = pcdev->current_fmt->host_fmt->fourcc;
	unsigned long bus_flags, common_flags;
	int ret;

	ret = test_platform_param(pcdev,
				  pcdev->current_fmt->host_fmt->bits_per_sample,
				  &bus_flags);
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
	} else if (ret != -ENOIOCTLCMD) {
		return ret;
	} else {
		common_flags = bus_flags;
	}

	pcdev->channels = 1;

	/* Make choices, based on platform preferences */
	if ((common_flags & V4L2_MBUS_HSYNC_ACTIVE_HIGH) &&
	    (common_flags & V4L2_MBUS_HSYNC_ACTIVE_LOW)) {
		if (pcdev->platform_flags & PXA_CAMERA_HSP)
			common_flags &= ~V4L2_MBUS_HSYNC_ACTIVE_HIGH;
		else
			common_flags &= ~V4L2_MBUS_HSYNC_ACTIVE_LOW;
	}

	if ((common_flags & V4L2_MBUS_VSYNC_ACTIVE_HIGH) &&
	    (common_flags & V4L2_MBUS_VSYNC_ACTIVE_LOW)) {
		if (pcdev->platform_flags & PXA_CAMERA_VSP)
			common_flags &= ~V4L2_MBUS_VSYNC_ACTIVE_HIGH;
		else
			common_flags &= ~V4L2_MBUS_VSYNC_ACTIVE_LOW;
	}

	if ((common_flags & V4L2_MBUS_PCLK_SAMPLE_RISING) &&
	    (common_flags & V4L2_MBUS_PCLK_SAMPLE_FALLING)) {
		if (pcdev->platform_flags & PXA_CAMERA_PCP)
			common_flags &= ~V4L2_MBUS_PCLK_SAMPLE_RISING;
		else
			common_flags &= ~V4L2_MBUS_PCLK_SAMPLE_FALLING;
	}

	cfg.flags = common_flags;
	ret = sensor_call(pcdev, video, s_mbus_config, &cfg);
	if (ret < 0 && ret != -ENOIOCTLCMD) {
		dev_dbg(pcdev_to_dev(pcdev),
			"camera s_mbus_config(0x%lx) returned %d\n",
			common_flags, ret);
		return ret;
	}

	pxa_camera_setup_cicr(pcdev, common_flags, pixfmt);

	return 0;
}