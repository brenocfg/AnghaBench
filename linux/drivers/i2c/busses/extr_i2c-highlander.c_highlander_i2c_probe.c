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
struct resource {int /*<<< orphan*/  start; } ;
struct platform_device {int /*<<< orphan*/  dev; int /*<<< orphan*/  id; int /*<<< orphan*/  name; } ;
struct TYPE_2__ {int /*<<< orphan*/ * parent; } ;
struct i2c_adapter {int /*<<< orphan*/  nr; TYPE_1__ dev; int /*<<< orphan*/ * algo; int /*<<< orphan*/  name; int /*<<< orphan*/  class; int /*<<< orphan*/  owner; } ;
struct highlander_i2c_dev {int /*<<< orphan*/  base; scalar_t__ irq; struct i2c_adapter adapter; int /*<<< orphan*/  last_read_time; int /*<<< orphan*/ * dev; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int ENXIO ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  I2C_CLASS_HWMON ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_notice (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  free_irq (scalar_t__,struct highlander_i2c_dev*) ; 
 int /*<<< orphan*/  highlander_i2c_algo ; 
 int /*<<< orphan*/  highlander_i2c_irq ; 
 int /*<<< orphan*/  highlander_i2c_irq_disable (struct highlander_i2c_dev*) ; 
 int /*<<< orphan*/  highlander_i2c_irq_enable (struct highlander_i2c_dev*) ; 
 int highlander_i2c_reset (struct highlander_i2c_dev*) ; 
 int /*<<< orphan*/  highlander_i2c_setup (struct highlander_i2c_dev*) ; 
 int i2c_add_numbered_adapter (struct i2c_adapter*) ; 
 int /*<<< orphan*/  i2c_set_adapdata (struct i2c_adapter*,struct highlander_i2c_dev*) ; 
 scalar_t__ iic_force_poll ; 
 int /*<<< orphan*/  ioremap_nocache (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  kfree (struct highlander_i2c_dev*) ; 
 struct highlander_i2c_dev* kzalloc (int,int /*<<< orphan*/ ) ; 
 scalar_t__ platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct highlander_i2c_dev*) ; 
 int request_irq (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct highlander_i2c_dev*) ; 
 int /*<<< orphan*/  resource_size (struct resource*) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int highlander_i2c_probe(struct platform_device *pdev)
{
	struct highlander_i2c_dev *dev;
	struct i2c_adapter *adap;
	struct resource *res;
	int ret;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	if (unlikely(!res)) {
		dev_err(&pdev->dev, "no mem resource\n");
		return -ENODEV;
	}

	dev = kzalloc(sizeof(struct highlander_i2c_dev), GFP_KERNEL);
	if (unlikely(!dev))
		return -ENOMEM;

	dev->base = ioremap_nocache(res->start, resource_size(res));
	if (unlikely(!dev->base)) {
		ret = -ENXIO;
		goto err;
	}

	dev->dev = &pdev->dev;
	platform_set_drvdata(pdev, dev);

	dev->irq = platform_get_irq(pdev, 0);
	if (iic_force_poll)
		dev->irq = 0;

	if (dev->irq) {
		ret = request_irq(dev->irq, highlander_i2c_irq, 0,
				  pdev->name, dev);
		if (unlikely(ret))
			goto err_unmap;

		highlander_i2c_irq_enable(dev);
	} else {
		dev_notice(&pdev->dev, "no IRQ, using polling mode\n");
		highlander_i2c_irq_disable(dev);
	}

	dev->last_read_time = jiffies;	/* initial read jiffies */

	highlander_i2c_setup(dev);

	adap = &dev->adapter;
	i2c_set_adapdata(adap, dev);
	adap->owner = THIS_MODULE;
	adap->class = I2C_CLASS_HWMON;
	strlcpy(adap->name, "HL FPGA I2C adapter", sizeof(adap->name));
	adap->algo = &highlander_i2c_algo;
	adap->dev.parent = &pdev->dev;
	adap->nr = pdev->id;

	/*
	 * Reset the adapter
	 */
	ret = highlander_i2c_reset(dev);
	if (unlikely(ret)) {
		dev_err(&pdev->dev, "controller didn't come up\n");
		goto err_free_irq;
	}

	ret = i2c_add_numbered_adapter(adap);
	if (unlikely(ret)) {
		dev_err(&pdev->dev, "failure adding adapter\n");
		goto err_free_irq;
	}

	return 0;

err_free_irq:
	if (dev->irq)
		free_irq(dev->irq, dev);
err_unmap:
	iounmap(dev->base);
err:
	kfree(dev);

	return ret;
}