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
typedef  int /*<<< orphan*/  u16 ;
struct net_device {int dummy; } ;
struct bnx2x {int /*<<< orphan*/  link_params; } ;

/* Variables and functions */
 int DEFAULT_PHY_DEV_ADDR ; 
 int /*<<< orphan*/  DP (int /*<<< orphan*/ ,char*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int MDIO_DEVAD_NONE ; 
 int /*<<< orphan*/  NETIF_MSG_LINK ; 
 int /*<<< orphan*/  bnx2x_acquire_phy_lock (struct bnx2x*) ; 
 int bnx2x_phy_write (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnx2x_release_phy_lock (struct bnx2x*) ; 
 struct bnx2x* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int bnx2x_mdio_write(struct net_device *netdev, int prtad, int devad,
			    u16 addr, u16 value)
{
	struct bnx2x *bp = netdev_priv(netdev);
	int rc;

	DP(NETIF_MSG_LINK,
	   "mdio_write: prtad 0x%x, devad 0x%x, addr 0x%x, value 0x%x\n",
	   prtad, devad, addr, value);

	/* The HW expects different devad if CL22 is used */
	devad = (devad == MDIO_DEVAD_NONE) ? DEFAULT_PHY_DEV_ADDR : devad;

	bnx2x_acquire_phy_lock(bp);
	rc = bnx2x_phy_write(&bp->link_params, prtad, devad, addr, value);
	bnx2x_release_phy_lock(bp);
	return rc;
}