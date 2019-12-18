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
struct pxa_pinctrl_group {int /*<<< orphan*/  pin; int /*<<< orphan*/  name; } ;
struct TYPE_2__ {int npins; struct pinctrl_pin_desc* pins; } ;
struct pxa_pinctrl {int npins; int ngroups; struct pxa_pinctrl_group* groups; int /*<<< orphan*/  dev; TYPE_1__ desc; struct pxa_desc_pin const* ppins; } ;
struct pinctrl_pin_desc {int /*<<< orphan*/  number; int /*<<< orphan*/  name; } ;
struct pxa_desc_pin {struct pinctrl_pin_desc pin; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct pinctrl_pin_desc* devm_kcalloc (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 struct pxa_pinctrl_group* devm_kmalloc_array (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int pxa2xx_build_functions (struct pxa_pinctrl*) ; 
 int pxa2xx_build_groups (struct pxa_pinctrl*) ; 

__attribute__((used)) static int pxa2xx_build_state(struct pxa_pinctrl *pctl,
			      const struct pxa_desc_pin *ppins, int npins)
{
	struct pxa_pinctrl_group *group;
	struct pinctrl_pin_desc *pins;
	int ret, i;

	pctl->npins = npins;
	pctl->ppins = ppins;
	pctl->ngroups = npins;

	pctl->desc.npins = npins;
	pins = devm_kcalloc(pctl->dev, npins, sizeof(*pins), GFP_KERNEL);
	if (!pins)
		return -ENOMEM;

	pctl->desc.pins = pins;
	for (i = 0; i < npins; i++)
		pins[i] = ppins[i].pin;

	pctl->groups = devm_kmalloc_array(pctl->dev, pctl->ngroups,
					  sizeof(*pctl->groups), GFP_KERNEL);
	if (!pctl->groups)
		return -ENOMEM;

	for (i = 0; i < npins; i++) {
		group = pctl->groups + i;
		group->name = ppins[i].pin.name;
		group->pin = ppins[i].pin.number;
	}

	ret = pxa2xx_build_functions(pctl);
	if (ret)
		return ret;

	ret = pxa2xx_build_groups(pctl);
	if (ret)
		return ret;

	return 0;
}