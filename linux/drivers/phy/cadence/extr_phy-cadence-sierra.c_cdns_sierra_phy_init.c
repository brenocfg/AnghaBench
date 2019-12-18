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
typedef  int u32 ;
struct TYPE_3__ {int /*<<< orphan*/  parent; } ;
struct phy {TYPE_1__ dev; } ;
struct cdns_sierra_phy {scalar_t__ base; TYPE_2__* init_data; } ;
struct cdns_sierra_inst {scalar_t__ phy_type; int num_lanes; int mlane; } ;
struct cdns_reg_pairs {scalar_t__ off; int /*<<< orphan*/  val; } ;
struct TYPE_4__ {int pcie_regs; int usb_regs; struct cdns_reg_pairs* usb_vals; struct cdns_reg_pairs* pcie_vals; } ;

/* Variables and functions */
 scalar_t__ PHY_TYPE_PCIE ; 
 scalar_t__ PHY_TYPE_USB3 ; 
 struct cdns_sierra_phy* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 struct cdns_sierra_inst* phy_get_drvdata (struct phy*) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void cdns_sierra_phy_init(struct phy *gphy)
{
	struct cdns_sierra_inst *ins = phy_get_drvdata(gphy);
	struct cdns_sierra_phy *phy = dev_get_drvdata(gphy->dev.parent);
	int i, j;
	struct cdns_reg_pairs *vals;
	u32 num_regs;

	if (ins->phy_type == PHY_TYPE_PCIE) {
		num_regs = phy->init_data->pcie_regs;
		vals = phy->init_data->pcie_vals;
	} else if (ins->phy_type == PHY_TYPE_USB3) {
		num_regs = phy->init_data->usb_regs;
		vals = phy->init_data->usb_vals;
	} else {
		return;
	}
	for (i = 0; i < ins->num_lanes; i++)
		for (j = 0; j < num_regs ; j++)
			writel(vals[j].val, phy->base +
				vals[j].off + (i + ins->mlane) * 0x800);
}