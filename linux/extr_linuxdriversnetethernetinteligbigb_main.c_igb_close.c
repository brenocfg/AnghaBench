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
struct net_device {scalar_t__ dismantle; } ;

/* Variables and functions */
 int __igb_close (struct net_device*,int) ; 
 scalar_t__ netif_device_present (struct net_device*) ; 

int igb_close(struct net_device *netdev)
{
	if (netif_device_present(netdev) || netdev->dismantle)
		return __igb_close(netdev, false);
	return 0;
}