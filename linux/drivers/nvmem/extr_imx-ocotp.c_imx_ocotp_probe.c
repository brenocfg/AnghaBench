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
struct device {int dummy; } ;
struct platform_device {struct device dev; } ;
struct ocotp_priv {TYPE_2__* config; TYPE_1__* params; int /*<<< orphan*/  clk; int /*<<< orphan*/  base; struct device* dev; } ;
struct nvmem_device {int dummy; } ;
struct TYPE_5__ {int size; struct ocotp_priv* priv; struct device* dev; } ;
struct TYPE_4__ {int nregs; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR_OR_ZERO (struct nvmem_device*) ; 
 int /*<<< orphan*/  devm_clk_get (struct device*,int /*<<< orphan*/ *) ; 
 struct ocotp_priv* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 struct nvmem_device* devm_nvmem_register (struct device*,TYPE_2__*) ; 
 int /*<<< orphan*/  devm_platform_ioremap_resource (struct platform_device*,int /*<<< orphan*/ ) ; 
 TYPE_2__ imx_ocotp_nvmem_config ; 
 TYPE_1__* of_device_get_match_data (struct device*) ; 

__attribute__((used)) static int imx_ocotp_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct ocotp_priv *priv;
	struct nvmem_device *nvmem;

	priv = devm_kzalloc(dev, sizeof(*priv), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	priv->dev = dev;

	priv->base = devm_platform_ioremap_resource(pdev, 0);
	if (IS_ERR(priv->base))
		return PTR_ERR(priv->base);

	priv->clk = devm_clk_get(dev, NULL);
	if (IS_ERR(priv->clk))
		return PTR_ERR(priv->clk);

	priv->params = of_device_get_match_data(&pdev->dev);
	imx_ocotp_nvmem_config.size = 4 * priv->params->nregs;
	imx_ocotp_nvmem_config.dev = dev;
	imx_ocotp_nvmem_config.priv = priv;
	priv->config = &imx_ocotp_nvmem_config;
	nvmem = devm_nvmem_register(dev, &imx_ocotp_nvmem_config);


	return PTR_ERR_OR_ZERO(nvmem);
}