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
struct wlandevice {int /*<<< orphan*/  netdev; int /*<<< orphan*/  nsdname; int /*<<< orphan*/  (* tx_timeout ) (struct wlandevice*) ;} ;
struct net_device {struct wlandevice* ml_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  netdev_warn (struct net_device*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_wake_queue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct wlandevice*) ; 

__attribute__((used)) static void p80211knetdev_tx_timeout(struct net_device *netdev)
{
	struct wlandevice *wlandev = netdev->ml_priv;

	if (wlandev->tx_timeout) {
		wlandev->tx_timeout(wlandev);
	} else {
		netdev_warn(netdev, "Implement tx_timeout for %s\n",
			    wlandev->nsdname);
		netif_wake_queue(wlandev->netdev);
	}
}