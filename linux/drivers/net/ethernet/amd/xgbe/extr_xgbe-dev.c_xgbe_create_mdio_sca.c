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

/* Variables and functions */
 int /*<<< orphan*/  DA ; 
 int /*<<< orphan*/  MAC_MDIOSCAR ; 
 int MII_ADDR_C45 ; 
 int /*<<< orphan*/  PA ; 
 int /*<<< orphan*/  RA ; 
 int /*<<< orphan*/  XGMAC_SET_BITS (unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static unsigned int xgbe_create_mdio_sca(int port, int reg)
{
	unsigned int mdio_sca, da;

	da = (reg & MII_ADDR_C45) ? reg >> 16 : 0;

	mdio_sca = 0;
	XGMAC_SET_BITS(mdio_sca, MAC_MDIOSCAR, RA, reg);
	XGMAC_SET_BITS(mdio_sca, MAC_MDIOSCAR, PA, port);
	XGMAC_SET_BITS(mdio_sca, MAC_MDIOSCAR, DA, da);

	return mdio_sca;
}