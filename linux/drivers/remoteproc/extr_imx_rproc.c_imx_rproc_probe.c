#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct device {struct device_node* of_node; } ;
struct rproc {struct device dev; struct imx_rproc* priv; } ;
struct regmap_config {char* name; } ;
struct regmap {int dummy; } ;
struct platform_device {struct device dev; } ;
struct imx_rproc_dcfg {int dummy; } ;
struct imx_rproc {struct regmap* clk; struct device* dev; struct imx_rproc_dcfg const* dcfg; struct regmap* regmap; struct rproc* rproc; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 scalar_t__ IS_ERR (struct regmap*) ; 
 int PTR_ERR (struct regmap*) ; 
 int /*<<< orphan*/  clk_disable_unprepare (struct regmap*) ; 
 int clk_prepare_enable (struct regmap*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  dev_set_drvdata (struct device*,struct rproc*) ; 
 struct regmap* devm_clk_get (struct device*,int /*<<< orphan*/ *) ; 
 int imx_rproc_addr_init (struct imx_rproc*,struct platform_device*) ; 
 int /*<<< orphan*/  imx_rproc_ops ; 
 struct imx_rproc_dcfg* of_device_get_match_data (struct device*) ; 
 int /*<<< orphan*/  regmap_attach_dev (struct device*,struct regmap*,struct regmap_config*) ; 
 int rproc_add (struct rproc*) ; 
 struct rproc* rproc_alloc (struct device*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  rproc_free (struct rproc*) ; 
 struct regmap* syscon_regmap_lookup_by_phandle (struct device_node*,char*) ; 

__attribute__((used)) static int imx_rproc_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct device_node *np = dev->of_node;
	struct imx_rproc *priv;
	struct rproc *rproc;
	struct regmap_config config = { .name = "imx-rproc" };
	const struct imx_rproc_dcfg *dcfg;
	struct regmap *regmap;
	int ret;

	regmap = syscon_regmap_lookup_by_phandle(np, "syscon");
	if (IS_ERR(regmap)) {
		dev_err(dev, "failed to find syscon\n");
		return PTR_ERR(regmap);
	}
	regmap_attach_dev(dev, regmap, &config);

	/* set some other name then imx */
	rproc = rproc_alloc(dev, "imx-rproc", &imx_rproc_ops,
			    NULL, sizeof(*priv));
	if (!rproc)
		return -ENOMEM;

	dcfg = of_device_get_match_data(dev);
	if (!dcfg) {
		ret = -EINVAL;
		goto err_put_rproc;
	}

	priv = rproc->priv;
	priv->rproc = rproc;
	priv->regmap = regmap;
	priv->dcfg = dcfg;
	priv->dev = dev;

	dev_set_drvdata(dev, rproc);

	ret = imx_rproc_addr_init(priv, pdev);
	if (ret) {
		dev_err(dev, "failed on imx_rproc_addr_init\n");
		goto err_put_rproc;
	}

	priv->clk = devm_clk_get(dev, NULL);
	if (IS_ERR(priv->clk)) {
		dev_err(dev, "Failed to get clock\n");
		ret = PTR_ERR(priv->clk);
		goto err_put_rproc;
	}

	/*
	 * clk for M4 block including memory. Should be
	 * enabled before .start for FW transfer.
	 */
	ret = clk_prepare_enable(priv->clk);
	if (ret) {
		dev_err(&rproc->dev, "Failed to enable clock\n");
		goto err_put_rproc;
	}

	ret = rproc_add(rproc);
	if (ret) {
		dev_err(dev, "rproc_add failed\n");
		goto err_put_clk;
	}

	return 0;

err_put_clk:
	clk_disable_unprepare(priv->clk);
err_put_rproc:
	rproc_free(rproc);

	return ret;
}