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
struct net_device {int mtu; int /*<<< orphan*/  features; } ;
struct bnx2x {scalar_t__ recovery_state; int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2X_ERR (char*) ; 
 int /*<<< orphan*/  BNX2X_MSG_IOV ; 
 scalar_t__ BNX2X_RECOVERY_DONE ; 
 int /*<<< orphan*/  CURR_CFG_MET_OS ; 
 int /*<<< orphan*/  DP (int /*<<< orphan*/ ,char*) ; 
 int EAGAIN ; 
 int EPERM ; 
 scalar_t__ IS_PF (struct bnx2x*) ; 
 int /*<<< orphan*/  NETIF_F_GRO_HW ; 
 scalar_t__ SHMEM2_HAS (struct bnx2x*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SHMEM2_WR (struct bnx2x*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnx2x_mtu_allows_gro (int) ; 
 int bnx2x_reload_if_running (struct net_device*) ; 
 int /*<<< orphan*/  curr_cfg ; 
 struct bnx2x* netdev_priv (struct net_device*) ; 
 scalar_t__ pci_num_vf (int /*<<< orphan*/ ) ; 

int bnx2x_change_mtu(struct net_device *dev, int new_mtu)
{
	struct bnx2x *bp = netdev_priv(dev);

	if (pci_num_vf(bp->pdev)) {
		DP(BNX2X_MSG_IOV, "VFs are enabled, can not change MTU\n");
		return -EPERM;
	}

	if (bp->recovery_state != BNX2X_RECOVERY_DONE) {
		BNX2X_ERR("Can't perform change MTU during parity recovery\n");
		return -EAGAIN;
	}

	/* This does not race with packet allocation
	 * because the actual alloc size is
	 * only updated as part of load
	 */
	dev->mtu = new_mtu;

	if (!bnx2x_mtu_allows_gro(new_mtu))
		dev->features &= ~NETIF_F_GRO_HW;

	if (IS_PF(bp) && SHMEM2_HAS(bp, curr_cfg))
		SHMEM2_WR(bp, curr_cfg, CURR_CFG_MET_OS);

	return bnx2x_reload_if_running(dev);
}