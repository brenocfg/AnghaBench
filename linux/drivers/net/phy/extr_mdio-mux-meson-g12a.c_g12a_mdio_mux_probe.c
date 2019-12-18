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
struct device {int /*<<< orphan*/  of_node; } ;
struct platform_device {struct device dev; } ;
struct g12a_mdio_mux {int /*<<< orphan*/  pclk; int /*<<< orphan*/  mux_handle; int /*<<< orphan*/  regs; } ;

/* Variables and functions */
 int ENOMEM ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int /*<<< orphan*/  devm_clk_get (struct device*,char*) ; 
 struct g12a_mdio_mux* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_platform_ioremap_resource (struct platform_device*,int /*<<< orphan*/ ) ; 
 int g12a_ephy_glue_clk_register (struct device*) ; 
 int /*<<< orphan*/  g12a_mdio_switch_fn ; 
 int mdio_mux_init (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct g12a_mdio_mux*) ; 

__attribute__((used)) static int g12a_mdio_mux_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct g12a_mdio_mux *priv;
	int ret;

	priv = devm_kzalloc(dev, sizeof(*priv), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	platform_set_drvdata(pdev, priv);

	priv->regs = devm_platform_ioremap_resource(pdev, 0);
	if (IS_ERR(priv->regs))
		return PTR_ERR(priv->regs);

	priv->pclk = devm_clk_get(dev, "pclk");
	if (IS_ERR(priv->pclk)) {
		ret = PTR_ERR(priv->pclk);
		if (ret != -EPROBE_DEFER)
			dev_err(dev, "failed to get peripheral clock\n");
		return ret;
	}

	/* Make sure the device registers are clocked */
	ret = clk_prepare_enable(priv->pclk);
	if (ret) {
		dev_err(dev, "failed to enable peripheral clock");
		return ret;
	}

	/* Register PLL in CCF */
	ret = g12a_ephy_glue_clk_register(dev);
	if (ret)
		goto err;

	ret = mdio_mux_init(dev, dev->of_node, g12a_mdio_switch_fn,
			    &priv->mux_handle, dev, NULL);
	if (ret) {
		if (ret != -EPROBE_DEFER)
			dev_err(dev, "mdio multiplexer init failed: %d", ret);
		goto err;
	}

	return 0;

err:
	clk_disable_unprepare(priv->pclk);
	return ret;
}