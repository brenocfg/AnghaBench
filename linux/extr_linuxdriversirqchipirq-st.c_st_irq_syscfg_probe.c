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
struct st_irq_syscfg {unsigned int syscfg; int /*<<< orphan*/  regmap; } ;
struct TYPE_5__ {struct device_node* of_node; } ;
struct platform_device {TYPE_1__ dev; } ;
struct of_device_id {scalar_t__ data; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  dev_set_drvdata (TYPE_1__*,struct st_irq_syscfg*) ; 
 struct st_irq_syscfg* devm_kzalloc (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 struct of_device_id* of_match_device (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int st_irq_syscfg_enable (struct platform_device*) ; 
 int /*<<< orphan*/  st_irq_syscfg_match ; 
 int /*<<< orphan*/  syscon_regmap_lookup_by_phandle (struct device_node*,char*) ; 

__attribute__((used)) static int st_irq_syscfg_probe(struct platform_device *pdev)
{
	struct device_node *np = pdev->dev.of_node;
	const struct of_device_id *match;
	struct st_irq_syscfg *ddata;

	ddata = devm_kzalloc(&pdev->dev, sizeof(*ddata), GFP_KERNEL);
	if (!ddata)
		return -ENOMEM;

	match = of_match_device(st_irq_syscfg_match, &pdev->dev);
	if (!match)
		return -ENODEV;

	ddata->syscfg = (unsigned int)match->data;

	ddata->regmap = syscon_regmap_lookup_by_phandle(np, "st,syscfg");
	if (IS_ERR(ddata->regmap)) {
		dev_err(&pdev->dev, "syscfg phandle missing\n");
		return PTR_ERR(ddata->regmap);
	}

	dev_set_drvdata(&pdev->dev, ddata);

	return st_irq_syscfg_enable(pdev);
}