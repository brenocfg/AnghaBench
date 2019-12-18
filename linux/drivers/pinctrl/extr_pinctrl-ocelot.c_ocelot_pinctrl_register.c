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
struct platform_device {int /*<<< orphan*/  dev; } ;
struct ocelot_pinctrl {int /*<<< orphan*/  pctl; int /*<<< orphan*/  desc; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  devm_pinctrl_register (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct ocelot_pinctrl*) ; 
 int ocelot_create_group_func_map (int /*<<< orphan*/ *,struct ocelot_pinctrl*) ; 

__attribute__((used)) static int ocelot_pinctrl_register(struct platform_device *pdev,
				   struct ocelot_pinctrl *info)
{
	int ret;

	ret = ocelot_create_group_func_map(&pdev->dev, info);
	if (ret) {
		dev_err(&pdev->dev, "Unable to create group func map.\n");
		return ret;
	}

	info->pctl = devm_pinctrl_register(&pdev->dev, info->desc, info);
	if (IS_ERR(info->pctl)) {
		dev_err(&pdev->dev, "Failed to register pinctrl\n");
		return PTR_ERR(info->pctl);
	}

	return 0;
}