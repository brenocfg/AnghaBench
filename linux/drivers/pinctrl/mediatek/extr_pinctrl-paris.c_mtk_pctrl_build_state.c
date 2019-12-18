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
struct platform_device {int /*<<< orphan*/  dev; } ;
struct mtk_pinctrl_group {int /*<<< orphan*/  pin; int /*<<< orphan*/  name; } ;
struct mtk_pinctrl {int /*<<< orphan*/ * grp_names; struct mtk_pinctrl_group* groups; TYPE_1__* soc; } ;
struct mtk_pin_desc {int /*<<< orphan*/  name; int /*<<< orphan*/  number; } ;
struct TYPE_2__ {int npins; struct mtk_pin_desc* pins; int /*<<< orphan*/  ngrps; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 void* devm_kmalloc_array (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 struct mtk_pinctrl* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int mtk_pctrl_build_state(struct platform_device *pdev)
{
	struct mtk_pinctrl *hw = platform_get_drvdata(pdev);
	int i;

	/* Allocate groups */
	hw->groups = devm_kmalloc_array(&pdev->dev, hw->soc->ngrps,
					sizeof(*hw->groups), GFP_KERNEL);
	if (!hw->groups)
		return -ENOMEM;

	/* We assume that one pin is one group, use pin name as group name. */
	hw->grp_names = devm_kmalloc_array(&pdev->dev, hw->soc->ngrps,
					   sizeof(*hw->grp_names), GFP_KERNEL);
	if (!hw->grp_names)
		return -ENOMEM;

	for (i = 0; i < hw->soc->npins; i++) {
		const struct mtk_pin_desc *pin = hw->soc->pins + i;
		struct mtk_pinctrl_group *group = hw->groups + i;

		group->name = pin->name;
		group->pin = pin->number;

		hw->grp_names[i] = pin->name;
	}

	return 0;
}