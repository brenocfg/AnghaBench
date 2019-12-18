#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_4__ {int /*<<< orphan*/  of_node; struct device* parent; } ;
struct TYPE_5__ {int retries; TYPE_1__ dev; int /*<<< orphan*/  nr; struct sprd_i2c* algo_data; int /*<<< orphan*/ * algo; int /*<<< orphan*/  owner; int /*<<< orphan*/  name; } ;
struct sprd_i2c {scalar_t__ irq; int bus_freq; int /*<<< orphan*/  clk; struct device* dev; TYPE_2__ adap; int /*<<< orphan*/  complete; int /*<<< orphan*/  base; } ;
struct device {int /*<<< orphan*/  of_node; } ;
struct platform_device {struct device dev; int /*<<< orphan*/  name; int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int IRQF_NO_SUSPEND ; 
 int IRQF_ONESHOT ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SPRD_I2C_PM_TIMEOUT ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 struct sprd_i2c* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_platform_ioremap_resource (struct platform_device*,int /*<<< orphan*/ ) ; 
 int devm_request_threaded_irq (struct device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct sprd_i2c*) ; 
 int i2c_add_numbered_adapter (TYPE_2__*) ; 
 int /*<<< orphan*/  i2c_set_adapdata (TYPE_2__*,struct sprd_i2c*) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  of_alias_get_id (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  of_property_read_u32 (int /*<<< orphan*/ ,char*,int*) ; 
 scalar_t__ platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct sprd_i2c*) ; 
 int /*<<< orphan*/  pm_runtime_disable (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_enable (struct device*) ; 
 int pm_runtime_get_sync (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_mark_last_busy (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_put_autosuspend (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_put_noidle (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_set_active (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_set_autosuspend_delay (struct device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_use_autosuspend (struct device*) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,char*) ; 
 int /*<<< orphan*/  sprd_i2c_algo ; 
 int sprd_i2c_clk_init (struct sprd_i2c*) ; 
 int /*<<< orphan*/  sprd_i2c_enable (struct sprd_i2c*) ; 
 int /*<<< orphan*/  sprd_i2c_isr ; 
 int /*<<< orphan*/  sprd_i2c_isr_thread ; 

__attribute__((used)) static int sprd_i2c_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct sprd_i2c *i2c_dev;
	u32 prop;
	int ret;

	pdev->id = of_alias_get_id(dev->of_node, "i2c");

	i2c_dev = devm_kzalloc(dev, sizeof(struct sprd_i2c), GFP_KERNEL);
	if (!i2c_dev)
		return -ENOMEM;

	i2c_dev->base = devm_platform_ioremap_resource(pdev, 0);
	if (IS_ERR(i2c_dev->base))
		return PTR_ERR(i2c_dev->base);

	i2c_dev->irq = platform_get_irq(pdev, 0);
	if (i2c_dev->irq < 0) {
		dev_err(&pdev->dev, "failed to get irq resource\n");
		return i2c_dev->irq;
	}

	i2c_set_adapdata(&i2c_dev->adap, i2c_dev);
	init_completion(&i2c_dev->complete);
	snprintf(i2c_dev->adap.name, sizeof(i2c_dev->adap.name),
		 "%s", "sprd-i2c");

	i2c_dev->bus_freq = 100000;
	i2c_dev->adap.owner = THIS_MODULE;
	i2c_dev->dev = dev;
	i2c_dev->adap.retries = 3;
	i2c_dev->adap.algo = &sprd_i2c_algo;
	i2c_dev->adap.algo_data = i2c_dev;
	i2c_dev->adap.dev.parent = dev;
	i2c_dev->adap.nr = pdev->id;
	i2c_dev->adap.dev.of_node = dev->of_node;

	if (!of_property_read_u32(dev->of_node, "clock-frequency", &prop))
		i2c_dev->bus_freq = prop;

	/* We only support 100k and 400k now, otherwise will return error. */
	if (i2c_dev->bus_freq != 100000 && i2c_dev->bus_freq != 400000)
		return -EINVAL;

	ret = sprd_i2c_clk_init(i2c_dev);
	if (ret)
		return ret;

	platform_set_drvdata(pdev, i2c_dev);

	ret = clk_prepare_enable(i2c_dev->clk);
	if (ret)
		return ret;

	sprd_i2c_enable(i2c_dev);

	pm_runtime_set_autosuspend_delay(i2c_dev->dev, SPRD_I2C_PM_TIMEOUT);
	pm_runtime_use_autosuspend(i2c_dev->dev);
	pm_runtime_set_active(i2c_dev->dev);
	pm_runtime_enable(i2c_dev->dev);

	ret = pm_runtime_get_sync(i2c_dev->dev);
	if (ret < 0)
		goto err_rpm_put;

	ret = devm_request_threaded_irq(dev, i2c_dev->irq,
		sprd_i2c_isr, sprd_i2c_isr_thread,
		IRQF_NO_SUSPEND | IRQF_ONESHOT,
		pdev->name, i2c_dev);
	if (ret) {
		dev_err(&pdev->dev, "failed to request irq %d\n", i2c_dev->irq);
		goto err_rpm_put;
	}

	ret = i2c_add_numbered_adapter(&i2c_dev->adap);
	if (ret) {
		dev_err(&pdev->dev, "add adapter failed\n");
		goto err_rpm_put;
	}

	pm_runtime_mark_last_busy(i2c_dev->dev);
	pm_runtime_put_autosuspend(i2c_dev->dev);
	return 0;

err_rpm_put:
	pm_runtime_put_noidle(i2c_dev->dev);
	pm_runtime_disable(i2c_dev->dev);
	clk_disable_unprepare(i2c_dev->clk);
	return ret;
}