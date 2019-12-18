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
struct atl1c_adapter {struct net_device* netdev; } ;

/* Variables and functions */
 int EIO ; 
 int ENOMEM ; 
 int atl1c_alloc_rx_buffer (struct atl1c_adapter*) ; 
 scalar_t__ atl1c_configure_mac (struct atl1c_adapter*) ; 
 int /*<<< orphan*/  atl1c_init_ring_ptrs (struct atl1c_adapter*) ; 
 int /*<<< orphan*/  atl1c_restore_vlan (struct atl1c_adapter*) ; 
 int /*<<< orphan*/  atl1c_set_multi (struct net_device*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int atl1c_configure(struct atl1c_adapter *adapter)
{
	struct net_device *netdev = adapter->netdev;
	int num;

	atl1c_init_ring_ptrs(adapter);
	atl1c_set_multi(netdev);
	atl1c_restore_vlan(adapter);

	num = atl1c_alloc_rx_buffer(adapter);
	if (unlikely(num == 0))
		return -ENOMEM;

	if (atl1c_configure_mac(adapter))
		return -EIO;

	return 0;
}