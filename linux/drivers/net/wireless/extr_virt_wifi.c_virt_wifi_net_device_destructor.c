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
struct net_device {int /*<<< orphan*/ * ieee80211_ptr; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void virt_wifi_net_device_destructor(struct net_device *dev)
{
	/* Delayed past dellink to allow nl80211 to react to the device being
	 * deleted.
	 */
	kfree(dev->ieee80211_ptr);
	dev->ieee80211_ptr = NULL;
	free_netdev(dev);
}