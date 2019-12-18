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
struct bnx2x {int /*<<< orphan*/  dev; int /*<<< orphan*/  sp_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2X_FILTER_ISCSI_ETH_START_SCHED ; 
 int /*<<< orphan*/  BNX2X_FILTER_ISCSI_ETH_STOP_SCHED ; 
 int /*<<< orphan*/  BNX2X_FILTER_RX_MODE_PENDING ; 
 int /*<<< orphan*/  BNX2X_FILTER_RX_MODE_SCHED ; 
 int /*<<< orphan*/  bnx2x_set_iscsi_eth_rx_mode (struct bnx2x*,int) ; 
 int /*<<< orphan*/  bnx2x_set_storm_rx_mode (struct bnx2x*) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netif_addr_lock_bh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_addr_unlock_bh (int /*<<< orphan*/ ) ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void bnx2x_handle_rx_mode_eqe(struct bnx2x *bp)
{
	netif_addr_lock_bh(bp->dev);

	clear_bit(BNX2X_FILTER_RX_MODE_PENDING, &bp->sp_state);

	/* Send rx_mode command again if was requested */
	if (test_and_clear_bit(BNX2X_FILTER_RX_MODE_SCHED, &bp->sp_state))
		bnx2x_set_storm_rx_mode(bp);
	else if (test_and_clear_bit(BNX2X_FILTER_ISCSI_ETH_START_SCHED,
				    &bp->sp_state))
		bnx2x_set_iscsi_eth_rx_mode(bp, true);
	else if (test_and_clear_bit(BNX2X_FILTER_ISCSI_ETH_STOP_SCHED,
				    &bp->sp_state))
		bnx2x_set_iscsi_eth_rx_mode(bp, false);

	netif_addr_unlock_bh(bp->dev);
}