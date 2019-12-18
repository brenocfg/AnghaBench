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
typedef  int /*<<< orphan*/  u8 ;
struct wiphy {int dummy; } ;
struct virt_wifi_netdev_priv {int /*<<< orphan*/  is_connected; } ;
struct station_info {int dummy; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fake_router_bssid ; 
 struct virt_wifi_netdev_priv* netdev_priv (struct net_device*) ; 
 int virt_wifi_get_station (struct wiphy*,struct net_device*,int /*<<< orphan*/ ,struct station_info*) ; 
 int /*<<< orphan*/  wiphy_debug (struct wiphy*,char*) ; 

__attribute__((used)) static int virt_wifi_dump_station(struct wiphy *wiphy, struct net_device *dev,
				  int idx, u8 *mac, struct station_info *sinfo)
{
	struct virt_wifi_netdev_priv *priv = netdev_priv(dev);

	wiphy_debug(wiphy, "dump_station\n");

	if (idx != 0 || !priv->is_connected)
		return -ENOENT;

	ether_addr_copy(mac, fake_router_bssid);
	return virt_wifi_get_station(wiphy, dev, fake_router_bssid, sinfo);
}