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
struct TYPE_4__ {int /*<<< orphan*/  parent; } ;
struct platform_device {TYPE_2__ dev; } ;
struct cdns_sierra_phy {int nsubnodes; TYPE_1__* phys; int /*<<< orphan*/  apb_rst; int /*<<< orphan*/  phy_rst; } ;
struct TYPE_3__ {int /*<<< orphan*/  lnk_rst; } ;

/* Variables and functions */
 struct cdns_sierra_phy* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_disable (TYPE_2__*) ; 
 int /*<<< orphan*/  reset_control_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reset_control_put (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cdns_sierra_phy_remove(struct platform_device *pdev)
{
	struct cdns_sierra_phy *phy = dev_get_drvdata(pdev->dev.parent);
	int i;

	reset_control_assert(phy->phy_rst);
	reset_control_assert(phy->apb_rst);
	pm_runtime_disable(&pdev->dev);

	/*
	 * The device level resets will be put automatically.
	 * Need to put the subnode resets here though.
	 */
	for (i = 0; i < phy->nsubnodes; i++) {
		reset_control_assert(phy->phys[i].lnk_rst);
		reset_control_put(phy->phys[i].lnk_rst);
	}
	return 0;
}