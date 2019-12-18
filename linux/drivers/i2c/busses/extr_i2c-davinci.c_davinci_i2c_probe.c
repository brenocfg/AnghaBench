#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_2__ ;
typedef  struct TYPE_24__   TYPE_1__ ;
typedef  struct TYPE_23__   TYPE_12__ ;

/* Type definitions */
typedef  int u32 ;
struct resource {int dummy; } ;
struct TYPE_25__ {scalar_t__ of_node; } ;
struct platform_device {int /*<<< orphan*/  id; TYPE_2__ dev; int /*<<< orphan*/  name; } ;
struct i2c_bus_recovery_info {void* sda_gpiod; void* scl_gpiod; } ;
struct TYPE_24__ {scalar_t__ of_node; TYPE_2__* parent; } ;
struct i2c_adapter {int /*<<< orphan*/  nr; struct i2c_bus_recovery_info* bus_recovery_info; TYPE_1__ dev; int /*<<< orphan*/  timeout; int /*<<< orphan*/ * algo; int /*<<< orphan*/  name; int /*<<< orphan*/  class; int /*<<< orphan*/  owner; } ;
struct davinci_i2c_platform_data {int dummy; } ;
struct davinci_i2c_dev {int irq; TYPE_2__* dev; TYPE_12__* pdata; struct i2c_adapter adapter; void* base; void* clk; int /*<<< orphan*/  cmd_complete; } ;
struct TYPE_23__ {int bus_freq; scalar_t__ gpio_recovery; scalar_t__ has_pfunc; } ;

