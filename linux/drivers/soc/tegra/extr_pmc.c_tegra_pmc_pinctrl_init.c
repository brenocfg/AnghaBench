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
struct tegra_pmc {int /*<<< orphan*/  dev; int /*<<< orphan*/  pctl_dev; TYPE_1__* soc; } ;
struct TYPE_5__ {scalar_t__ npins; int /*<<< orphan*/  pins; int /*<<< orphan*/  name; } ;
struct TYPE_4__ {scalar_t__ num_pin_descs; int /*<<< orphan*/  pin_descs; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_pinctrl_register (int /*<<< orphan*/ ,TYPE_2__*,struct tegra_pmc*) ; 
 TYPE_2__ tegra_pmc_pctl_desc ; 

__attribute__((used)) static int tegra_pmc_pinctrl_init(struct tegra_pmc *pmc)
{
	int err;

	if (!pmc->soc->num_pin_descs)
		return 0;

	tegra_pmc_pctl_desc.name = dev_name(pmc->dev);
	tegra_pmc_pctl_desc.pins = pmc->soc->pin_descs;
	tegra_pmc_pctl_desc.npins = pmc->soc->num_pin_descs;

	pmc->pctl_dev = devm_pinctrl_register(pmc->dev, &tegra_pmc_pctl_desc,
					      pmc);
	if (IS_ERR(pmc->pctl_dev)) {
		err = PTR_ERR(pmc->pctl_dev);
		dev_err(pmc->dev, "failed to register pin controller: %d\n",
			err);
		return err;
	}

	return 0;
}