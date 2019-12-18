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
struct TYPE_5__ {struct device_node* of_node; } ;
struct platform_device {TYPE_1__ dev; } ;
struct mvneta_bm {int /*<<< orphan*/  clk; struct platform_device* pdev; int /*<<< orphan*/  reg_base; } ;
struct device_node {struct mvneta_bm* data; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  dev_info (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  devm_clk_get (TYPE_1__*,int /*<<< orphan*/ *) ; 
 struct mvneta_bm* devm_kzalloc (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_platform_ioremap_resource (struct platform_device*,int /*<<< orphan*/ ) ; 
 int mvneta_bm_get_sram (struct device_node*,struct mvneta_bm*) ; 
 int mvneta_bm_init (struct mvneta_bm*) ; 
 int /*<<< orphan*/  mvneta_bm_put_sram (struct mvneta_bm*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct mvneta_bm*) ; 

__attribute__((used)) static int mvneta_bm_probe(struct platform_device *pdev)
{
	struct device_node *dn = pdev->dev.of_node;
	struct mvneta_bm *priv;
	int err;

	priv = devm_kzalloc(&pdev->dev, sizeof(struct mvneta_bm), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	priv->reg_base = devm_platform_ioremap_resource(pdev, 0);
	if (IS_ERR(priv->reg_base))
		return PTR_ERR(priv->reg_base);

	priv->clk = devm_clk_get(&pdev->dev, NULL);
	if (IS_ERR(priv->clk))
		return PTR_ERR(priv->clk);
	err = clk_prepare_enable(priv->clk);
	if (err < 0)
		return err;

	err = mvneta_bm_get_sram(dn, priv);
	if (err < 0) {
		dev_err(&pdev->dev, "failed to allocate internal memory\n");
		goto err_clk;
	}

	priv->pdev = pdev;

	/* Initialize buffer manager internals */
	err = mvneta_bm_init(priv);
	if (err < 0) {
		dev_err(&pdev->dev, "failed to initialize controller\n");
		goto err_sram;
	}

	dn->data = priv;
	platform_set_drvdata(pdev, priv);

	dev_info(&pdev->dev, "Buffer Manager for network controller enabled\n");

	return 0;

err_sram:
	mvneta_bm_put_sram(priv);
err_clk:
	clk_disable_unprepare(priv->clk);
	return err;
}