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
struct wlandevice {int hwremoved; scalar_t__ state; int /*<<< orphan*/  netdev; } ;

/* Variables and functions */
 scalar_t__ WLAN_DEVICE_OPEN ; 
 int /*<<< orphan*/  netif_device_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_stop_queue (int /*<<< orphan*/ ) ; 

void p80211netdev_hwremoved(struct wlandevice *wlandev)
{
	wlandev->hwremoved = 1;
	if (wlandev->state == WLAN_DEVICE_OPEN)
		netif_stop_queue(wlandev->netdev);

	netif_device_detach(wlandev->netdev);
}