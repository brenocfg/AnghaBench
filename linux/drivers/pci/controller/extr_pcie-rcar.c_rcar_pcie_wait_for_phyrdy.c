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
struct rcar_pcie {int dummy; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int /*<<< orphan*/  PCIEPHYSR ; 
 int PHYRDY ; 
 int /*<<< orphan*/  msleep (int) ; 
 int rcar_pci_read_reg (struct rcar_pcie*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rcar_pcie_wait_for_phyrdy(struct rcar_pcie *pcie)
{
	unsigned int timeout = 10;

	while (timeout--) {
		if (rcar_pci_read_reg(pcie, PCIEPHYSR) & PHYRDY)
			return 0;

		msleep(5);
	}

	return -ETIMEDOUT;
}