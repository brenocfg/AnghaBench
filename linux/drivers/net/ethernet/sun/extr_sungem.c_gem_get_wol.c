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
struct gem {int /*<<< orphan*/  wake_on_lan; scalar_t__ has_wol; } ;
struct ethtool_wolinfo {int /*<<< orphan*/  wolopts; scalar_t__ supported; } ;

/* Variables and functions */
 scalar_t__ WOL_SUPPORTED_MASK ; 
 struct gem* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void gem_get_wol(struct net_device *dev, struct ethtool_wolinfo *wol)
{
	struct gem *gp = netdev_priv(dev);

	/* Add more when I understand how to program the chip */
	if (gp->has_wol) {
		wol->supported = WOL_SUPPORTED_MASK;
		wol->wolopts = gp->wake_on_lan;
	} else {
		wol->supported = 0;
		wol->wolopts = 0;
	}
}