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
struct ef4_nic {int phy_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  MDIO_MMD_PMAPMD ; 
 int /*<<< orphan*/  MDIO_PMA_TXDIS ; 
 int /*<<< orphan*/  MDIO_PMD_TXDIS_GLOBAL ; 
 int PHY_MODE_TX_DISABLED ; 
 int /*<<< orphan*/  ef4_mdio_set_flag (struct ef4_nic*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void ef4_mdio_transmit_disable(struct ef4_nic *efx)
{
	ef4_mdio_set_flag(efx, MDIO_MMD_PMAPMD,
			  MDIO_PMA_TXDIS, MDIO_PMD_TXDIS_GLOBAL,
			  efx->phy_mode & PHY_MODE_TX_DISABLED);
}