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
typedef  int u32 ;
struct keystone_pcie {scalar_t__ is_am6; TYPE_1__* pci; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {struct device* dev; } ;

/* Variables and functions */
 int AM6_ERR_AER ; 
 int ERR_AER ; 
 int ERR_AXI ; 
 int ERR_CORR ; 
 int ERR_FATAL ; 
 int /*<<< orphan*/  ERR_IRQ_STATUS ; 
 int ERR_NONFATAL ; 
 int ERR_SYS ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int ks_pcie_app_readl (struct keystone_pcie*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ks_pcie_app_writel (struct keystone_pcie*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static irqreturn_t ks_pcie_handle_error_irq(struct keystone_pcie *ks_pcie)
{
	u32 reg;
	struct device *dev = ks_pcie->pci->dev;

	reg = ks_pcie_app_readl(ks_pcie, ERR_IRQ_STATUS);
	if (!reg)
		return IRQ_NONE;

	if (reg & ERR_SYS)
		dev_err(dev, "System Error\n");

	if (reg & ERR_FATAL)
		dev_err(dev, "Fatal Error\n");

	if (reg & ERR_NONFATAL)
		dev_dbg(dev, "Non Fatal Error\n");

	if (reg & ERR_CORR)
		dev_dbg(dev, "Correctable Error\n");

	if (!ks_pcie->is_am6 && (reg & ERR_AXI))
		dev_err(dev, "AXI tag lookup fatal Error\n");

	if (reg & ERR_AER || (ks_pcie->is_am6 && (reg & AM6_ERR_AER)))
		dev_err(dev, "ECRC Error\n");

	ks_pcie_app_writel(ks_pcie, ERR_IRQ_STATUS, reg);

	return IRQ_HANDLED;
}