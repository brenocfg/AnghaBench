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
 int /*<<< orphan*/  MDIO_MMD_PHYXS ; 
 int /*<<< orphan*/  MDIO_PHYXS_LNSTAT ; 
 int MDIO_PHYXS_LNSTAT_ALIGN ; 
 int ef4_mdio_read (struct ef4_nic*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hw ; 
 int /*<<< orphan*/  netif_dbg (struct ef4_nic*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static inline bool ef4_mdio_phyxgxs_lane_sync(struct ef4_nic *efx)
{
	int i, lane_status;
	bool sync;

	for (i = 0; i < 2; ++i)
		lane_status = ef4_mdio_read(efx, MDIO_MMD_PHYXS,
					    MDIO_PHYXS_LNSTAT);

	sync = !!(lane_status & MDIO_PHYXS_LNSTAT_ALIGN);
	if (!sync)
		netif_dbg(efx, hw, efx->net_dev, "XGXS lane status: %x\n",
			  lane_status);
	return sync;
}