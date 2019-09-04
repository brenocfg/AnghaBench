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
struct resource {int dummy; } ;
struct device {int dummy; } ;
struct platform_device {struct device dev; } ;
struct brcmnand_soc {int /*<<< orphan*/  ctlrdy_set_enabled; int /*<<< orphan*/  ctlrdy_ack; } ;
struct bcm63138_nand_soc {int /*<<< orphan*/  base; struct brcmnand_soc soc; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcm63138_nand_intc_ack ; 
 int /*<<< orphan*/  bcm63138_nand_intc_set ; 
 int brcmnand_probe (struct platform_device*,struct brcmnand_soc*) ; 
 int /*<<< orphan*/  devm_ioremap_resource (struct device*,struct resource*) ; 
 struct bcm63138_nand_soc* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource_byname (struct platform_device*,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int bcm63138_nand_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct bcm63138_nand_soc *priv;
	struct brcmnand_soc *soc;
	struct resource *res;

	priv = devm_kzalloc(dev, sizeof(*priv), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;
	soc = &priv->soc;

	res = platform_get_resource_byname(pdev, IORESOURCE_MEM, "nand-int-base");
	priv->base = devm_ioremap_resource(dev, res);
	if (IS_ERR(priv->base))
		return PTR_ERR(priv->base);

	soc->ctlrdy_ack = bcm63138_nand_intc_ack;
	soc->ctlrdy_set_enabled = bcm63138_nand_intc_set;

	return brcmnand_probe(pdev, soc);
}