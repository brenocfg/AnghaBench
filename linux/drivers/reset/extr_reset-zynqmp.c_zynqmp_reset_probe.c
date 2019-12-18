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
struct TYPE_5__ {int /*<<< orphan*/  nr_resets; int /*<<< orphan*/  of_node; int /*<<< orphan*/  owner; int /*<<< orphan*/ * ops; } ;
struct zynqmp_reset_data {TYPE_2__ rcdev; int /*<<< orphan*/  eemi_ops; } ;
struct TYPE_4__ {int /*<<< orphan*/  of_node; } ;
struct platform_device {TYPE_1__ dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  ZYNQMP_NR_RESETS ; 
 struct zynqmp_reset_data* devm_kzalloc (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int devm_reset_controller_register (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct zynqmp_reset_data*) ; 
 int /*<<< orphan*/  zynqmp_pm_get_eemi_ops () ; 
 int /*<<< orphan*/  zynqmp_reset_ops ; 

__attribute__((used)) static int zynqmp_reset_probe(struct platform_device *pdev)
{
	struct zynqmp_reset_data *priv;

	priv = devm_kzalloc(&pdev->dev, sizeof(*priv), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	priv->eemi_ops = zynqmp_pm_get_eemi_ops();
	if (IS_ERR(priv->eemi_ops))
		return PTR_ERR(priv->eemi_ops);

	platform_set_drvdata(pdev, priv);

	priv->rcdev.ops = &zynqmp_reset_ops;
	priv->rcdev.owner = THIS_MODULE;
	priv->rcdev.of_node = pdev->dev.of_node;
	priv->rcdev.nr_resets = ZYNQMP_NR_RESETS;

	return devm_reset_controller_register(&pdev->dev, &priv->rcdev);
}