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
struct qlcnic_adapter {int /*<<< orphan*/  state; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __QLCNIC_FW_ATTACHED ; 
 int /*<<< orphan*/  __qlcnic_set_multi (struct net_device*,int /*<<< orphan*/ ) ; 
 struct qlcnic_adapter* netdev_priv (struct net_device*) ; 
 scalar_t__ qlcnic_sriov_vf_check (struct qlcnic_adapter*) ; 
 int /*<<< orphan*/  qlcnic_sriov_vf_set_multi (struct net_device*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void qlcnic_set_multi(struct net_device *netdev)
{
	struct qlcnic_adapter *adapter = netdev_priv(netdev);

	if (!test_bit(__QLCNIC_FW_ATTACHED, &adapter->state))
		return;

	if (qlcnic_sriov_vf_check(adapter))
		qlcnic_sriov_vf_set_multi(netdev);
	else
		__qlcnic_set_multi(netdev, 0);
}