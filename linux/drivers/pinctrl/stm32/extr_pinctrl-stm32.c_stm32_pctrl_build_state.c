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
struct stm32_pinctrl_group {int /*<<< orphan*/  pin; int /*<<< orphan*/  name; } ;
struct stm32_pinctrl {int ngroups; int npins; int /*<<< orphan*/ * grp_names; struct stm32_pinctrl_group* groups; struct stm32_desc_pin* pins; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; int /*<<< orphan*/  number; } ;
struct stm32_desc_pin {TYPE_1__ pin; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 void* devm_kcalloc (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 
 struct stm32_pinctrl* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int stm32_pctrl_build_state(struct platform_device *pdev)
{
	struct stm32_pinctrl *pctl = platform_get_drvdata(pdev);
	int i;

	pctl->ngroups = pctl->npins;

	/* Allocate groups */
	pctl->groups = devm_kcalloc(&pdev->dev, pctl->ngroups,
				    sizeof(*pctl->groups), GFP_KERNEL);
	if (!pctl->groups)
		return -ENOMEM;

	/* We assume that one pin is one group, use pin name as group name. */
	pctl->grp_names = devm_kcalloc(&pdev->dev, pctl->ngroups,
				       sizeof(*pctl->grp_names), GFP_KERNEL);
	if (!pctl->grp_names)
		return -ENOMEM;

	for (i = 0; i < pctl->npins; i++) {
		const struct stm32_desc_pin *pin = pctl->pins + i;
		struct stm32_pinctrl_group *group = pctl->groups + i;

		group->name = pin->pin.name;
		group->pin = pin->pin.number;
		pctl->grp_names[i] = pin->pin.name;
	}

	return 0;
}