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
struct TYPE_6__ {unsigned long spi_master_freq; int /*<<< orphan*/ * base; int /*<<< orphan*/  phys_base; } ;
struct dfsdm_priv {unsigned long spi_clk_out_div; TYPE_1__ dfsdm; int /*<<< orphan*/ * clk; int /*<<< orphan*/ * aclk; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 unsigned long clk_get_rate (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*,...) ; 
 int /*<<< orphan*/  dev_warn (TYPE_2__*,char*,...) ; 
 void* devm_clk_get (TYPE_2__*,char*) ; 
 int /*<<< orphan*/ * devm_ioremap_resource (TYPE_2__*,struct resource*) ; 
 unsigned long div_u64_rem (unsigned long,unsigned int,unsigned int*) ; 
 int of_property_read_u32 (struct device_node*,char*,unsigned int*) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int stm32_dfsdm_parse_of(struct platform_device *pdev,
				struct dfsdm_priv *priv)
{
	struct device_node *node = pdev->dev.of_node;
	struct resource *res;
	unsigned long clk_freq, divider;
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
	if (IS_ERR(priv->dfsdm.base))
		return PTR_ERR(priv->dfsdm.base);

	/*
	 * "dfsdm" clock is mandatory for DFSDM peripheral clocking.
	 * "dfsdm" or "audio" clocks can be used as source clock for
	 * the SPI clock out signal and internal processing, depending
	 * on use case.
	 */
	priv->clk = devm_clk_get(&pdev->dev, "dfsdm");
	if (IS_ERR(priv->clk)) {
		ret = PTR_ERR(priv->clk);
		if (ret != -EPROBE_DEFER)
			dev_err(&pdev->dev, "Failed to get clock (%d)\n", ret);
		return ret;
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

	divider = div_u64_rem(clk_freq, spi_freq, &rem);
	/* Round up divider when ckout isn't precise, not to exceed spi_freq */
	if (rem)
		divider++;

	/* programmable divider is in range of [2:256] */
	if (divider < 2 || divider > 256) {
		dev_err(&pdev->dev, "spi-max-frequency not achievable\n");
		return -EINVAL;
	}

	/* SPI clock output divider is: divider = CKOUTDIV + 1 */
	priv->spi_clk_out_div = divider - 1;
	priv->dfsdm.spi_master_freq = clk_freq / (priv->spi_clk_out_div + 1);

	if (rem) {
		dev_warn(&pdev->dev, "SPI clock not accurate\n");
		dev_warn(&pdev->dev, "%ld = %d * %d + %d\n",
			 clk_freq, spi_freq, priv->spi_clk_out_div + 1, rem);
	}

	return 0;
}