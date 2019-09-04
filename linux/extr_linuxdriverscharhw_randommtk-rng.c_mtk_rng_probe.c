#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct resource {int dummy; } ;
struct platform_device {int /*<<< orphan*/  dev; int /*<<< orphan*/  name; } ;
struct TYPE_2__ {unsigned long priv; int quality; int /*<<< orphan*/  read; int /*<<< orphan*/  cleanup; int /*<<< orphan*/  init; int /*<<< orphan*/  name; } ;
struct mtk_rng {TYPE_1__ rng; int /*<<< orphan*/  base; int /*<<< orphan*/  clk; } ;

/* Variables and functions */
 int ENOMEM ; 
 int ENXIO ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RNG_AUTOSUSPEND_TIMEOUT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_set_drvdata (int /*<<< orphan*/ *,struct mtk_rng*) ; 
 int /*<<< orphan*/  devm_clk_get (int /*<<< orphan*/ *,char*) ; 
 int devm_hwrng_register (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  devm_ioremap_resource (int /*<<< orphan*/ *,struct resource*) ; 
 struct mtk_rng* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtk_rng_cleanup ; 
 int /*<<< orphan*/  mtk_rng_init ; 
 int /*<<< orphan*/  mtk_rng_read ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_enable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_set_autosuspend_delay (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_use_autosuspend (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mtk_rng_probe(struct platform_device *pdev)
{
	struct resource *res;
	int ret;
	struct mtk_rng *priv;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	if (!res) {
		dev_err(&pdev->dev, "no iomem resource\n");
		return -ENXIO;
	}

	priv = devm_kzalloc(&pdev->dev, sizeof(*priv), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	priv->rng.name = pdev->name;
#ifndef CONFIG_PM
	priv->rng.init = mtk_rng_init;
	priv->rng.cleanup = mtk_rng_cleanup;
#endif
	priv->rng.read = mtk_rng_read;
	priv->rng.priv = (unsigned long)&pdev->dev;
	priv->rng.quality = 900;

	priv->clk = devm_clk_get(&pdev->dev, "rng");
	if (IS_ERR(priv->clk)) {
		ret = PTR_ERR(priv->clk);
		dev_err(&pdev->dev, "no clock for device: %d\n", ret);
		return ret;
	}

	priv->base = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(priv->base))
		return PTR_ERR(priv->base);

	ret = devm_hwrng_register(&pdev->dev, &priv->rng);
	if (ret) {
		dev_err(&pdev->dev, "failed to register rng device: %d\n",
			ret);
		return ret;
	}

	dev_set_drvdata(&pdev->dev, priv);
	pm_runtime_set_autosuspend_delay(&pdev->dev, RNG_AUTOSUSPEND_TIMEOUT);
	pm_runtime_use_autosuspend(&pdev->dev);
	pm_runtime_enable(&pdev->dev);

	dev_info(&pdev->dev, "registered RNG driver\n");

	return 0;
}