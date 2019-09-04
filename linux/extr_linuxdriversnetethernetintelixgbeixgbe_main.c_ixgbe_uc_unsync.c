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
struct ixgbe_adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  VMDQ_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ixgbe_del_mac_filter (struct ixgbe_adapter*,unsigned char const*,int /*<<< orphan*/ ) ; 
 struct ixgbe_adapter* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int ixgbe_uc_unsync(struct net_device *netdev, const unsigned char *addr)
{
	struct ixgbe_adapter *adapter = netdev_priv(netdev);

	ixgbe_del_mac_filter(adapter, addr, VMDQ_P(0));

	return 0;
}