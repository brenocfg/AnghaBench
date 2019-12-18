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
struct igb_adapter {int /*<<< orphan*/  vfs_allocated_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  igb_del_mac_filter (struct igb_adapter*,unsigned char const*,int /*<<< orphan*/ ) ; 
 struct igb_adapter* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int igb_uc_unsync(struct net_device *netdev, const unsigned char *addr)
{
	struct igb_adapter *adapter = netdev_priv(netdev);

	igb_del_mac_filter(adapter, addr, adapter->vfs_allocated_count);

	return 0;
}