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
 int /*<<< orphan*/  __nixge_hw_set_mac_address (struct net_device*) ; 
 int eth_mac_addr (struct net_device*,void*) ; 

__attribute__((used)) static int nixge_net_set_mac_address(struct net_device *ndev, void *p)
{
	int err;

	err = eth_mac_addr(ndev, p);
	if (!err)
		__nixge_hw_set_mac_address(ndev);

	return err;
}