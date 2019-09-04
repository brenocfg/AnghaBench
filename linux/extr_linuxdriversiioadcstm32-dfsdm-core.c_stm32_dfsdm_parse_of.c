#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct resource {int /*<<< orphan*/  start; } ;
struct TYPE_7__ {struct device_node* of_node; } ;
struct platform_device {TYPE_2__ dev; } ;
struct TYPE_6__ {unsigned int spi_master_freq; int /*<<< orphan*/  base; int /*<<< orphan*/  phys_base; } ;
struct dfsdm_priv {scalar_t__ spi_clk_out_div; TYPE_1__ dfsdm; int /*<<< orphan*/ * clk; int /*<<< orphan*/ * aclk; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 unsigned long clk_get_rate (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  dev_warn (TYPE_2__*,char*,...) ; 
 void* devm_clk_get (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  devm_ioremap_resource (TYPE_2__*,struct resource*) ; 
 scalar_t__ div_u64_rem (unsigned long,unsigned int,unsigned int*) ; 
 int of_property_read_u32 (struct device_node*,char*,unsigned int*) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int stm32_dfsdm_parse_of(struct platform_device *pdev,
				struct dfsdm_priv *priv)
{
	struct device_node *node = pdev->dev.of_node;
	struct resource *res;
	unsigned long clk_freq;
	unsigned int spi_freq, rem;
	int ret;

	if (!node)
		return -EINVAL;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	if (!res) {
		dev_err(&pdev->dev, "Failed to get memory resource\n");
		return -ENODEV;
	}
	priv->dfsdm.phys_base = res->start;
	priv->dfsdm.base = devm_ioremap_resource(&pdev->dev, res);

	/*
	 * "dfsdm" clock is mandatory for DFSDM peripheral clocking.
	 * "dfsdm" or "audio" clocks can be used as source clock for
	 * the SPI clock out signal and internal processing, depending
	 * on use case.
	 */
	priv->clk = devm_clk_get(&pdev->dev, "dfsdm");
	if (IS_ERR(priv->clk)) {
		dev_err(&pdev->dev, "No stm32_dfsdm_clk clock found\n");
		return -EINVAL;
	}

	priv->aclk = devm_clk_get(&pdev->dev, "audio");
	if (IS_ERR(priv->aclk))
		priv->aclk = NULL;

	if (priv->aclk)
		clk_freq = clk_get_rate(priv->aclk);
	else
		clk_freq = clk_get_rate(priv->clk);

	/* SPI clock out frequency */
	ret = of_property_read_u32(pdev->dev.of_node, "spi-max-frequency",
				   &spi_freq);
	if (ret < 0) {
		/* No SPI master mode */
		return 0;
	}

	priv->spi_clk_out_div = div_u64_rem(clk_freq, spi_freq, &rem) - 1;
	if (!priv->spi_clk_out_div) {
		/* spi_clk_out_div == 0 means ckout is OFF */
		dev_err(&pdev->dev, "spi-max-frequency not achievable\n");
		return -EINVAL;
	}
	priv->dfsdm.spi_master_freq = spi_freq;

	if (rem) {
		dev_warn(&pdev->dev, "SPI clock not accurate\n");
		dev_warn(&pdev->dev, "%ld = %d * %d + %d\n",
			 clk_freq, spi_freq, priv->spi_clk_out_div + 1, rem);
	}

	return 0;
}