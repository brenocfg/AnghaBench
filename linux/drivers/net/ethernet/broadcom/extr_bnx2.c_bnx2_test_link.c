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
typedef  int u32 ;
struct bnx2 {int phy_flags; int /*<<< orphan*/  phy_lock; int /*<<< orphan*/  mii_bmsr1; scalar_t__ link_up; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int BMSR_LSTATUS ; 
 int BNX2_PHY_FLAG_REMOTE_PHY_CAP ; 
 int ENODEV ; 
 int /*<<< orphan*/  bnx2_disable_bmsr1 (struct bnx2*) ; 
 int /*<<< orphan*/  bnx2_enable_bmsr1 (struct bnx2*) ; 
 int /*<<< orphan*/  bnx2_read_phy (struct bnx2*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  netif_running (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
bnx2_test_link(struct bnx2 *bp)
{
	u32 bmsr;

	if (!netif_running(bp->dev))
		return -ENODEV;

	if (bp->phy_flags & BNX2_PHY_FLAG_REMOTE_PHY_CAP) {
		if (bp->link_up)
			return 0;
		return -ENODEV;
	}
	spin_lock_bh(&bp->phy_lock);
	bnx2_enable_bmsr1(bp);
	bnx2_read_phy(bp, bp->mii_bmsr1, &bmsr);
	bnx2_read_phy(bp, bp->mii_bmsr1, &bmsr);
	bnx2_disable_bmsr1(bp);
	spin_unlock_bh(&bp->phy_lock);

	if (bmsr & BMSR_LSTATUS) {
		return 0;
	}
	return -ENODEV;
}