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
struct TYPE_4__ {int /*<<< orphan*/  npins; int /*<<< orphan*/  pins; int /*<<< orphan*/ * confops; int /*<<< orphan*/ * pmxops; int /*<<< orphan*/ * pctlops; int /*<<< orphan*/  owner; int /*<<< orphan*/  name; } ;
struct sh_pfc_pinctrl {int /*<<< orphan*/  pctl; TYPE_2__ pctl_desc; int /*<<< orphan*/  pins; struct sh_pfc* pfc; } ;
struct sh_pfc {int /*<<< orphan*/  dev; TYPE_1__* info; } ;
struct TYPE_3__ {int /*<<< orphan*/  nr_pins; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRV_NAME ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 struct sh_pfc_pinctrl* devm_kzalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int devm_pinctrl_register_and_init (int /*<<< orphan*/ ,TYPE_2__*,struct sh_pfc_pinctrl*,int /*<<< orphan*/ *) ; 
 int pinctrl_enable (int /*<<< orphan*/ ) ; 
 int sh_pfc_map_pins (struct sh_pfc*,struct sh_pfc_pinctrl*) ; 
 int /*<<< orphan*/  sh_pfc_pinconf_ops ; 
 int /*<<< orphan*/  sh_pfc_pinctrl_ops ; 
 int /*<<< orphan*/  sh_pfc_pinmux_ops ; 
 scalar_t__ unlikely (int) ; 

int sh_pfc_register_pinctrl(struct sh_pfc *pfc)
{
	struct sh_pfc_pinctrl *pmx;
	int ret;

	pmx = devm_kzalloc(pfc->dev, sizeof(*pmx), GFP_KERNEL);
	if (unlikely(!pmx))
		return -ENOMEM;

	pmx->pfc = pfc;

	ret = sh_pfc_map_pins(pfc, pmx);
	if (ret < 0)
		return ret;

	pmx->pctl_desc.name = DRV_NAME;
	pmx->pctl_desc.owner = THIS_MODULE;
	pmx->pctl_desc.pctlops = &sh_pfc_pinctrl_ops;
	pmx->pctl_desc.pmxops = &sh_pfc_pinmux_ops;
	pmx->pctl_desc.confops = &sh_pfc_pinconf_ops;
	pmx->pctl_desc.pins = pmx->pins;
	pmx->pctl_desc.npins = pfc->info->nr_pins;

	ret = devm_pinctrl_register_and_init(pfc->dev, &pmx->pctl_desc, pmx,
					     &pmx->pctl);
	if (ret) {
		dev_err(pfc->dev, "could not register: %i\n", ret);

		return ret;
	}

	return pinctrl_enable(pmx->pctl);
}