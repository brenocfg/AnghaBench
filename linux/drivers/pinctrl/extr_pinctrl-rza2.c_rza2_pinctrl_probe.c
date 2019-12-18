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
struct TYPE_2__ {int npins; int /*<<< orphan*/  owner; int /*<<< orphan*/ * pmxops; int /*<<< orphan*/ * pctlops; int /*<<< orphan*/  name; } ;
struct rza2_pinctrl_priv {int npins; TYPE_1__ desc; int /*<<< orphan*/  base; int /*<<< orphan*/ * dev; } ;
struct resource {int dummy; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRIVER_NAME ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int RZA2_PINS_PER_PORT ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_ioremap_resource (int /*<<< orphan*/ *,struct resource*) ; 
 struct rza2_pinctrl_priv* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 scalar_t__ of_device_get_match_data (int /*<<< orphan*/ *) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct rza2_pinctrl_priv*) ; 
 int /*<<< orphan*/ * port_names ; 
 int /*<<< orphan*/  rza2_pinctrl_ops ; 
 int rza2_pinctrl_register (struct rza2_pinctrl_priv*) ; 
 int /*<<< orphan*/  rza2_pinmux_ops ; 

__attribute__((used)) static int rza2_pinctrl_probe(struct platform_device *pdev)
{
	struct rza2_pinctrl_priv *priv;
	struct resource *res;
	int ret;

	priv = devm_kzalloc(&pdev->dev, sizeof(*priv), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	priv->dev = &pdev->dev;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	priv->base = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(priv->base))
		return PTR_ERR(priv->base);

	platform_set_drvdata(pdev, priv);

	priv->npins = (int)(uintptr_t)of_device_get_match_data(&pdev->dev) *
		      RZA2_PINS_PER_PORT;

	priv->desc.name		= DRIVER_NAME;
	priv->desc.pctlops	= &rza2_pinctrl_ops;
	priv->desc.pmxops	= &rza2_pinmux_ops;
	priv->desc.owner	= THIS_MODULE;

	ret = rza2_pinctrl_register(priv);
	if (ret)
		return ret;

	dev_info(&pdev->dev, "Registered ports P0 - P%c\n",
		 port_names[priv->desc.npins / RZA2_PINS_PER_PORT - 1]);

	return 0;
}