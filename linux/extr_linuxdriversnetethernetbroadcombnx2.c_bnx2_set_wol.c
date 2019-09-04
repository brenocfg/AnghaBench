#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct net_device {int dummy; } ;
struct ethtool_wolinfo {int wolopts; } ;
struct bnx2 {int flags; int wol; TYPE_1__* pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int BNX2_FLAG_NO_WOL ; 
 int EINVAL ; 
 int WAKE_MAGIC ; 
 int /*<<< orphan*/  device_set_wakeup_enable (int /*<<< orphan*/ *,int) ; 
 struct bnx2* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int
bnx2_set_wol(struct net_device *dev, struct ethtool_wolinfo *wol)
{
	struct bnx2 *bp = netdev_priv(dev);

	if (wol->wolopts & ~WAKE_MAGIC)
		return -EINVAL;

	if (wol->wolopts & WAKE_MAGIC) {
		if (bp->flags & BNX2_FLAG_NO_WOL)
			return -EINVAL;

		bp->wol = 1;
	}
	else {
		bp->wol = 0;
	}

	device_set_wakeup_enable(&bp->pdev->dev, bp->wol);

	return 0;
}