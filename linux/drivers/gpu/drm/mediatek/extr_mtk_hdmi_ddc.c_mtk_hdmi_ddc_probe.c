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
struct resource {int /*<<< orphan*/  end; int /*<<< orphan*/  start; } ;
struct device {int /*<<< orphan*/  of_node; } ;
struct platform_device {struct device dev; } ;
struct TYPE_4__ {struct device* parent; int /*<<< orphan*/  of_node; } ;
struct TYPE_5__ {int retries; TYPE_1__ dev; struct mtk_hdmi_ddc* algo_data; int /*<<< orphan*/ * algo; int /*<<< orphan*/  class; int /*<<< orphan*/  owner; int /*<<< orphan*/  name; } ;
struct mtk_hdmi_ddc {int /*<<< orphan*/  clk; TYPE_2__ adap; int /*<<< orphan*/  regs; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  I2C_CLASS_DDC ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,TYPE_2__*,...) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int /*<<< orphan*/  devm_clk_get (struct device*,char*) ; 
 int /*<<< orphan*/  devm_ioremap_resource (struct device*,struct resource*) ; 
 struct mtk_hdmi_ddc* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int i2c_add_adapter (TYPE_2__*) ; 
 int /*<<< orphan*/  mtk_hdmi_ddc_algorithm ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct mtk_hdmi_ddc*) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int mtk_hdmi_ddc_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct mtk_hdmi_ddc *ddc;
	struct resource *mem;
	int ret;

	ddc = devm_kzalloc(dev, sizeof(struct mtk_hdmi_ddc), GFP_KERNEL);
	if (!ddc)
		return -ENOMEM;

	ddc->clk = devm_clk_get(dev, "ddc-i2c");
	if (IS_ERR(ddc->clk)) {
		dev_err(dev, "get ddc_clk failed: %p ,\n", ddc->clk);
		return PTR_ERR(ddc->clk);
	}

	mem = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	ddc->regs = devm_ioremap_resource(&pdev->dev, mem);
	if (IS_ERR(ddc->regs))
		return PTR_ERR(ddc->regs);

	ret = clk_prepare_enable(ddc->clk);
	if (ret) {
		dev_err(dev, "enable ddc clk failed!\n");
		return ret;
	}

	strlcpy(ddc->adap.name, "mediatek-hdmi-ddc", sizeof(ddc->adap.name));
	ddc->adap.owner = THIS_MODULE;
	ddc->adap.class = I2C_CLASS_DDC;
	ddc->adap.algo = &mtk_hdmi_ddc_algorithm;
	ddc->adap.retries = 3;
	ddc->adap.dev.of_node = dev->of_node;
	ddc->adap.algo_data = ddc;
	ddc->adap.dev.parent = &pdev->dev;

	ret = i2c_add_adapter(&ddc->adap);
	if (ret < 0) {
		dev_err(dev, "failed to add bus to i2c core\n");
		goto err_clk_disable;
	}

	platform_set_drvdata(pdev, ddc);

	dev_dbg(dev, "ddc->adap: %p\n", &ddc->adap);
	dev_dbg(dev, "ddc->clk: %p\n", ddc->clk);
	dev_dbg(dev, "physical adr: %pa, end: %pa\n", &mem->start,
		&mem->end);

	return 0;

err_clk_disable:
	clk_disable_unprepare(ddc->clk);
	return ret;
}