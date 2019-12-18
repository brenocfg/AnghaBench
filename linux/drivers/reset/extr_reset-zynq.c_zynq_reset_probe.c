#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int nr_resets; int /*<<< orphan*/  of_node; int /*<<< orphan*/ * ops; int /*<<< orphan*/  owner; } ;
struct zynq_reset_data {TYPE_2__ rcdev; int /*<<< orphan*/  offset; int /*<<< orphan*/  slcr; } ;
struct resource {int /*<<< orphan*/  start; } ;
struct TYPE_5__ {int /*<<< orphan*/  of_node; } ;
struct platform_device {TYPE_1__ dev; } ;

/* Variables and functions */
 int BITS_PER_LONG ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*) ; 
 struct zynq_reset_data* devm_kzalloc (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int devm_reset_controller_register (TYPE_1__*,TYPE_2__*) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct zynq_reset_data*) ; 
 int resource_size (struct resource*) ; 
 int /*<<< orphan*/  syscon_regmap_lookup_by_phandle (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  zynq_reset_ops ; 

__attribute__((used)) static int zynq_reset_probe(struct platform_device *pdev)
{
	struct resource *res;
	struct zynq_reset_data *priv;

	priv = devm_kzalloc(&pdev->dev, sizeof(*priv), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;
	platform_set_drvdata(pdev, priv);

	priv->slcr = syscon_regmap_lookup_by_phandle(pdev->dev.of_node,
						     "syscon");
	if (IS_ERR(priv->slcr)) {
		dev_err(&pdev->dev, "unable to get zynq-slcr regmap");
		return PTR_ERR(priv->slcr);
	}

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	if (!res) {
		dev_err(&pdev->dev, "missing IO resource\n");
		return -ENODEV;
	}

	priv->offset = res->start;

	priv->rcdev.owner = THIS_MODULE;
	priv->rcdev.nr_resets = resource_size(res) / 4 * BITS_PER_LONG;
	priv->rcdev.ops = &zynq_reset_ops;
	priv->rcdev.of_node = pdev->dev.of_node;

	return devm_reset_controller_register(&pdev->dev, &priv->rcdev);
}