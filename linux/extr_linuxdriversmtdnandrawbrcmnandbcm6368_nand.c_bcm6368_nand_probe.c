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
struct bcm6368_nand_soc {scalar_t__ base; struct brcmnand_soc soc; } ;

/* Variables and functions */
 scalar_t__ BCM6368_NAND_INT ; 
 int /*<<< orphan*/  BCM6368_NAND_STATUS_MASK ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (scalar_t__) ; 
 int PTR_ERR (scalar_t__) ; 
 int /*<<< orphan*/  bcm6368_nand_intc_ack ; 
 int /*<<< orphan*/  bcm6368_nand_intc_set ; 
 int brcmnand_probe (struct platform_device*,struct brcmnand_soc*) ; 
 int /*<<< orphan*/  brcmnand_writel (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ devm_ioremap_resource (struct device*,struct resource*) ; 
 struct bcm6368_nand_soc* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource_byname (struct platform_device*,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int bcm6368_nand_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct bcm6368_nand_soc *priv;
	struct brcmnand_soc *soc;
	struct resource *res;

	priv = devm_kzalloc(dev, sizeof(*priv), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;
	soc = &priv->soc;

	res = platform_get_resource_byname(pdev,
		IORESOURCE_MEM, "nand-int-base");
	priv->base = devm_ioremap_resource(dev, res);
	if (IS_ERR(priv->base))
		return PTR_ERR(priv->base);

	soc->ctlrdy_ack = bcm6368_nand_intc_ack;
	soc->ctlrdy_set_enabled = bcm6368_nand_intc_set;

	/* Disable and ack all interrupts  */
	brcmnand_writel(0, priv->base + BCM6368_NAND_INT);
	brcmnand_writel(BCM6368_NAND_STATUS_MASK,
			priv->base + BCM6368_NAND_INT);

	return brcmnand_probe(pdev, soc);
}