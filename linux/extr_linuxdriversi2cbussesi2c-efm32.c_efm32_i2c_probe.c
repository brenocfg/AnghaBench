#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct resource {int dummy; } ;
struct TYPE_12__ {struct device_node* of_node; } ;
struct platform_device {TYPE_4__ dev; int /*<<< orphan*/  name; } ;
struct TYPE_10__ {struct device_node* of_node; TYPE_4__* parent; } ;
struct TYPE_11__ {TYPE_1__ dev; int /*<<< orphan*/ * algo; int /*<<< orphan*/  owner; int /*<<< orphan*/  name; } ;
struct efm32_i2c_ddata {int irq; int location; int frequency; int /*<<< orphan*/  clk; TYPE_2__ adapter; int /*<<< orphan*/  base; int /*<<< orphan*/  done; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int DIV_ROUND_UP (unsigned long,int) ; 
 int /*<<< orphan*/  DRIVER_NAME ; 
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_CLKDIV ; 
 int REG_CLKDIV_DIV (int) ; 
 int /*<<< orphan*/  REG_CMD ; 
 int REG_CMD_ABORT ; 
 int /*<<< orphan*/  REG_CTRL ; 
 int REG_CTRL_BITO_160PCC ; 
 int REG_CTRL_EN ; 
 int REG_CTRL_GIBITO ; 
 int /*<<< orphan*/  REG_IEN ; 
 int /*<<< orphan*/  REG_IFC ; 
 int REG_IFC__MASK ; 
 int REG_IF_ACK ; 
 int REG_IF_ARBLOST ; 
 int REG_IF_BUSERR ; 
 int REG_IF_NACK ; 
 int REG_IF_RXDATAV ; 
 int REG_IF_TXC ; 
 int /*<<< orphan*/  REG_ROUTE ; 
 int REG_ROUTE_LOCATION (int) ; 
 int REG_ROUTE_SCLPEN ; 
 int REG_ROUTE_SDAPEN ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 unsigned long clk_get_rate (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (TYPE_4__*,char*,unsigned long,...) ; 
 int /*<<< orphan*/  dev_err (TYPE_4__*,char*,...) ; 
 int /*<<< orphan*/  dev_info (TYPE_4__*,char*,...) ; 
 int /*<<< orphan*/  devm_clk_get (TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  devm_ioremap_resource (TYPE_4__*,struct resource*) ; 
 struct efm32_i2c_ddata* devm_kzalloc (TYPE_4__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  efm32_i2c_algo ; 
 int efm32_i2c_get_configured_location (struct efm32_i2c_ddata*) ; 
 int /*<<< orphan*/  efm32_i2c_irq ; 
 int /*<<< orphan*/  efm32_i2c_write32 (struct efm32_i2c_ddata*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  free_irq (int,struct efm32_i2c_ddata*) ; 
 int i2c_add_adapter (TYPE_2__*) ; 
 int /*<<< orphan*/  i2c_set_adapdata (TYPE_2__*,struct efm32_i2c_ddata*) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int of_property_read_u32 (struct device_node*,char*,int*) ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct efm32_i2c_ddata*) ; 
 int request_irq (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct efm32_i2c_ddata*) ; 
 int resource_size (struct resource*) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int efm32_i2c_probe(struct platform_device *pdev)
{
	struct efm32_i2c_ddata *ddata;
	struct resource *res;
	unsigned long rate;
	struct device_node *np = pdev->dev.of_node;
	u32 location, frequency;
	int ret;
	u32 clkdiv;

	if (!np)
		return -EINVAL;

	ddata = devm_kzalloc(&pdev->dev, sizeof(*ddata), GFP_KERNEL);
	if (!ddata)
		return -ENOMEM;
	platform_set_drvdata(pdev, ddata);

	init_completion(&ddata->done);
	strlcpy(ddata->adapter.name, pdev->name, sizeof(ddata->adapter.name));
	ddata->adapter.owner = THIS_MODULE;
	ddata->adapter.algo = &efm32_i2c_algo;
	ddata->adapter.dev.parent = &pdev->dev;
	ddata->adapter.dev.of_node = pdev->dev.of_node;
	i2c_set_adapdata(&ddata->adapter, ddata);

	ddata->clk = devm_clk_get(&pdev->dev, NULL);
	if (IS_ERR(ddata->clk)) {
		ret = PTR_ERR(ddata->clk);
		dev_err(&pdev->dev, "failed to get clock: %d\n", ret);
		return ret;
	}

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	if (!res) {
		dev_err(&pdev->dev, "failed to determine base address\n");
		return -ENODEV;
	}

	if (resource_size(res) < 0x42) {
		dev_err(&pdev->dev, "memory resource too small\n");
		return -EINVAL;
	}

	ddata->base = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(ddata->base))
		return PTR_ERR(ddata->base);

	ret = platform_get_irq(pdev, 0);
	if (ret <= 0) {
		dev_err(&pdev->dev, "failed to get irq (%d)\n", ret);
		if (!ret)
			ret = -EINVAL;
		return ret;
	}

	ddata->irq = ret;

	ret = clk_prepare_enable(ddata->clk);
	if (ret < 0) {
		dev_err(&pdev->dev, "failed to enable clock (%d)\n", ret);
		return ret;
	}


	ret = of_property_read_u32(np, "energymicro,location", &location);

	if (ret)
		/* fall back to wrongly namespaced property */
		ret = of_property_read_u32(np, "efm32,location", &location);

	if (!ret) {
		dev_dbg(&pdev->dev, "using location %u\n", location);
	} else {
		/* default to location configured in hardware */
		location = efm32_i2c_get_configured_location(ddata);

		dev_info(&pdev->dev, "fall back to location %u\n", location);
	}

	ddata->location = location;

	ret = of_property_read_u32(np, "clock-frequency", &frequency);
	if (!ret) {
		dev_dbg(&pdev->dev, "using frequency %u\n", frequency);
	} else {
		frequency = 100000;
		dev_info(&pdev->dev, "defaulting to 100 kHz\n");
	}
	ddata->frequency = frequency;

	rate = clk_get_rate(ddata->clk);
	if (!rate) {
		dev_err(&pdev->dev, "there is no input clock available\n");
		ret = -EINVAL;
		goto err_disable_clk;
	}
	clkdiv = DIV_ROUND_UP(rate, 8 * ddata->frequency) - 1;
	if (clkdiv >= 0x200) {
		dev_err(&pdev->dev,
				"input clock too fast (%lu) to divide down to bus freq (%lu)",
				rate, ddata->frequency);
		ret = -EINVAL;
		goto err_disable_clk;
	}

	dev_dbg(&pdev->dev, "input clock = %lu, bus freq = %lu, clkdiv = %lu\n",
			rate, ddata->frequency, (unsigned long)clkdiv);
	efm32_i2c_write32(ddata, REG_CLKDIV, REG_CLKDIV_DIV(clkdiv));

	efm32_i2c_write32(ddata, REG_ROUTE, REG_ROUTE_SDAPEN |
			REG_ROUTE_SCLPEN |
			REG_ROUTE_LOCATION(ddata->location));

	efm32_i2c_write32(ddata, REG_CTRL, REG_CTRL_EN |
			REG_CTRL_BITO_160PCC | 0 * REG_CTRL_GIBITO);

	efm32_i2c_write32(ddata, REG_IFC, REG_IFC__MASK);
	efm32_i2c_write32(ddata, REG_IEN, REG_IF_TXC | REG_IF_ACK | REG_IF_NACK
			| REG_IF_ARBLOST | REG_IF_BUSERR | REG_IF_RXDATAV);

	/* to make bus idle */
	efm32_i2c_write32(ddata, REG_CMD, REG_CMD_ABORT);

	ret = request_irq(ddata->irq, efm32_i2c_irq, 0, DRIVER_NAME, ddata);
	if (ret < 0) {
		dev_err(&pdev->dev, "failed to request irq (%d)\n", ret);
		goto err_disable_clk;
	}

	ret = i2c_add_adapter(&ddata->adapter);
	if (ret) {
		free_irq(ddata->irq, ddata);

err_disable_clk:
		clk_disable_unprepare(ddata->clk);
	}
	return ret;
}