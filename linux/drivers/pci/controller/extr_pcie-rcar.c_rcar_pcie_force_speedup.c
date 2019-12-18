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
struct rcar_pcie {struct device* dev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXPCAP (int) ; 
 int LINK_SPEED ; 
 int LINK_SPEED_5_0GTS ; 
 int /*<<< orphan*/  MACCGSPSETR ; 
 int /*<<< orphan*/  MACCTLR ; 
 int /*<<< orphan*/  MACS2R ; 
 int /*<<< orphan*/  MACSR ; 
 int PCI_EXP_LNKSTA_CLS ; 
 int PCI_EXP_LNKSTA_CLS_5_0GB ; 
 int SPCHGFAIL ; 
 int SPCHGFIN ; 
 int SPCHGSUC ; 
 int SPCNGRSN ; 
 int SPEED_CHANGE ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*,char*) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int rcar_pci_read_reg (struct rcar_pcie*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcar_pci_write_reg (struct rcar_pcie*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcar_rmw32 (struct rcar_pcie*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void rcar_pcie_force_speedup(struct rcar_pcie *pcie)
{
	struct device *dev = pcie->dev;
	unsigned int timeout = 1000;
	u32 macsr;

	if ((rcar_pci_read_reg(pcie, MACS2R) & LINK_SPEED) != LINK_SPEED_5_0GTS)
		return;

	if (rcar_pci_read_reg(pcie, MACCTLR) & SPEED_CHANGE) {
		dev_err(dev, "Speed change already in progress\n");
		return;
	}

	macsr = rcar_pci_read_reg(pcie, MACSR);
	if ((macsr & LINK_SPEED) == LINK_SPEED_5_0GTS)
		goto done;

	/* Set target link speed to 5.0 GT/s */
	rcar_rmw32(pcie, EXPCAP(12), PCI_EXP_LNKSTA_CLS,
		   PCI_EXP_LNKSTA_CLS_5_0GB);

	/* Set speed change reason as intentional factor */
	rcar_rmw32(pcie, MACCGSPSETR, SPCNGRSN, 0);

	/* Clear SPCHGFIN, SPCHGSUC, and SPCHGFAIL */
	if (macsr & (SPCHGFIN | SPCHGSUC | SPCHGFAIL))
		rcar_pci_write_reg(pcie, macsr, MACSR);

	/* Start link speed change */
	rcar_rmw32(pcie, MACCTLR, SPEED_CHANGE, SPEED_CHANGE);

	while (timeout--) {
		macsr = rcar_pci_read_reg(pcie, MACSR);
		if (macsr & SPCHGFIN) {
			/* Clear the interrupt bits */
			rcar_pci_write_reg(pcie, macsr, MACSR);

			if (macsr & SPCHGFAIL)
				dev_err(dev, "Speed change failed\n");

			goto done;
		}

		msleep(1);
	}

	dev_err(dev, "Speed change timed out\n");

done:
	dev_info(dev, "Current link speed is %s GT/s\n",
		 (macsr & LINK_SPEED) == LINK_SPEED_5_0GTS ? "5" : "2.5");
}