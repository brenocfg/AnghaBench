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
struct pxa168_eth_private {int /*<<< orphan*/  dev; } ;
struct mii_bus {struct pxa168_eth_private* priv; } ;

/* Variables and functions */
 int ENODEV ; 
 int ETIMEDOUT ; 
 int PHY_WAIT_ITERATIONS ; 
 int /*<<< orphan*/  SMI ; 
 int SMI_OP_R ; 
 int SMI_R_VALID ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  netdev_warn (int /*<<< orphan*/ ,char*) ; 
 int rdl (struct pxa168_eth_private*,int /*<<< orphan*/ ) ; 
 scalar_t__ smi_wait_ready (struct pxa168_eth_private*) ; 
 int /*<<< orphan*/  wrl (struct pxa168_eth_private*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int pxa168_smi_read(struct mii_bus *bus, int phy_addr, int regnum)
{
	struct pxa168_eth_private *pep = bus->priv;
	int i = 0;
	int val;

	if (smi_wait_ready(pep)) {
		netdev_warn(pep->dev, "pxa168_eth: SMI bus busy timeout\n");
		return -ETIMEDOUT;
	}
	wrl(pep, SMI, (phy_addr << 16) | (regnum << 21) | SMI_OP_R);
	/* now wait for the data to be valid */
	for (i = 0; !((val = rdl(pep, SMI)) & SMI_R_VALID); i++) {
		if (i == PHY_WAIT_ITERATIONS) {
			netdev_warn(pep->dev,
				    "pxa168_eth: SMI bus read not valid\n");
			return -ENODEV;
		}
		msleep(10);
	}

	return val & 0xffff;
}