/* Variables and functions */
 int /*<<< orphan*/  DAVINCI_I2C_PM_TIMEOUT ; 
 int /*<<< orphan*/  DAVINCI_I2C_TIMEOUT ; 
 int ENOMEM ; 
 int ENXIO ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GPIOD_IN ; 
 int /*<<< orphan*/  GPIOD_OUT_HIGH_OPEN_DRAIN ; 
 int /*<<< orphan*/  I2C_CLASS_DEPRECATED ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (void*) ; 
 int PTR_ERR (void*) ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 struct i2c_bus_recovery_info davinci_i2c_gpio_recovery_info ; 
 TYPE_12__ davinci_i2c_platform_data_default ; 
 struct i2c_bus_recovery_info davinci_i2c_scl_recovery_info ; 
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*,...) ; 
 TYPE_12__* dev_get_platdata (TYPE_2__*) ; 
 void* devm_clk_get (TYPE_2__*,int /*<<< orphan*/ *) ; 
 void* devm_gpiod_get (TYPE_2__*,char*,int /*<<< orphan*/ ) ; 
 void* devm_ioremap_resource (TYPE_2__*,struct resource*) ; 
 void* devm_kzalloc (TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 int devm_request_irq (TYPE_2__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct davinci_i2c_dev*) ; 
 int i2c_add_numbered_adapter (struct i2c_adapter*) ; 
 int /*<<< orphan*/  i2c_davinci_algo ; 
 int i2c_davinci_cpufreq_register (struct davinci_i2c_dev*) ; 
 int /*<<< orphan*/  i2c_davinci_init (struct davinci_i2c_dev*) ; 
 int /*<<< orphan*/  i2c_davinci_isr ; 
 int /*<<< orphan*/  i2c_set_adapdata (struct i2c_adapter*,struct davinci_i2c_dev*) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (TYPE_12__*,TYPE_12__*,int) ; 
 scalar_t__ of_property_read_bool (scalar_t__,char*) ; 
 int /*<<< orphan*/  of_property_read_u32 (scalar_t__,char*,int*) ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct davinci_i2c_dev*) ; 
 int /*<<< orphan*/  pm_runtime_disable (TYPE_2__*) ; 
 int /*<<< orphan*/  pm_runtime_dont_use_autosuspend (TYPE_2__*) ; 
 int /*<<< orphan*/  pm_runtime_enable (TYPE_2__*) ; 
 int pm_runtime_get_sync (TYPE_2__*) ; 
 int /*<<< orphan*/  pm_runtime_mark_last_busy (TYPE_2__*) ; 
 int /*<<< orphan*/  pm_runtime_put_autosuspend (TYPE_2__*) ; 
 int /*<<< orphan*/  pm_runtime_put_noidle (TYPE_2__*) ; 
 int /*<<< orphan*/  pm_runtime_put_sync (TYPE_2__*) ; 
 int /*<<< orphan*/  pm_runtime_set_autosuspend_delay (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_use_autosuspend (TYPE_2__*) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int davinci_i2c_probe(struct platform_device *pdev)
{
	struct davinci_i2c_dev *dev;
	struct i2c_adapter *adap;
	struct resource *mem;
	struct i2c_bus_recovery_info *rinfo;
	int r, irq;

	irq = platform_get_irq(pdev, 0);
	if (irq <= 0) {
		if (!irq)
			irq = -ENXIO;
		if (irq != -EPROBE_DEFER)
			dev_err(&pdev->dev,
				"can't get irq resource ret=%d\n", irq);
		return irq;
	}

	dev = devm_kzalloc(&pdev->dev, sizeof(struct davinci_i2c_dev),
			GFP_KERNEL);
	if (!dev) {
		dev_err(&pdev->dev, "Memory allocation failed\n");
		return -ENOMEM;
	}

	init_completion(&dev->cmd_complete);

	dev->dev = &pdev->dev;
	dev->irq = irq;
	dev->pdata = dev_get_platdata(&pdev->dev);
	platform_set_drvdata(pdev, dev);

	if (!dev->pdata && pdev->dev.of_node) {
		u32 prop;

		dev->pdata = devm_kzalloc(&pdev->dev,
			sizeof(struct davinci_i2c_platform_data), GFP_KERNEL);
		if (!dev->pdata)
			return -ENOMEM;

		memcpy(dev->pdata, &davinci_i2c_platform_data_default,
			sizeof(struct davinci_i2c_platform_data));
		if (!of_property_read_u32(pdev->dev.of_node, "clock-frequency",
			&prop))
			dev->pdata->bus_freq = prop / 1000;

		dev->pdata->has_pfunc =
			of_property_read_bool(pdev->dev.of_node,
					      "ti,has-pfunc");
	} else if (!dev->pdata) {
		dev->pdata = &davinci_i2c_platform_data_default;
	}

	dev->clk = devm_clk_get(&pdev->dev, NULL);
	if (IS_ERR(dev->clk))
		return PTR_ERR(dev->clk);

	mem = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	dev->base = devm_ioremap_resource(&pdev->dev, mem);
	if (IS_ERR(dev->base)) {
		return PTR_ERR(dev->base);
	}

	pm_runtime_set_autosuspend_delay(dev->dev,
					 DAVINCI_I2C_PM_TIMEOUT);
	pm_runtime_use_autosuspend(dev->dev);

	pm_runtime_enable(dev->dev);

	r = pm_runtime_get_sync(dev->dev);
	if (r < 0) {
		dev_err(dev->dev, "failed to runtime_get device: %d\n", r);
		pm_runtime_put_noidle(dev->dev);
		return r;
	}

	i2c_davinci_init(dev);

	r = devm_request_irq(&pdev->dev, dev->irq, i2c_davinci_isr, 0,
			pdev->name, dev);
	if (r) {
		dev_err(&pdev->dev, "failure requesting irq %i\n", dev->irq);
		goto err_unuse_clocks;
	}

	r = i2c_davinci_cpufreq_register(dev);
	if (r) {
		dev_err(&pdev->dev, "failed to register cpufreq\n");
		goto err_unuse_clocks;
	}

	adap = &dev->adapter;
	i2c_set_adapdata(adap, dev);
	adap->owner = THIS_MODULE;
	adap->class = I2C_CLASS_DEPRECATED;
	strlcpy(adap->name, "DaVinci I2C adapter", sizeof(adap->name));
	adap->algo = &i2c_davinci_algo;
	adap->dev.parent = &pdev->dev;
	adap->timeout = DAVINCI_I2C_TIMEOUT;
	adap->dev.of_node = pdev->dev.of_node;

	if (dev->pdata->has_pfunc)
		adap->bus_recovery_info = &davinci_i2c_scl_recovery_info;
	else if (dev->pdata->gpio_recovery) {
		rinfo =  &davinci_i2c_gpio_recovery_info;
		adap->bus_recovery_info = rinfo;
		rinfo->scl_gpiod = devm_gpiod_get(&pdev->dev, "scl",
						  GPIOD_OUT_HIGH_OPEN_DRAIN);
		if (IS_ERR(rinfo->scl_gpiod)) {
			r = PTR_ERR(rinfo->scl_gpiod);
			goto err_unuse_clocks;
		}
		rinfo->sda_gpiod = devm_gpiod_get(&pdev->dev, "sda", GPIOD_IN);
		if (IS_ERR(rinfo->sda_gpiod)) {
			r = PTR_ERR(rinfo->sda_gpiod);
			goto err_unuse_clocks;
		}
	}

	adap->nr = pdev->id;
	r = i2c_add_numbered_adapter(adap);
	if (r)
		goto err_unuse_clocks;

	pm_runtime_mark_last_busy(dev->dev);
	pm_runtime_put_autosuspend(dev->dev);

	return 0;

err_unuse_clocks:
	pm_runtime_dont_use_autosuspend(dev->dev);
	pm_runtime_put_sync(dev->dev);
	pm_runtime_disable(dev->dev);

	return r;
}