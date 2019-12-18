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
struct net_device {int dummy; } ;
struct bnx2 {int autoneg; int phy_flags; int serdes_an_pending; int /*<<< orphan*/  phy_lock; int /*<<< orphan*/  mii_bmcr; scalar_t__ current_interval; int /*<<< orphan*/  timer; int /*<<< orphan*/  phy_port; } ;

/* Variables and functions */
 int AUTONEG_SPEED ; 
 int BMCR_ANENABLE ; 
 int BMCR_ANRESTART ; 
 int BMCR_LOOPBACK ; 
 int BNX2_PHY_FLAG_REMOTE_PHY_CAP ; 
 int BNX2_PHY_FLAG_SERDES ; 
 scalar_t__ BNX2_SERDES_AN_TIMEOUT ; 
 int EAGAIN ; 
 int EINVAL ; 
 int /*<<< orphan*/  bnx2_read_phy (struct bnx2*,int /*<<< orphan*/ ,int*) ; 
 int bnx2_setup_remote_phy (struct bnx2*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnx2_write_phy (struct bnx2*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  msleep (int) ; 
 struct bnx2* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_running (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
bnx2_nway_reset(struct net_device *dev)
{
	struct bnx2 *bp = netdev_priv(dev);
	u32 bmcr;

	if (!netif_running(dev))
		return -EAGAIN;

	if (!(bp->autoneg & AUTONEG_SPEED)) {
		return -EINVAL;
	}

	spin_lock_bh(&bp->phy_lock);

	if (bp->phy_flags & BNX2_PHY_FLAG_REMOTE_PHY_CAP) {
		int rc;

		rc = bnx2_setup_remote_phy(bp, bp->phy_port);
		spin_unlock_bh(&bp->phy_lock);
		return rc;
	}

	/* Force a link down visible on the other side */
	if (bp->phy_flags & BNX2_PHY_FLAG_SERDES) {
		bnx2_write_phy(bp, bp->mii_bmcr, BMCR_LOOPBACK);
		spin_unlock_bh(&bp->phy_lock);

		msleep(20);

		spin_lock_bh(&bp->phy_lock);

		bp->current_interval = BNX2_SERDES_AN_TIMEOUT;
		bp->serdes_an_pending = 1;
		mod_timer(&bp->timer, jiffies + bp->current_interval);
	}

	bnx2_read_phy(bp, bp->mii_bmcr, &bmcr);
	bmcr &= ~BMCR_LOOPBACK;
	bnx2_write_phy(bp, bp->mii_bmcr, bmcr | BMCR_ANRESTART | BMCR_ANENABLE);

	spin_unlock_bh(&bp->phy_lock);

	return 0;
}