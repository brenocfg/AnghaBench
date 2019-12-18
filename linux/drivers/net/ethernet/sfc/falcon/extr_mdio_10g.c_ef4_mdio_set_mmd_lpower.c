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
struct ef4_nic {int /*<<< orphan*/  net_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  MDIO_CTRL1 ; 
 int /*<<< orphan*/  MDIO_CTRL1_LPOWER ; 
 int /*<<< orphan*/  MDIO_STAT1 ; 
 int MDIO_STAT1_LPOWERABLE ; 
 int /*<<< orphan*/  drv ; 
 int ef4_mdio_read (struct ef4_nic*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ef4_mdio_set_flag (struct ef4_nic*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  netif_vdbg (struct ef4_nic*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int) ; 

__attribute__((used)) static void ef4_mdio_set_mmd_lpower(struct ef4_nic *efx,
				    int lpower, int mmd)
{
	int stat = ef4_mdio_read(efx, mmd, MDIO_STAT1);

	netif_vdbg(efx, drv, efx->net_dev, "Setting low power mode for MMD %d to %d\n",
		  mmd, lpower);

	if (stat & MDIO_STAT1_LPOWERABLE) {
		ef4_mdio_set_flag(efx, mmd, MDIO_CTRL1,
				  MDIO_CTRL1_LPOWER, lpower);
	}
}