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
 int /*<<< orphan*/  ave_macaddr_init (struct net_device*) ; 
 int eth_mac_addr (struct net_device*,void*) ; 

__attribute__((used)) static int ave_set_mac_address(struct net_device *ndev, void *p)
{
	int ret = eth_mac_addr(ndev, p);

	if (ret)
		return ret;

	ave_macaddr_init(ndev);

	return 0;
}