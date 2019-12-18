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
struct vortex_private {scalar_t__ enable_wol; } ;
struct net_device {int dummy; } ;
struct ethtool_wolinfo {int /*<<< orphan*/  wolopts; int /*<<< orphan*/  supported; } ;

/* Variables and functions */
 int /*<<< orphan*/  VORTEX_PCI (struct vortex_private*) ; 
 int /*<<< orphan*/  WAKE_MAGIC ; 
 struct vortex_private* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void vortex_get_wol(struct net_device *dev, struct ethtool_wolinfo *wol)
{
	struct vortex_private *vp = netdev_priv(dev);

	if (!VORTEX_PCI(vp))
		return;

	wol->supported = WAKE_MAGIC;

	wol->wolopts = 0;
	if (vp->enable_wol)
		wol->wolopts |= WAKE_MAGIC;
}