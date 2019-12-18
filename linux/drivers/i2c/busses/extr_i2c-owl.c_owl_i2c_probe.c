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
struct resource {int dummy; } ;
struct device {int /*<<< orphan*/  of_node; } ;
struct platform_device {int /*<<< orphan*/  name; struct device dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  of_node; struct device* parent; } ;
struct TYPE_5__ {int /*<<< orphan*/  name; TYPE_1__ dev; int /*<<< orphan*/ * quirks; int /*<<< orphan*/  timeout; int /*<<< orphan*/ * algo; int /*<<< orphan*/  owner; } ;
struct owl_i2c_dev {scalar_t__ bus_freq; int /*<<< orphan*/  clk; TYPE_2__ adap; int /*<<< orphan*/  lock; int /*<<< orphan*/  msg_complete; int /*<<< orphan*/  clk_rate; int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 scalar_t__ OWL_I2C_DEF_SPEED_HZ ; 
 scalar_t__ OWL_I2C_MAX_SPEED_HZ ; 
 int /*<<< orphan*/  OWL_I2C_TIMEOUT ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_get_rate (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int /*<<< orphan*/  devm_clk_get (struct device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  devm_ioremap_resource (struct device*,struct resource*) ; 
 struct owl_i2c_dev* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int devm_request_irq (struct device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct owl_i2c_dev*) ; 
 int i2c_add_adapter (TYPE_2__*) ; 
 int /*<<< orphan*/  i2c_set_adapdata (TYPE_2__*,struct owl_i2c_dev*) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 scalar_t__ of_property_read_u32 (int /*<<< orphan*/ ,char*,scalar_t__*) ; 
 int /*<<< orphan*/  owl_i2c_algorithm ; 
 int /*<<< orphan*/  owl_i2c_interrupt ; 
 int /*<<< orphan*/  owl_i2c_quirks ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct owl_i2c_dev*) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,char*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int owl_i2c_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct owl_i2c_dev *i2c_dev;
	struct resource *res;
	int ret, irq;

	i2c_dev = devm_kzalloc(dev, sizeof(*i2c_dev), GFP_KERNEL);
	if (!i2c_dev)
		return -ENOMEM;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	i2c_dev->base = devm_ioremap_resource(dev, res);
	if (IS_ERR(i2c_dev->base))
		return PTR_ERR(i2c_dev->base);

	irq = platform_get_irq(pdev, 0);
	if (irq < 0) {
		dev_err(dev, "failed to get IRQ number\n");
		return irq;
	}

	if (of_property_read_u32(dev->of_node, "clock-frequency",
				 &i2c_dev->bus_freq))
		i2c_dev->bus_freq = OWL_I2C_DEF_SPEED_HZ;

	/* We support only frequencies of 100k and 400k for now */
	if (i2c_dev->bus_freq != OWL_I2C_DEF_SPEED_HZ &&
	    i2c_dev->bus_freq != OWL_I2C_MAX_SPEED_HZ) {
		dev_err(dev, "invalid clock-frequency %d\n", i2c_dev->bus_freq);
		return -EINVAL;
	}

	i2c_dev->clk = devm_clk_get(dev, NULL);
	if (IS_ERR(i2c_dev->clk)) {
		dev_err(dev, "failed to get clock\n");
		return PTR_ERR(i2c_dev->clk);
	}

	ret = clk_prepare_enable(i2c_dev->clk);
	if (ret)
		return ret;

	i2c_dev->clk_rate = clk_get_rate(i2c_dev->clk);
	if (!i2c_dev->clk_rate) {
		dev_err(dev, "input clock rate should not be zero\n");
		ret = -EINVAL;
		goto disable_clk;
	}

	init_completion(&i2c_dev->msg_complete);
	spin_lock_init(&i2c_dev->lock);
	i2c_dev->adap.owner = THIS_MODULE;
	i2c_dev->adap.algo = &owl_i2c_algorithm;
	i2c_dev->adap.timeout = OWL_I2C_TIMEOUT;
	i2c_dev->adap.quirks = &owl_i2c_quirks;
	i2c_dev->adap.dev.parent = dev;
	i2c_dev->adap.dev.of_node = dev->of_node;
	snprintf(i2c_dev->adap.name, sizeof(i2c_dev->adap.name),
		 "%s", "OWL I2C adapter");
	i2c_set_adapdata(&i2c_dev->adap, i2c_dev);

	platform_set_drvdata(pdev, i2c_dev);

	ret = devm_request_irq(dev, irq, owl_i2c_interrupt, 0, pdev->name,
			       i2c_dev);
	if (ret) {
		dev_err(dev, "failed to request irq %d\n", irq);
		goto disable_clk;
	}

	return i2c_add_adapter(&i2c_dev->adap);

disable_clk:
	clk_disable_unprepare(i2c_dev->clk);

	return ret;
}