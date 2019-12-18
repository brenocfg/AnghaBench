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
struct resource {int /*<<< orphan*/  start; } ;
struct device {int /*<<< orphan*/  of_node; } ;
struct platform_device {struct device dev; } ;
struct TYPE_2__ {int nr_resets; int /*<<< orphan*/  of_node; int /*<<< orphan*/ * ops; int /*<<< orphan*/  owner; } ;
struct brcmstb_reset {TYPE_1__ rcdev; int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int DIV_ROUND_DOWN_ULL (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int /*<<< orphan*/  IS_ALIGNED (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SW_INIT_BANK_SIZE ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  brcmstb_reset_ops ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  dev_set_drvdata (struct device*,struct brcmstb_reset*) ; 
 int /*<<< orphan*/  devm_ioremap_resource (struct device*,struct resource*) ; 
 struct brcmstb_reset* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int devm_reset_controller_register (struct device*,TYPE_1__*) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  resource_size (struct resource*) ; 

__attribute__((used)) static int brcmstb_reset_probe(struct platform_device *pdev)
{
	struct device *kdev = &pdev->dev;
	struct brcmstb_reset *priv;
	struct resource *res;

	priv = devm_kzalloc(kdev, sizeof(*priv), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	if (!IS_ALIGNED(res->start, SW_INIT_BANK_SIZE) ||
	    !IS_ALIGNED(resource_size(res), SW_INIT_BANK_SIZE)) {
		dev_err(kdev, "incorrect register range\n");
		return -EINVAL;
	}

	priv->base = devm_ioremap_resource(kdev, res);
	if (IS_ERR(priv->base))
		return PTR_ERR(priv->base);

	dev_set_drvdata(kdev, priv);

	priv->rcdev.owner = THIS_MODULE;
	priv->rcdev.nr_resets = DIV_ROUND_DOWN_ULL(resource_size(res),
						   SW_INIT_BANK_SIZE) * 32;
	priv->rcdev.ops = &brcmstb_reset_ops;
	priv->rcdev.of_node = kdev->of_node;
	/* Use defaults: 1 cell and simple xlate function */

	return devm_reset_controller_register(kdev, &priv->rcdev);
}