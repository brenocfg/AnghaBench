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
struct pinctrl_desc {int /*<<< orphan*/ * pmxops; int /*<<< orphan*/ * pctlops; } ;
struct ltq_pinmux_info {int /*<<< orphan*/  pctrl; int /*<<< orphan*/ * dev; struct pinctrl_desc* desc; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  devm_pinctrl_register (int /*<<< orphan*/ *,struct pinctrl_desc*,struct ltq_pinmux_info*) ; 
 int /*<<< orphan*/  ltq_pctrl_ops ; 
 int /*<<< orphan*/  ltq_pmx_ops ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct ltq_pinmux_info*) ; 

int ltq_pinctrl_register(struct platform_device *pdev,
				struct ltq_pinmux_info *info)
{
	struct pinctrl_desc *desc;

	if (!info)
		return -EINVAL;
	desc = info->desc;
	desc->pctlops = &ltq_pctrl_ops;
	desc->pmxops = &ltq_pmx_ops;
	info->dev = &pdev->dev;

	info->pctrl = devm_pinctrl_register(&pdev->dev, desc, info);
	if (IS_ERR(info->pctrl)) {
		dev_err(&pdev->dev, "failed to register LTQ pinmux driver\n");
		return PTR_ERR(info->pctrl);
	}
	platform_set_drvdata(pdev, info);
	return 0;
}