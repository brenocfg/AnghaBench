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
struct wiphy {int dummy; } ;
struct usbnet {int /*<<< orphan*/  net; } ;
struct rndis_wlan_private {scalar_t__ device_type; int /*<<< orphan*/  scan_work; int /*<<< orphan*/  workqueue; struct cfg80211_scan_request* scan_request; } ;
struct net_device {int dummy; } ;
struct cfg80211_scan_request {TYPE_1__* wdev; } ;
struct TYPE_2__ {struct net_device* netdev; } ;

/* Variables and functions */
 int EBUSY ; 
 int HZ ; 
 scalar_t__ RNDIS_BCM4320A ; 
 int SCAN_DELAY_JIFFIES ; 
 struct rndis_wlan_private* get_rndis_wlan_priv (struct usbnet*) ; 
 int /*<<< orphan*/  netdev_dbg (int /*<<< orphan*/ ,char*) ; 
 struct usbnet* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  rndis_check_bssid_list (struct usbnet*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int rndis_start_bssid_list_scan (struct usbnet*) ; 

__attribute__((used)) static int rndis_scan(struct wiphy *wiphy,
			struct cfg80211_scan_request *request)
{
	struct net_device *dev = request->wdev->netdev;
	struct usbnet *usbdev = netdev_priv(dev);
	struct rndis_wlan_private *priv = get_rndis_wlan_priv(usbdev);
	int ret;
	int delay = SCAN_DELAY_JIFFIES;

	netdev_dbg(usbdev->net, "cfg80211.scan\n");

	/* Get current bssid list from device before new scan, as new scan
	 * clears internal bssid list.
	 */
	rndis_check_bssid_list(usbdev, NULL, NULL);

	if (priv->scan_request && priv->scan_request != request)
		return -EBUSY;

	priv->scan_request = request;

	ret = rndis_start_bssid_list_scan(usbdev);
	if (ret == 0) {
		if (priv->device_type == RNDIS_BCM4320A)
			delay = HZ;

		/* Wait before retrieving scan results from device */
		queue_delayed_work(priv->workqueue, &priv->scan_work, delay);
	}

	return ret;
}