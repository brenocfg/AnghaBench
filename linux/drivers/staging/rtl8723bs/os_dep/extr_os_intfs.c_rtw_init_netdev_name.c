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
struct net_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ dev_alloc_name (struct net_device*,char const*) ; 
 int /*<<< orphan*/  netif_carrier_off (struct net_device*) ; 
 int /*<<< orphan*/  pr_err (char*,char const*) ; 

int rtw_init_netdev_name(struct net_device *pnetdev, const char *ifname)
{
	if (dev_alloc_name(pnetdev, ifname) < 0) {
		pr_err("dev_alloc_name, fail for %s\n", ifname);
		return 1;
	}
	netif_carrier_off(pnetdev);
	/* rtw_netif_stop_queue(pnetdev); */

	return 0;
}