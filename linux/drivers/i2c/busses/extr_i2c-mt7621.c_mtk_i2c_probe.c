#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct resource {int dummy; } ;
struct TYPE_10__ {int /*<<< orphan*/  of_node; } ;
struct platform_device {TYPE_2__ dev; } ;
struct TYPE_9__ {int /*<<< orphan*/  of_node; TYPE_2__* parent; } ;
struct i2c_adapter {int retries; int /*<<< orphan*/  name; TYPE_1__ dev; int /*<<< orphan*/ * algo; int /*<<< orphan*/  owner; } ;
struct mtk_i2c {int bus_freq; struct i2c_adapter adap; TYPE_2__* dev; int /*<<< orphan*/  clk; int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  dev_info (TYPE_2__*,char*,int) ; 
 int /*<<< orphan*/  dev_name (TYPE_2__*) ; 
 int /*<<< orphan*/  dev_warn (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  devm_clk_get (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  devm_ioremap_resource (TYPE_2__*,struct resource*) ; 
 struct mtk_i2c* devm_kzalloc (TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 int i2c_add_adapter (struct i2c_adapter*) ; 
 int /*<<< orphan*/  i2c_set_adapdata (struct i2c_adapter*,struct mtk_i2c*) ; 
 int /*<<< orphan*/  mtk_i2c_algo ; 
 int /*<<< orphan*/  mtk_i2c_init (struct mtk_i2c*) ; 
 scalar_t__ of_property_read_u32 (int /*<<< orphan*/ ,char*,int*) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct mtk_i2c*) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int mtk_i2c_probe(struct platform_device *pdev)
{
	struct resource *res;
	struct mtk_i2c *i2c;
	struct i2c_adapter *adap;
	int ret;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);

	i2c = devm_kzalloc(&pdev->dev, sizeof(struct mtk_i2c), GFP_KERNEL);
	if (!i2c)
		return -ENOMEM;

	i2c->base = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(i2c->base))
		return PTR_ERR(i2c->base);

	i2c->clk = devm_clk_get(&pdev->dev, NULL);
	if (IS_ERR(i2c->clk)) {
		dev_err(&pdev->dev, "no clock defined\n");
		return PTR_ERR(i2c->clk);
	}
	ret = clk_prepare_enable(i2c->clk);
	if (ret) {
		dev_err(&pdev->dev, "Unable to enable clock\n");
		return ret;
	}

	i2c->dev = &pdev->dev;

	if (of_property_read_u32(pdev->dev.of_node, "clock-frequency",
				 &i2c->bus_freq))
		i2c->bus_freq = 100000;

	if (i2c->bus_freq == 0) {
		dev_warn(i2c->dev, "clock-frequency 0 not supported\n");
		return -EINVAL;
	}

	adap = &i2c->adap;
	adap->owner = THIS_MODULE;
	adap->algo = &mtk_i2c_algo;
	adap->retries = 3;
	adap->dev.parent = &pdev->dev;
	i2c_set_adapdata(adap, i2c);
	adap->dev.of_node = pdev->dev.of_node;
	strlcpy(adap->name, dev_name(&pdev->dev), sizeof(adap->name));

	platform_set_drvdata(pdev, i2c);

	mtk_i2c_init(i2c);

	ret = i2c_add_adapter(adap);
	if (ret < 0)
		return ret;

	dev_info(&pdev->dev, "clock %u kHz\n", i2c->bus_freq / 1000);

	return ret;
}