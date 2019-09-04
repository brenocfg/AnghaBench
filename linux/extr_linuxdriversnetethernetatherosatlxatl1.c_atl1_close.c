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
struct atl1_adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  atl1_down (struct atl1_adapter*) ; 
 int /*<<< orphan*/  atl1_free_ring_resources (struct atl1_adapter*) ; 
 struct atl1_adapter* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int atl1_close(struct net_device *netdev)
{
	struct atl1_adapter *adapter = netdev_priv(netdev);
	atl1_down(adapter);
	atl1_free_ring_resources(adapter);
	return 0;
}