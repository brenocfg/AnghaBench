#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sunxi_pinctrl_group {char* name; int /*<<< orphan*/  pin; } ;
struct sunxi_pinctrl_function {char** groups; int ngroups; } ;
struct sunxi_pinctrl {int ngroups; int variant; int nfunctions; int /*<<< orphan*/ * functions; TYPE_1__* desc; int /*<<< orphan*/ * irq_array; struct sunxi_pinctrl_group* groups; } ;
struct TYPE_4__ {char* name; int /*<<< orphan*/  number; } ;
struct sunxi_desc_pin {int variant; TYPE_2__ pin; struct sunxi_desc_function* functions; } ;
struct sunxi_desc_function {int variant; int irqnum; int irqbank; scalar_t__ name; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int npins; struct sunxi_desc_pin* pins; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int IRQ_PER_BANK ; 
 void* devm_kcalloc (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 void* krealloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 struct sunxi_pinctrl* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  strcmp (scalar_t__,char*) ; 
 int /*<<< orphan*/  sunxi_pinctrl_add_function (struct sunxi_pinctrl*,scalar_t__) ; 
 struct sunxi_pinctrl_function* sunxi_pinctrl_find_function_by_name (struct sunxi_pinctrl*,scalar_t__) ; 

__attribute__((used)) static int sunxi_pinctrl_build_state(struct platform_device *pdev)
{
	struct sunxi_pinctrl *pctl = platform_get_drvdata(pdev);
	void *ptr;
	int i;

	/*
	 * Allocate groups
	 *
	 * We assume that the number of groups is the number of pins
	 * given in the data array.

	 * This will not always be true, since some pins might not be
	 * available in the current variant, but fortunately for us,
	 * this means that the number of pins is the maximum group
	 * number we will ever see.
	 */
	pctl->groups = devm_kcalloc(&pdev->dev,
				    pctl->desc->npins, sizeof(*pctl->groups),
				    GFP_KERNEL);
	if (!pctl->groups)
		return -ENOMEM;

	for (i = 0; i < pctl->desc->npins; i++) {
		const struct sunxi_desc_pin *pin = pctl->desc->pins + i;
		struct sunxi_pinctrl_group *group = pctl->groups + pctl->ngroups;

		if (pin->variant && !(pctl->variant & pin->variant))
			continue;

		group->name = pin->pin.name;
		group->pin = pin->pin.number;

		/* And now we count the actual number of pins / groups */
		pctl->ngroups++;
	}

	/*
	 * We suppose that we won't have any more functions than pins,
	 * we'll reallocate that later anyway
	 */
	pctl->functions = kcalloc(pctl->ngroups,
				  sizeof(*pctl->functions),
				  GFP_KERNEL);
	if (!pctl->functions)
		return -ENOMEM;

	/* Count functions and their associated groups */
	for (i = 0; i < pctl->desc->npins; i++) {
		const struct sunxi_desc_pin *pin = pctl->desc->pins + i;
		struct sunxi_desc_function *func;

		if (pin->variant && !(pctl->variant & pin->variant))
			continue;

		for (func = pin->functions; func->name; func++) {
			if (func->variant && !(pctl->variant & func->variant))
				continue;

			/* Create interrupt mapping while we're at it */
			if (!strcmp(func->name, "irq")) {
				int irqnum = func->irqnum + func->irqbank * IRQ_PER_BANK;
				pctl->irq_array[irqnum] = pin->pin.number;
			}

			sunxi_pinctrl_add_function(pctl, func->name);
		}
	}

	/* And now allocated and fill the array for real */
	ptr = krealloc(pctl->functions,
		       pctl->nfunctions * sizeof(*pctl->functions),
		       GFP_KERNEL);
	if (!ptr) {
		kfree(pctl->functions);
		pctl->functions = NULL;
		return -ENOMEM;
	}
	pctl->functions = ptr;

	for (i = 0; i < pctl->desc->npins; i++) {
		const struct sunxi_desc_pin *pin = pctl->desc->pins + i;
		struct sunxi_desc_function *func;

		if (pin->variant && !(pctl->variant & pin->variant))
			continue;

		for (func = pin->functions; func->name; func++) {
			struct sunxi_pinctrl_function *func_item;
			const char **func_grp;

			if (func->variant && !(pctl->variant & func->variant))
				continue;

			func_item = sunxi_pinctrl_find_function_by_name(pctl,
									func->name);
			if (!func_item) {
				kfree(pctl->functions);
				return -EINVAL;
			}

			if (!func_item->groups) {
				func_item->groups =
					devm_kcalloc(&pdev->dev,
						     func_item->ngroups,
						     sizeof(*func_item->groups),
						     GFP_KERNEL);
				if (!func_item->groups) {
					kfree(pctl->functions);
					return -ENOMEM;
				}
			}

			func_grp = func_item->groups;
			while (*func_grp)
				func_grp++;

			*func_grp = pin->pin.name;
		}
	}

	return 0;
}