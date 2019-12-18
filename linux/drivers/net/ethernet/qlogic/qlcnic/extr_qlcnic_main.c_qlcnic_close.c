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
struct qlcnic_adapter {int dummy; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __qlcnic_down (struct qlcnic_adapter*,struct net_device*) ; 
 struct qlcnic_adapter* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int qlcnic_close(struct net_device *netdev)
{
	struct qlcnic_adapter *adapter = netdev_priv(netdev);

	__qlcnic_down(adapter, netdev);

	return 0;
}