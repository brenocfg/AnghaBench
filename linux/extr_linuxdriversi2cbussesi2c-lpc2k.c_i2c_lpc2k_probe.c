#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct resource {int dummy; } ;
struct TYPE_13__ {int /*<<< orphan*/  of_node; } ;
struct platform_device {TYPE_4__ dev; } ;
struct TYPE_11__ {int /*<<< orphan*/  of_node; TYPE_4__* parent; } ;
struct TYPE_12__ {TYPE_1__ dev; int /*<<< orphan*/ * algo; int /*<<< orphan*/  name; int /*<<< orphan*/  owner; } ;
struct lpc2k_i2c {scalar_t__ irq; scalar_t__ clk; TYPE_2__ adap; scalar_t__ base; int /*<<< orphan*/  wait; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int I2C_FAST_MODE_DUTY ; 
 int I2C_FAST_MODE_PLUS_DUTY ; 
 int I2C_STD_MODE_DUTY ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (scalar_t__) ; 
 scalar_t__ LPC24XX_I2SCLH ; 
 scalar_t__ LPC24XX_I2SCLL ; 
 int PTR_ERR (scalar_t__) ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  clk_disable_unprepare (scalar_t__) ; 
 int clk_get_rate (scalar_t__) ; 
 int clk_prepare_enable (scalar_t__) ; 
 int /*<<< orphan*/  dev_err (TYPE_4__*,char*) ; 
 int /*<<< orphan*/  dev_info (TYPE_4__*,char*) ; 
 int /*<<< orphan*/  dev_name (TYPE_4__*) ; 
 scalar_t__ devm_clk_get (TYPE_4__*,int /*<<< orphan*/ *) ; 
 scalar_t__ devm_ioremap_resource (TYPE_4__*,struct resource*) ; 
 struct lpc2k_i2c* devm_kzalloc (TYPE_4__*,int,int /*<<< orphan*/ ) ; 
 int devm_request_irq (TYPE_4__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct lpc2k_i2c*) ; 
 int /*<<< orphan*/  disable_irq_nosync (int) ; 
 int i2c_add_adapter (TYPE_2__*) ; 
 int /*<<< orphan*/  i2c_lpc2k_algorithm ; 
 int /*<<< orphan*/  i2c_lpc2k_handler ; 
 int /*<<< orphan*/  i2c_lpc2k_reset (struct lpc2k_i2c*) ; 
 int /*<<< orphan*/  i2c_set_adapdata (TYPE_2__*,struct lpc2k_i2c*) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int of_property_read_u32 (int /*<<< orphan*/ ,char*,int*) ; 
 scalar_t__ platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct lpc2k_i2c*) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int i2c_lpc2k_probe(struct platform_device *pdev)
{
	struct lpc2k_i2c *i2c;
	struct resource *res;
	u32 bus_clk_rate;
	u32 scl_high;
	u32 clkrate;
	int ret;

	i2c = devm_kzalloc(&pdev->dev, sizeof(*i2c), GFP_KERNEL);
	if (!i2c)
		return -ENOMEM;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	i2c->base = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(i2c->base))
		return PTR_ERR(i2c->base);

	i2c->irq = platform_get_irq(pdev, 0);
	if (i2c->irq < 0) {
		dev_err(&pdev->dev, "can't get interrupt resource\n");
		return i2c->irq;
	}

	init_waitqueue_head(&i2c->wait);

	i2c->clk = devm_clk_get(&pdev->dev, NULL);
	if (IS_ERR(i2c->clk)) {
		dev_err(&pdev->dev, "error getting clock\n");
		return PTR_ERR(i2c->clk);
	}

	ret = clk_prepare_enable(i2c->clk);
	if (ret) {
		dev_err(&pdev->dev, "unable to enable clock.\n");
		return ret;
	}

	ret = devm_request_irq(&pdev->dev, i2c->irq, i2c_lpc2k_handler, 0,
			       dev_name(&pdev->dev), i2c);
	if (ret < 0) {
		dev_err(&pdev->dev, "can't request interrupt.\n");
		goto fail_clk;
	}

	disable_irq_nosync(i2c->irq);

	/* Place controller is a known state */
	i2c_lpc2k_reset(i2c);

	ret = of_property_read_u32(pdev->dev.of_node, "clock-frequency",
				   &bus_clk_rate);
	if (ret)
		bus_clk_rate = 100000; /* 100 kHz default clock rate */

	clkrate = clk_get_rate(i2c->clk);
	if (clkrate == 0) {
		dev_err(&pdev->dev, "can't get I2C base clock\n");
		ret = -EINVAL;
		goto fail_clk;
	}

	/* Setup I2C dividers to generate clock with proper duty cycle */
	clkrate = clkrate / bus_clk_rate;
	if (bus_clk_rate <= 100000)
		scl_high = (clkrate * I2C_STD_MODE_DUTY) / 100;
	else if (bus_clk_rate <= 400000)
		scl_high = (clkrate * I2C_FAST_MODE_DUTY) / 100;
	else
		scl_high = (clkrate * I2C_FAST_MODE_PLUS_DUTY) / 100;

	writel(scl_high, i2c->base + LPC24XX_I2SCLH);
	writel(clkrate - scl_high, i2c->base + LPC24XX_I2SCLL);

	platform_set_drvdata(pdev, i2c);

	i2c_set_adapdata(&i2c->adap, i2c);
	i2c->adap.owner = THIS_MODULE;
	strlcpy(i2c->adap.name, "LPC2K I2C adapter", sizeof(i2c->adap.name));
	i2c->adap.algo = &i2c_lpc2k_algorithm;
	i2c->adap.dev.parent = &pdev->dev;
	i2c->adap.dev.of_node = pdev->dev.of_node;

	ret = i2c_add_adapter(&i2c->adap);
	if (ret < 0)
		goto fail_clk;

	dev_info(&pdev->dev, "LPC2K I2C adapter\n");

	return 0;

fail_clk:
	clk_disable_unprepare(i2c->clk);
	return ret;
}