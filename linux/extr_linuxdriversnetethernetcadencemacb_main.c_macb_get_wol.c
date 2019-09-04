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
struct net_device {int dummy; } ;
struct macb {int wol; } ;
struct ethtool_wolinfo {scalar_t__ wolopts; scalar_t__ supported; } ;

/* Variables and functions */
 int MACB_WOL_ENABLED ; 
 int MACB_WOL_HAS_MAGIC_PACKET ; 
 scalar_t__ WAKE_MAGIC ; 
 struct macb* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void macb_get_wol(struct net_device *netdev, struct ethtool_wolinfo *wol)
{
	struct macb *bp = netdev_priv(netdev);

	wol->supported = 0;
	wol->wolopts = 0;

	if (bp->wol & MACB_WOL_HAS_MAGIC_PACKET) {
		wol->supported = WAKE_MAGIC;

		if (bp->wol & MACB_WOL_ENABLED)
			wol->wolopts |= WAKE_MAGIC;
	}
}