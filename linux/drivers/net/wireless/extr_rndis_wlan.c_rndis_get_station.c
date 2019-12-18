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
struct usbnet {int dummy; } ;
struct station_info {int dummy; } ;
struct rndis_wlan_private {int /*<<< orphan*/  bssid; struct usbnet* usbdev; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  ether_addr_equal (int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  rndis_fill_station_info (struct usbnet*,struct station_info*) ; 
 struct rndis_wlan_private* wiphy_priv (struct wiphy*) ; 

__attribute__((used)) static int rndis_get_station(struct wiphy *wiphy, struct net_device *dev,
			     const u8 *mac, struct station_info *sinfo)
{
	struct rndis_wlan_private *priv = wiphy_priv(wiphy);
	struct usbnet *usbdev = priv->usbdev;

	if (!ether_addr_equal(priv->bssid, mac))
		return -ENOENT;

	rndis_fill_station_info(usbdev, sinfo);

	return 0;
}