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
struct bnx2 {int phy_flags; int /*<<< orphan*/  phy_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2_DRV_MSG_CODE_RESET ; 
 int BNX2_PHY_FLAG_REMOTE_PHY_CAP ; 
 int /*<<< orphan*/  bnx2_init_phy (struct bnx2*,int) ; 
 int /*<<< orphan*/  bnx2_remote_phy_event (struct bnx2*) ; 
 int bnx2_reset_nic (struct bnx2*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnx2_set_link (struct bnx2*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
bnx2_init_nic(struct bnx2 *bp, int reset_phy)
{
	int rc;

	if ((rc = bnx2_reset_nic(bp, BNX2_DRV_MSG_CODE_RESET)) != 0)
		return rc;

	spin_lock_bh(&bp->phy_lock);
	bnx2_init_phy(bp, reset_phy);
	bnx2_set_link(bp);
	if (bp->phy_flags & BNX2_PHY_FLAG_REMOTE_PHY_CAP)
		bnx2_remote_phy_event(bp);
	spin_unlock_bh(&bp->phy_lock);
	return 0;
}