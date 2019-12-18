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
struct video_device {int device_caps; int /*<<< orphan*/ * v4l2_dev; int /*<<< orphan*/  vfl_dir; int /*<<< orphan*/ * ioctl_ops; int /*<<< orphan*/ * fops; int /*<<< orphan*/  (* release ) (struct video_device*) ;int /*<<< orphan*/  name; } ;
struct venus_core {struct device* dev_enc; struct video_device* vdev_enc; int /*<<< orphan*/  v4l2_dev; void* core1_bus_clk; void* core1_clk; } ;
struct device {int /*<<< orphan*/  parent; } ;
struct platform_device {struct device dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int EPROBE_DEFER ; 
 scalar_t__ IS_ERR (void*) ; 
 scalar_t__ IS_V3 (struct venus_core*) ; 
 scalar_t__ IS_V4 (struct venus_core*) ; 
 int PTR_ERR (void*) ; 
 int V4L2_CAP_STREAMING ; 
 int V4L2_CAP_VIDEO_M2M_MPLANE ; 
 int /*<<< orphan*/  VFL_DIR_M2M ; 
 int /*<<< orphan*/  VFL_TYPE_GRABBER ; 
 struct venus_core* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 void* devm_clk_get (struct device*,char*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct venus_core*) ; 
 int /*<<< orphan*/  pm_runtime_enable (struct device*) ; 
 int /*<<< orphan*/  strscpy (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  venc_fops ; 
 int /*<<< orphan*/  venc_ioctl_ops ; 
 struct video_device* video_device_alloc () ; 
 int /*<<< orphan*/  video_device_release (struct video_device*) ; 
 int video_register_device (struct video_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  video_set_drvdata (struct video_device*,struct venus_core*) ; 

__attribute__((used)) static int venc_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct video_device *vdev;
	struct venus_core *core;
	int ret;

	if (!dev->parent)
		return -EPROBE_DEFER;

	core = dev_get_drvdata(dev->parent);
	if (!core)
		return -EPROBE_DEFER;

	if (IS_V3(core) || IS_V4(core)) {
		core->core1_clk = devm_clk_get(dev, "core");
		if (IS_ERR(core->core1_clk))
			return PTR_ERR(core->core1_clk);
	}

	if (IS_V4(core)) {
		core->core1_bus_clk = devm_clk_get(dev, "bus");
		if (IS_ERR(core->core1_bus_clk))
			return PTR_ERR(core->core1_bus_clk);
	}

	platform_set_drvdata(pdev, core);

	vdev = video_device_alloc();
	if (!vdev)
		return -ENOMEM;

	strscpy(vdev->name, "qcom-venus-encoder", sizeof(vdev->name));
	vdev->release = video_device_release;
	vdev->fops = &venc_fops;
	vdev->ioctl_ops = &venc_ioctl_ops;
	vdev->vfl_dir = VFL_DIR_M2M;
	vdev->v4l2_dev = &core->v4l2_dev;
	vdev->device_caps = V4L2_CAP_VIDEO_M2M_MPLANE | V4L2_CAP_STREAMING;

	ret = video_register_device(vdev, VFL_TYPE_GRABBER, -1);
	if (ret)
		goto err_vdev_release;

	core->vdev_enc = vdev;
	core->dev_enc = dev;

	video_set_drvdata(vdev, core);
	pm_runtime_enable(dev);

	return 0;

err_vdev_release:
	video_device_release(vdev);
	return ret;
}