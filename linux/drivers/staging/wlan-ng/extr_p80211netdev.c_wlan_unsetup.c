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
struct wlandevice {int /*<<< orphan*/ * netdev; int /*<<< orphan*/  rx_bh; } ;
struct wireless_dev {scalar_t__ wiphy; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_netdev (int /*<<< orphan*/ *) ; 
 struct wireless_dev* netdev_priv (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tasklet_kill (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wlan_free_wiphy (scalar_t__) ; 

void wlan_unsetup(struct wlandevice *wlandev)
{
	struct wireless_dev *wdev;

	tasklet_kill(&wlandev->rx_bh);

	if (wlandev->netdev) {
		wdev = netdev_priv(wlandev->netdev);
		if (wdev->wiphy)
			wlan_free_wiphy(wdev->wiphy);
		free_netdev(wlandev->netdev);
		wlandev->netdev = NULL;
	}
}