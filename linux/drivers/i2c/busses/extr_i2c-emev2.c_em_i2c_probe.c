#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct resource {int dummy; } ;
struct TYPE_12__ {int /*<<< orphan*/  of_node; } ;
struct platform_device {TYPE_5__ dev; } ;
struct TYPE_10__ {int /*<<< orphan*/  of_node; TYPE_5__* parent; } ;
struct TYPE_11__ {int retries; int /*<<< orphan*/  nr; TYPE_1__ dev; int /*<<< orphan*/  owner; int /*<<< orphan*/ * algo; int /*<<< orphan*/  timeout; int /*<<< orphan*/  name; } ;
struct em_i2c_device {int /*<<< orphan*/  sclk; int /*<<< orphan*/  irq; TYPE_2__ adap; int /*<<< orphan*/  msg_done; int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_info (TYPE_5__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_clk_get (TYPE_5__*,char*) ; 
 int /*<<< orphan*/  devm_ioremap_resource (TYPE_5__*,struct resource*) ; 
 struct em_i2c_device* devm_kzalloc (TYPE_5__*,int,int /*<<< orphan*/ ) ; 
 int devm_request_irq (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct em_i2c_device*) ; 
 int /*<<< orphan*/  em_i2c_algo ; 
 int /*<<< orphan*/  em_i2c_irq_handler ; 
 int /*<<< orphan*/  em_i2c_reset (TYPE_2__*) ; 
 int i2c_add_adapter (TYPE_2__*) ; 
 int /*<<< orphan*/  i2c_set_adapdata (TYPE_2__*,struct em_i2c_device*) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct em_i2c_device*) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int em_i2c_probe(struct platform_device *pdev)
{
	struct em_i2c_device *priv;
	struct resource *r;
	int ret;

	priv = devm_kzalloc(&pdev->dev, sizeof(*priv), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	r = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	priv->base = devm_ioremap_resource(&pdev->dev, r);
	if (IS_ERR(priv->base))
		return PTR_ERR(priv->base);

	strlcpy(priv->adap.name, "EMEV2 I2C", sizeof(priv->adap.name));

	priv->sclk = devm_clk_get(&pdev->dev, "sclk");
	if (IS_ERR(priv->sclk))
		return PTR_ERR(priv->sclk);

	ret = clk_prepare_enable(priv->sclk);
	if (ret)
		return ret;

	priv->adap.timeout = msecs_to_jiffies(100);
	priv->adap.retries = 5;
	priv->adap.dev.parent = &pdev->dev;
	priv->adap.algo = &em_i2c_algo;
	priv->adap.owner = THIS_MODULE;
	priv->adap.dev.of_node = pdev->dev.of_node;

	init_completion(&priv->msg_done);

	platform_set_drvdata(pdev, priv);
	i2c_set_adapdata(&priv->adap, priv);

	em_i2c_reset(&priv->adap);

	priv->irq = platform_get_irq(pdev, 0);
	ret = devm_request_irq(&pdev->dev, priv->irq, em_i2c_irq_handler, 0,
				"em_i2c", priv);
	if (ret)
		goto err_clk;

	ret = i2c_add_adapter(&priv->adap);

	if (ret)
		goto err_clk;

	dev_info(&pdev->dev, "Added i2c controller %d, irq %d\n", priv->adap.nr,
		 priv->irq);

	return 0;

err_clk:
	clk_disable_unprepare(priv->sclk);
	return ret;
}