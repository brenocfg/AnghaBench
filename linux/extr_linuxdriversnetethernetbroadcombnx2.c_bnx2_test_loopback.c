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
struct bnx2 {int /*<<< orphan*/  phy_lock; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2_DRV_MSG_CODE_RESET ; 
 int BNX2_LOOPBACK_FAILED ; 
 int /*<<< orphan*/  BNX2_MAC_LOOPBACK ; 
 int BNX2_MAC_LOOPBACK_FAILED ; 
 int /*<<< orphan*/  BNX2_PHY_LOOPBACK ; 
 int BNX2_PHY_LOOPBACK_FAILED ; 
 int /*<<< orphan*/  bnx2_init_phy (struct bnx2*,int) ; 
 int /*<<< orphan*/  bnx2_reset_nic (struct bnx2*,int /*<<< orphan*/ ) ; 
 scalar_t__ bnx2_run_loopback (struct bnx2*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_running (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
bnx2_test_loopback(struct bnx2 *bp)
{
	int rc = 0;

	if (!netif_running(bp->dev))
		return BNX2_LOOPBACK_FAILED;

	bnx2_reset_nic(bp, BNX2_DRV_MSG_CODE_RESET);
	spin_lock_bh(&bp->phy_lock);
	bnx2_init_phy(bp, 1);
	spin_unlock_bh(&bp->phy_lock);
	if (bnx2_run_loopback(bp, BNX2_MAC_LOOPBACK))
		rc |= BNX2_MAC_LOOPBACK_FAILED;
	if (bnx2_run_loopback(bp, BNX2_PHY_LOOPBACK))
		rc |= BNX2_PHY_LOOPBACK_FAILED;
	return rc;
}