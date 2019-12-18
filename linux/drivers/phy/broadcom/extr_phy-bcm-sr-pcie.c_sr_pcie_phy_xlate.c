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
struct sr_pcie_phy_core {TYPE_1__* phys; } ;
struct phy {int dummy; } ;
struct of_phandle_args {int* args; } ;
struct device {int dummy; } ;
struct TYPE_2__ {struct phy* phy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENODEV ; 
 struct phy* ERR_PTR (int /*<<< orphan*/ ) ; 
 int SR_NR_PCIE_PHYS ; 
 scalar_t__ WARN_ON (int) ; 
 struct sr_pcie_phy_core* dev_get_drvdata (struct device*) ; 

__attribute__((used)) static struct phy *sr_pcie_phy_xlate(struct device *dev,
				     struct of_phandle_args *args)
{
	struct sr_pcie_phy_core *core;
	int phy_idx;

	core = dev_get_drvdata(dev);
	if (!core)
		return ERR_PTR(-EINVAL);

	phy_idx = args->args[0];

	if (WARN_ON(phy_idx >= SR_NR_PCIE_PHYS))
		return ERR_PTR(-ENODEV);

	return core->phys[phy_idx].phy;
}