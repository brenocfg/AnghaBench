#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct resource {int /*<<< orphan*/  start; } ;
struct TYPE_9__ {int /*<<< orphan*/  of_node; } ;
struct platform_device {TYPE_2__ dev; } ;
struct TYPE_8__ {int /*<<< orphan*/  of_node; TYPE_2__* parent; } ;
struct i2c_adapter {int /*<<< orphan*/ * quirks; TYPE_1__ dev; int /*<<< orphan*/ * algo; int /*<<< orphan*/  name; int /*<<< orphan*/  class; int /*<<< orphan*/  owner; } ;
struct bcm2835_i2c_dev {int bus_clk_rate; int /*<<< orphan*/  irq; struct i2c_adapter adapter; int /*<<< orphan*/  clk; int /*<<< orphan*/  regs; int /*<<< orphan*/  completion; TYPE_2__* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BCM2835_I2C_C ; 
 int ENODEV ; 
 int ENOMEM ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  I2C_CLASS_DEPRECATED ; 
 int /*<<< orphan*/  IORESOURCE_IRQ ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  bcm2835_i2c_algo ; 
 int /*<<< orphan*/  bcm2835_i2c_isr ; 
 int /*<<< orphan*/  bcm2835_i2c_quirks ; 
 int /*<<< orphan*/  bcm2835_i2c_writel (struct bcm2835_i2c_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  dev_name (TYPE_2__*) ; 
 int /*<<< orphan*/  dev_warn (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  devm_clk_get (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  devm_ioremap_resource (TYPE_2__*,struct resource*) ; 
 struct bcm2835_i2c_dev* devm_kzalloc (TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct bcm2835_i2c_dev*) ; 
 int i2c_add_adapter (struct i2c_adapter*) ; 
 int /*<<< orphan*/  i2c_set_adapdata (struct i2c_adapter*,struct bcm2835_i2c_dev*) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int of_property_read_u32 (int /*<<< orphan*/ ,char*,int*) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct bcm2835_i2c_dev*) ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct bcm2835_i2c_dev*) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int bcm2835_i2c_probe(struct platform_device *pdev)
{
	struct bcm2835_i2c_dev *i2c_dev;
	struct resource *mem, *irq;
	int ret;
	struct i2c_adapter *adap;

	i2c_dev = devm_kzalloc(&pdev->dev, sizeof(*i2c_dev), GFP_KERNEL);
	if (!i2c_dev)
		return -ENOMEM;
	platform_set_drvdata(pdev, i2c_dev);
	i2c_dev->dev = &pdev->dev;
	init_completion(&i2c_dev->completion);

	mem = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	i2c_dev->regs = devm_ioremap_resource(&pdev->dev, mem);
	if (IS_ERR(i2c_dev->regs))
		return PTR_ERR(i2c_dev->regs);

	i2c_dev->clk = devm_clk_get(&pdev->dev, NULL);
	if (IS_ERR(i2c_dev->clk)) {
		if (PTR_ERR(i2c_dev->clk) != -EPROBE_DEFER)
			dev_err(&pdev->dev, "Could not get clock\n");
		return PTR_ERR(i2c_dev->clk);
	}

	ret = of_property_read_u32(pdev->dev.of_node, "clock-frequency",
				   &i2c_dev->bus_clk_rate);
	if (ret < 0) {
		dev_warn(&pdev->dev,
			 "Could not read clock-frequency property\n");
		i2c_dev->bus_clk_rate = 100000;
	}

	irq = platform_get_resource(pdev, IORESOURCE_IRQ, 0);
	if (!irq) {
		dev_err(&pdev->dev, "No IRQ resource\n");
		return -ENODEV;
	}
	i2c_dev->irq = irq->start;

	ret = request_irq(i2c_dev->irq, bcm2835_i2c_isr, IRQF_SHARED,
			  dev_name(&pdev->dev), i2c_dev);
	if (ret) {
		dev_err(&pdev->dev, "Could not request IRQ\n");
		return -ENODEV;
	}

	adap = &i2c_dev->adapter;
	i2c_set_adapdata(adap, i2c_dev);
	adap->owner = THIS_MODULE;
	adap->class = I2C_CLASS_DEPRECATED;
	strlcpy(adap->name, "bcm2835 I2C adapter", sizeof(adap->name));
	adap->algo = &bcm2835_i2c_algo;
	adap->dev.parent = &pdev->dev;
	adap->dev.of_node = pdev->dev.of_node;
	adap->quirks = &bcm2835_i2c_quirks;

	bcm2835_i2c_writel(i2c_dev, BCM2835_I2C_C, 0);

	ret = i2c_add_adapter(adap);
	if (ret)
		free_irq(i2c_dev->irq, i2c_dev);

	return ret;
}