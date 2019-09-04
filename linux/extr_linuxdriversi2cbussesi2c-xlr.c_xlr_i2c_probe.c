#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;
typedef  struct TYPE_11__   TYPE_10__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_11__ {int /*<<< orphan*/  of_node; TYPE_2__* parent; } ;
struct TYPE_14__ {TYPE_10__ dev; int /*<<< orphan*/  name; int /*<<< orphan*/  class; int /*<<< orphan*/  nr; int /*<<< orphan*/ * quirks; int /*<<< orphan*/ * algo; struct xlr_i2c_private* algo_data; int /*<<< orphan*/  owner; } ;
struct xlr_i2c_private {int irq; TYPE_3__ adap; struct clk* clk; struct clk* iobase; int /*<<< orphan*/  wait; TYPE_1__* cfg; } ;
struct resource {int dummy; } ;
struct TYPE_13__ {int /*<<< orphan*/  of_node; } ;
struct platform_device {int /*<<< orphan*/  id; TYPE_2__ dev; } ;
struct of_device_id {TYPE_1__* data; } ;
struct clk {int dummy; } ;
struct TYPE_12__ {int flags; } ;

/* Variables and functions */
 unsigned long DIV_ROUND_UP (unsigned long,int) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  I2C_CLASS_HWMON ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 scalar_t__ IS_ERR (struct clk*) ; 
 int PTR_ERR (struct clk*) ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  XLR_I2C_CLKDIV ; 
 int XLR_I2C_FLAG_IRQ ; 
 int /*<<< orphan*/  XLR_I2C_INT_EN ; 
 int /*<<< orphan*/  XLR_I2C_INT_STAT ; 
 int /*<<< orphan*/  clk_disable (struct clk*) ; 
 unsigned long clk_get_rate (struct clk*) ; 
 int clk_prepare_enable (struct clk*) ; 
 int /*<<< orphan*/  dev_info (TYPE_10__*,char*) ; 
 int /*<<< orphan*/  dev_name (TYPE_2__*) ; 
 struct clk* devm_clk_get (TYPE_2__*,int /*<<< orphan*/ *) ; 
 struct clk* devm_ioremap_resource (TYPE_2__*,struct resource*) ; 
 struct xlr_i2c_private* devm_kzalloc (TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 int devm_request_irq (TYPE_2__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct xlr_i2c_private*) ; 
 int i2c_add_numbered_adapter (TYPE_3__*) ; 
 int /*<<< orphan*/  i2c_set_adapdata (TYPE_3__*,struct xlr_i2c_private*) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 struct of_device_id* of_match_device (int /*<<< orphan*/ ,TYPE_2__*) ; 
 scalar_t__ of_property_read_u32 (int /*<<< orphan*/ ,char*,int*) ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct xlr_i2c_private*) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  xlr_i2c_algo ; 
 TYPE_1__ xlr_i2c_config_default ; 
 int /*<<< orphan*/  xlr_i2c_dt_ids ; 
 int /*<<< orphan*/  xlr_i2c_irq ; 
 int /*<<< orphan*/  xlr_i2c_quirks ; 
 int /*<<< orphan*/  xlr_i2c_wreg (struct clk*,int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static int xlr_i2c_probe(struct platform_device *pdev)
{
	const struct of_device_id *match;
	struct xlr_i2c_private  *priv;
	struct resource *res;
	struct clk *clk;
	unsigned long clk_rate;
	unsigned long clk_div;
	u32 busfreq;
	int irq;
	int ret;

	priv = devm_kzalloc(&pdev->dev, sizeof(*priv), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	match = of_match_device(xlr_i2c_dt_ids, &pdev->dev);
	if (match)
		priv->cfg = match->data;
	else
		priv->cfg = &xlr_i2c_config_default;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	priv->iobase = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(priv->iobase))
		return PTR_ERR(priv->iobase);

	irq = platform_get_irq(pdev, 0);

	if (irq > 0 && (priv->cfg->flags & XLR_I2C_FLAG_IRQ)) {
		priv->irq = irq;

		xlr_i2c_wreg(priv->iobase, XLR_I2C_INT_EN, 0);
		xlr_i2c_wreg(priv->iobase, XLR_I2C_INT_STAT, 0xf);

		ret = devm_request_irq(&pdev->dev, priv->irq, xlr_i2c_irq,
					IRQF_SHARED, dev_name(&pdev->dev),
					priv);
		if (ret)
			return ret;

		init_waitqueue_head(&priv->wait);
	}

	if (of_property_read_u32(pdev->dev.of_node, "clock-frequency",
				 &busfreq))
		busfreq = 100000;

	clk = devm_clk_get(&pdev->dev, NULL);
	if (!IS_ERR(clk)) {
		ret = clk_prepare_enable(clk);
		if (ret)
			return ret;

		clk_rate = clk_get_rate(clk);
		clk_div = DIV_ROUND_UP(clk_rate, 2 * busfreq);
		xlr_i2c_wreg(priv->iobase, XLR_I2C_CLKDIV, clk_div);

		clk_disable(clk);
		priv->clk = clk;
	}

	priv->adap.dev.parent = &pdev->dev;
	priv->adap.dev.of_node	= pdev->dev.of_node;
	priv->adap.owner	= THIS_MODULE;
	priv->adap.algo_data	= priv;
	priv->adap.algo		= &xlr_i2c_algo;
	priv->adap.quirks	= &xlr_i2c_quirks;
	priv->adap.nr		= pdev->id;
	priv->adap.class	= I2C_CLASS_HWMON;
	snprintf(priv->adap.name, sizeof(priv->adap.name), "xlr-i2c");

	i2c_set_adapdata(&priv->adap, priv);
	ret = i2c_add_numbered_adapter(&priv->adap);
	if (ret < 0)
		return ret;

	platform_set_drvdata(pdev, priv);
	dev_info(&priv->adap.dev, "Added I2C Bus.\n");
	return 0;
}