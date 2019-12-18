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
struct device {int dummy; } ;
struct platform_device {struct device dev; } ;
struct delta_dev {int /*<<< orphan*/  v4l2_dev; int /*<<< orphan*/  work_queue; TYPE_1__* vdev; struct device* dev; int /*<<< orphan*/ * clk_flash_promip; int /*<<< orphan*/ * clk_st231; int /*<<< orphan*/ * clk_delta; int /*<<< orphan*/  lock; struct platform_device* pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  num; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  DELTA_HW_AUTOSUSPEND_DELAY_MS ; 
 int /*<<< orphan*/  DELTA_NAME ; 
 int /*<<< orphan*/  DELTA_PREFIX ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  create_workqueue (int /*<<< orphan*/ ) ; 
 int delta_ipc_init (struct delta_dev*) ; 
 int delta_register_device (struct delta_dev*) ; 
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* devm_clk_get (struct device*,char*) ; 
 struct delta_dev* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct delta_dev*) ; 
 int /*<<< orphan*/  pm_runtime_enable (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_set_autosuspend_delay (struct device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_set_suspended (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_use_autosuspend (struct device*) ; 
 int /*<<< orphan*/  register_decoders (struct delta_dev*) ; 
 int /*<<< orphan*/  register_formats (struct delta_dev*) ; 
 int v4l2_device_register (struct device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_device_unregister (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int delta_probe(struct platform_device *pdev)
{
	struct delta_dev *delta;
	struct device *dev = &pdev->dev;
	int ret;

	delta = devm_kzalloc(dev, sizeof(*delta), GFP_KERNEL);
	if (!delta) {
		ret = -ENOMEM;
		goto err;
	}

	delta->dev = dev;
	delta->pdev = pdev;
	platform_set_drvdata(pdev, delta);

	mutex_init(&delta->lock);

	/* get clock resources */
	delta->clk_delta = devm_clk_get(dev, "delta");
	if (IS_ERR(delta->clk_delta)) {
		dev_dbg(dev, "%s can't get delta clock\n", DELTA_PREFIX);
		delta->clk_delta = NULL;
	}

	delta->clk_st231 = devm_clk_get(dev, "delta-st231");
	if (IS_ERR(delta->clk_st231)) {
		dev_dbg(dev, "%s can't get delta-st231 clock\n", DELTA_PREFIX);
		delta->clk_st231 = NULL;
	}

	delta->clk_flash_promip = devm_clk_get(dev, "delta-flash-promip");
	if (IS_ERR(delta->clk_flash_promip)) {
		dev_dbg(dev, "%s can't get delta-flash-promip clock\n",
			DELTA_PREFIX);
		delta->clk_flash_promip = NULL;
	}

	/* init pm_runtime used for power management */
	pm_runtime_set_autosuspend_delay(dev, DELTA_HW_AUTOSUSPEND_DELAY_MS);
	pm_runtime_use_autosuspend(dev);
	pm_runtime_set_suspended(dev);
	pm_runtime_enable(dev);

	/* init firmware ipc channel */
	ret = delta_ipc_init(delta);
	if (ret) {
		dev_err(delta->dev, "%s failed to initialize firmware ipc channel\n",
			DELTA_PREFIX);
		goto err;
	}

	/* register all available decoders */
	register_decoders(delta);

	/* register all supported formats */
	register_formats(delta);

	/* register on V4L2 */
	ret = v4l2_device_register(dev, &delta->v4l2_dev);
	if (ret) {
		dev_err(delta->dev, "%s failed to register V4L2 device\n",
			DELTA_PREFIX);
		goto err;
	}

	delta->work_queue = create_workqueue(DELTA_NAME);
	if (!delta->work_queue) {
		dev_err(delta->dev, "%s failed to allocate work queue\n",
			DELTA_PREFIX);
		ret = -ENOMEM;
		goto err_v4l2;
	}

	/* register device */
	ret = delta_register_device(delta);
	if (ret)
		goto err_work_queue;

	dev_info(dev, "%s %s registered as /dev/video%d\n",
		 DELTA_PREFIX, delta->vdev->name, delta->vdev->num);

	return 0;

err_work_queue:
	destroy_workqueue(delta->work_queue);
err_v4l2:
	v4l2_device_unregister(&delta->v4l2_dev);
err:
	return ret;
}