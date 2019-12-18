#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct v4l2_device {int /*<<< orphan*/  name; int /*<<< orphan*/  notify; TYPE_4__* mdev; } ;
struct device {int /*<<< orphan*/  of_node; } ;
struct platform_device {struct device dev; } ;
struct TYPE_7__ {struct device* dev; int /*<<< orphan*/ * ops; int /*<<< orphan*/  model; } ;
struct TYPE_6__ {int /*<<< orphan*/ * ops; } ;
struct fimc_md {int user_subdev_api; scalar_t__ num_sensors; struct v4l2_device v4l2_dev; TYPE_4__ media_dev; TYPE_1__ subdev_notifier; int /*<<< orphan*/  use_isp; struct platform_device* pdev; int /*<<< orphan*/  pipelines; int /*<<< orphan*/  slock; } ;

/* Variables and functions */
 int ENOMEM ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_attr_subdev_conf_mode ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 int device_create_file (struct device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_remove_file (struct device*,int /*<<< orphan*/ *) ; 
 struct fimc_md* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int fimc_md_get_clocks (struct fimc_md*) ; 
 int fimc_md_get_pinctrl (struct fimc_md*) ; 
 int /*<<< orphan*/  fimc_md_is_isp_available (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fimc_md_ops ; 
 int /*<<< orphan*/  fimc_md_put_clocks (struct fimc_md*) ; 
 int fimc_md_register_clk_provider (struct fimc_md*) ; 
 int fimc_md_register_platform_entities (struct fimc_md*,int /*<<< orphan*/ ) ; 
 int fimc_md_register_sensor_entities (struct fimc_md*) ; 
 int /*<<< orphan*/  fimc_md_unregister_clk_provider (struct fimc_md*) ; 
 int /*<<< orphan*/  fimc_md_unregister_entities (struct fimc_md*) ; 
 int /*<<< orphan*/  fimc_sensor_notify ; 
 int /*<<< orphan*/  media_device_cleanup (TYPE_4__*) ; 
 int /*<<< orphan*/  media_device_init (TYPE_4__*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct fimc_md*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strscpy (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  subdev_notifier_ops ; 
 int /*<<< orphan*/  v4l2_async_notifier_cleanup (TYPE_1__*) ; 
 int /*<<< orphan*/  v4l2_async_notifier_init (TYPE_1__*) ; 
 int v4l2_async_notifier_register (struct v4l2_device*,TYPE_1__*) ; 
 int v4l2_device_register (struct device*,struct v4l2_device*) ; 
 int /*<<< orphan*/  v4l2_device_unregister (struct v4l2_device*) ; 
 int /*<<< orphan*/  v4l2_err (struct v4l2_device*,char*,...) ; 

__attribute__((used)) static int fimc_md_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct v4l2_device *v4l2_dev;
	struct fimc_md *fmd;
	int ret;

	fmd = devm_kzalloc(dev, sizeof(*fmd), GFP_KERNEL);
	if (!fmd)
		return -ENOMEM;

	spin_lock_init(&fmd->slock);
	INIT_LIST_HEAD(&fmd->pipelines);
	fmd->pdev = pdev;

	strscpy(fmd->media_dev.model, "SAMSUNG S5P FIMC",
		sizeof(fmd->media_dev.model));
	fmd->media_dev.ops = &fimc_md_ops;
	fmd->media_dev.dev = dev;

	v4l2_dev = &fmd->v4l2_dev;
	v4l2_dev->mdev = &fmd->media_dev;
	v4l2_dev->notify = fimc_sensor_notify;
	strscpy(v4l2_dev->name, "s5p-fimc-md", sizeof(v4l2_dev->name));

	fmd->use_isp = fimc_md_is_isp_available(dev->of_node);
	fmd->user_subdev_api = true;

	media_device_init(&fmd->media_dev);

	ret = v4l2_device_register(dev, &fmd->v4l2_dev);
	if (ret < 0) {
		v4l2_err(v4l2_dev, "Failed to register v4l2_device: %d\n", ret);
		return ret;
	}

	ret = fimc_md_get_clocks(fmd);
	if (ret)
		goto err_md;

	ret = fimc_md_get_pinctrl(fmd);
	if (ret < 0) {
		if (ret != EPROBE_DEFER)
			dev_err(dev, "Failed to get pinctrl: %d\n", ret);
		goto err_clk;
	}

	platform_set_drvdata(pdev, fmd);

	v4l2_async_notifier_init(&fmd->subdev_notifier);

	ret = fimc_md_register_platform_entities(fmd, dev->of_node);
	if (ret)
		goto err_clk;

	ret = fimc_md_register_sensor_entities(fmd);
	if (ret)
		goto err_m_ent;

	ret = device_create_file(&pdev->dev, &dev_attr_subdev_conf_mode);
	if (ret)
		goto err_cleanup;
	/*
	 * FIMC platform devices need to be registered before the sclk_cam
	 * clocks provider, as one of these devices needs to be activated
	 * to enable the clock.
	 */
	ret = fimc_md_register_clk_provider(fmd);
	if (ret < 0) {
		v4l2_err(v4l2_dev, "clock provider registration failed\n");
		goto err_attr;
	}

	if (fmd->num_sensors > 0) {
		fmd->subdev_notifier.ops = &subdev_notifier_ops;
		fmd->num_sensors = 0;

		ret = v4l2_async_notifier_register(&fmd->v4l2_dev,
						&fmd->subdev_notifier);
		if (ret)
			goto err_clk_p;
	}

	return 0;

err_clk_p:
	fimc_md_unregister_clk_provider(fmd);
err_attr:
	device_remove_file(&pdev->dev, &dev_attr_subdev_conf_mode);
err_cleanup:
	v4l2_async_notifier_cleanup(&fmd->subdev_notifier);
err_m_ent:
	fimc_md_unregister_entities(fmd);
err_clk:
	fimc_md_put_clocks(fmd);
err_md:
	media_device_cleanup(&fmd->media_dev);
	v4l2_device_unregister(&fmd->v4l2_dev);
	return ret;
}