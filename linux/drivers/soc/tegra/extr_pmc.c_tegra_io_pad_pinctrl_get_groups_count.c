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
struct tegra_pmc {TYPE_1__* soc; } ;
struct pinctrl_dev {int dummy; } ;
struct TYPE_2__ {int num_io_pads; } ;

/* Variables and functions */
 struct tegra_pmc* pinctrl_dev_get_drvdata (struct pinctrl_dev*) ; 

__attribute__((used)) static int tegra_io_pad_pinctrl_get_groups_count(struct pinctrl_dev *pctl_dev)
{
	struct tegra_pmc *pmc = pinctrl_dev_get_drvdata(pctl_dev);

	return pmc->soc->num_io_pads;
}