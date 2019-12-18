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
struct usbnet {struct aqc111_data* driver_priv; } ;
struct net_device {int dummy; } ;
struct ethtool_wolinfo {int /*<<< orphan*/  wolopts; int /*<<< orphan*/  supported; } ;
struct aqc111_data {int wol_flags; } ;

/* Variables and functions */
 int AQ_WOL_FLAG_MP ; 
 int /*<<< orphan*/  WAKE_MAGIC ; 
 struct usbnet* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void aqc111_get_wol(struct net_device *net,
			   struct ethtool_wolinfo *wolinfo)
{
	struct usbnet *dev = netdev_priv(net);
	struct aqc111_data *aqc111_data = dev->driver_priv;

	wolinfo->supported = WAKE_MAGIC;
	wolinfo->wolopts = 0;

	if (aqc111_data->wol_flags & AQ_WOL_FLAG_MP)
		wolinfo->wolopts |= WAKE_MAGIC;
}