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
struct TYPE_2__ {int /*<<< orphan*/  wolopts; int /*<<< orphan*/  supported; } ;
struct tulip_private {TYPE_1__ wolinfo; } ;
struct net_device {int dummy; } ;
struct ethtool_wolinfo {int /*<<< orphan*/  wolopts; int /*<<< orphan*/  supported; } ;

/* Variables and functions */
 struct tulip_private* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void tulip_ethtool_get_wol(struct net_device *dev,
				  struct ethtool_wolinfo *wolinfo)
{
	struct tulip_private *tp = netdev_priv(dev);

	wolinfo->supported = tp->wolinfo.supported;
	wolinfo->wolopts = tp->wolinfo.wolopts;
	return;
}