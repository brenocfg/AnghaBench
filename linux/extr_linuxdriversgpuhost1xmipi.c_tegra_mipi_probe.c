#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct tegra_mipi {int /*<<< orphan*/  clk; int /*<<< orphan*/  lock; int /*<<< orphan*/  regs; TYPE_1__* dev; int /*<<< orphan*/  soc; } ;
struct resource {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  of_node; } ;
struct platform_device {TYPE_1__ dev; } ;
struct of_device_id {int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int clk_prepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  devm_clk_get (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  devm_ioremap_resource (TYPE_1__*,struct resource*) ; 
 struct tegra_mipi* devm_kzalloc (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 struct of_device_id* of_match_node (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct tegra_mipi*) ; 
 int /*<<< orphan*/  tegra_mipi_of_match ; 

__attribute__((used)) static int tegra_mipi_probe(struct platform_device *pdev)
{
	const struct of_device_id *match;
	struct tegra_mipi *mipi;
	struct resource *res;
	int err;

	match = of_match_node(tegra_mipi_of_match, pdev->dev.of_node);
	if (!match)
		return -ENODEV;

	mipi = devm_kzalloc(&pdev->dev, sizeof(*mipi), GFP_KERNEL);
	if (!mipi)
		return -ENOMEM;

	mipi->soc = match->data;
	mipi->dev = &pdev->dev;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	mipi->regs = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(mipi->regs))
		return PTR_ERR(mipi->regs);

	mutex_init(&mipi->lock);

	mipi->clk = devm_clk_get(&pdev->dev, NULL);
	if (IS_ERR(mipi->clk)) {
		dev_err(&pdev->dev, "failed to get clock\n");
		return PTR_ERR(mipi->clk);
	}

	err = clk_prepare(mipi->clk);
	if (err < 0)
		return err;

	platform_set_drvdata(pdev, mipi);

	return 0;
}