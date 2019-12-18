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
typedef  int /*<<< orphan*/  u16 ;
struct wiphy {int dummy; } ;
struct virt_wifi_netdev_priv {int is_connected; scalar_t__ being_deleted; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  cfg80211_disconnected (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 struct virt_wifi_netdev_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_off (struct net_device*) ; 
 int /*<<< orphan*/  virt_wifi_cancel_connect (struct net_device*) ; 
 int /*<<< orphan*/  wiphy_debug (struct wiphy*,char*) ; 

__attribute__((used)) static int virt_wifi_disconnect(struct wiphy *wiphy, struct net_device *netdev,
				u16 reason_code)
{
	struct virt_wifi_netdev_priv *priv = netdev_priv(netdev);

	if (priv->being_deleted)
		return -EBUSY;

	wiphy_debug(wiphy, "disconnect\n");
	virt_wifi_cancel_connect(netdev);

	cfg80211_disconnected(netdev, reason_code, NULL, 0, true, GFP_KERNEL);
	priv->is_connected = false;
	netif_carrier_off(netdev);

	return 0;
}