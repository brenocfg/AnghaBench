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
struct macb {int wol; TYPE_1__* pdev; } ;
struct ethtool_wolinfo {int wolopts; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int MACB_WOL_ENABLED ; 
 int MACB_WOL_HAS_MAGIC_PACKET ; 
 int WAKE_MAGIC ; 
 int /*<<< orphan*/  device_set_wakeup_enable (int /*<<< orphan*/ *,int) ; 
 struct macb* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int macb_set_wol(struct net_device *netdev, struct ethtool_wolinfo *wol)
{
	struct macb *bp = netdev_priv(netdev);

	if (!(bp->wol & MACB_WOL_HAS_MAGIC_PACKET) ||
	    (wol->wolopts & ~WAKE_MAGIC))
		return -EOPNOTSUPP;

	if (wol->wolopts & WAKE_MAGIC)
		bp->wol |= MACB_WOL_ENABLED;
	else
		bp->wol &= ~MACB_WOL_ENABLED;

	device_set_wakeup_enable(&bp->pdev->dev, bp->wol & MACB_WOL_ENABLED);

	return 0;
}