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
struct rcar_pcie {int dummy; } ;

/* Variables and functions */
 int ADR_POS ; 
 int /*<<< orphan*/  H1_PCIEPHYADRR ; 
 int /*<<< orphan*/  H1_PCIEPHYDOUTR ; 
 unsigned int LANE_POS ; 
 unsigned int RATE_POS ; 
 unsigned int WRITE_CMD ; 
 int /*<<< orphan*/  phy_wait_for_ack (struct rcar_pcie*) ; 
 int /*<<< orphan*/  rcar_pci_write_reg (struct rcar_pcie*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void phy_write_reg(struct rcar_pcie *pcie,
			  unsigned int rate, u32 addr,
			  unsigned int lane, u32 data)
{
	u32 phyaddr;

	phyaddr = WRITE_CMD |
		((rate & 1) << RATE_POS) |
		((lane & 0xf) << LANE_POS) |
		((addr & 0xff) << ADR_POS);

	/* Set write data */
	rcar_pci_write_reg(pcie, data, H1_PCIEPHYDOUTR);
	rcar_pci_write_reg(pcie, phyaddr, H1_PCIEPHYADRR);

	/* Ignore errors as they will be dealt with if the data link is down */
	phy_wait_for_ack(pcie);

	/* Clear command */
	rcar_pci_write_reg(pcie, 0, H1_PCIEPHYDOUTR);
	rcar_pci_write_reg(pcie, 0, H1_PCIEPHYADRR);

	/* Ignore errors as they will be dealt with if the data link is down */
	phy_wait_for_ack(pcie);
}