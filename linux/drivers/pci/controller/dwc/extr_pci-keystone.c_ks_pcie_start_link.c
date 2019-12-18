#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u32 ;
struct keystone_pcie {int dummy; } ;
struct dw_pcie {struct device* dev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_STATUS ; 
 int LTSSM_EN_VAL ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*) ; 
 scalar_t__ dw_pcie_link_up (struct dw_pcie*) ; 
 int ks_pcie_app_readl (struct keystone_pcie*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ks_pcie_app_writel (struct keystone_pcie*,int /*<<< orphan*/ ,int) ; 
 struct keystone_pcie* to_keystone_pcie (struct dw_pcie*) ; 

__attribute__((used)) static int ks_pcie_start_link(struct dw_pcie *pci)
{
	struct keystone_pcie *ks_pcie = to_keystone_pcie(pci);
	struct device *dev = pci->dev;
	u32 val;

	if (dw_pcie_link_up(pci)) {
		dev_dbg(dev, "link is already up\n");
		return 0;
	}

	/* Initiate Link Training */
	val = ks_pcie_app_readl(ks_pcie, CMD_STATUS);
	ks_pcie_app_writel(ks_pcie, CMD_STATUS, LTSSM_EN_VAL | val);

	return 0;
}