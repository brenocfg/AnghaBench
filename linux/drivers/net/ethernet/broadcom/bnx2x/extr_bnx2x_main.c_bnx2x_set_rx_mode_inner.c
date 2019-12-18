#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct bnx2x {TYPE_1__* dev; int /*<<< orphan*/  sp_state; int /*<<< orphan*/  rx_mode; } ;
struct TYPE_4__ {int flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2X_FILTER_RX_MODE_PENDING ; 
 int /*<<< orphan*/  BNX2X_FILTER_RX_MODE_SCHED ; 
 scalar_t__ BNX2X_MAX_MULTICAST ; 
 int /*<<< orphan*/  BNX2X_RX_MODE_ALLMULTI ; 
 int /*<<< orphan*/  BNX2X_RX_MODE_NONE ; 
 int /*<<< orphan*/  BNX2X_RX_MODE_NORMAL ; 
 int /*<<< orphan*/  BNX2X_RX_MODE_PROMISC ; 
 int /*<<< orphan*/  BNX2X_SP_RTNL_VFPF_MCAST ; 
 scalar_t__ CHIP_IS_E1 (struct bnx2x*) ; 
 int /*<<< orphan*/  DP (int /*<<< orphan*/ ,char*,int) ; 
 int IFF_ALLMULTI ; 
 int IFF_PROMISC ; 
 scalar_t__ IS_MF_ISCSI_ONLY (struct bnx2x*) ; 
 scalar_t__ IS_PF (struct bnx2x*) ; 
 int /*<<< orphan*/  NETIF_MSG_IFUP ; 
 int /*<<< orphan*/  bnx2x_schedule_sp_rtnl (struct bnx2x*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ bnx2x_set_mc_list (struct bnx2x*) ; 
 int /*<<< orphan*/  bnx2x_set_storm_rx_mode (struct bnx2x*) ; 
 scalar_t__ bnx2x_set_uc_list (struct bnx2x*) ; 
 int /*<<< orphan*/  bnx2x_vfpf_storm_rx_mode (struct bnx2x*) ; 
 scalar_t__ netdev_mc_count (TYPE_1__*) ; 
 int /*<<< orphan*/  netif_addr_lock_bh (TYPE_1__*) ; 
 int /*<<< orphan*/  netif_addr_unlock_bh (TYPE_1__*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void bnx2x_set_rx_mode_inner(struct bnx2x *bp)
{
	u32 rx_mode = BNX2X_RX_MODE_NORMAL;

	DP(NETIF_MSG_IFUP, "dev->flags = %x\n", bp->dev->flags);

	netif_addr_lock_bh(bp->dev);

	if (bp->dev->flags & IFF_PROMISC) {
		rx_mode = BNX2X_RX_MODE_PROMISC;
	} else if ((bp->dev->flags & IFF_ALLMULTI) ||
		   ((netdev_mc_count(bp->dev) > BNX2X_MAX_MULTICAST) &&
		    CHIP_IS_E1(bp))) {
		rx_mode = BNX2X_RX_MODE_ALLMULTI;
	} else {
		if (IS_PF(bp)) {
			/* some multicasts */
			if (bnx2x_set_mc_list(bp) < 0)
				rx_mode = BNX2X_RX_MODE_ALLMULTI;

			/* release bh lock, as bnx2x_set_uc_list might sleep */
			netif_addr_unlock_bh(bp->dev);
			if (bnx2x_set_uc_list(bp) < 0)
				rx_mode = BNX2X_RX_MODE_PROMISC;
			netif_addr_lock_bh(bp->dev);
		} else {
			/* configuring mcast to a vf involves sleeping (when we
			 * wait for the pf's response).
			 */
			bnx2x_schedule_sp_rtnl(bp,
					       BNX2X_SP_RTNL_VFPF_MCAST, 0);
		}
	}

	bp->rx_mode = rx_mode;
	/* handle ISCSI SD mode */
	if (IS_MF_ISCSI_ONLY(bp))
		bp->rx_mode = BNX2X_RX_MODE_NONE;

	/* Schedule the rx_mode command */
	if (test_bit(BNX2X_FILTER_RX_MODE_PENDING, &bp->sp_state)) {
		set_bit(BNX2X_FILTER_RX_MODE_SCHED, &bp->sp_state);
		netif_addr_unlock_bh(bp->dev);
		return;
	}

	if (IS_PF(bp)) {
		bnx2x_set_storm_rx_mode(bp);
		netif_addr_unlock_bh(bp->dev);
	} else {
		/* VF will need to request the PF to make this change, and so
		 * the VF needs to release the bottom-half lock prior to the
		 * request (as it will likely require sleep on the VF side)
		 */
		netif_addr_unlock_bh(bp->dev);
		bnx2x_vfpf_storm_rx_mode(bp);
	}
}