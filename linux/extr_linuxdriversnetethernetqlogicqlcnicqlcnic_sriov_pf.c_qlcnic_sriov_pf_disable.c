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
struct qlcnic_adapter {int /*<<< orphan*/  portnum; int /*<<< orphan*/  netdev; int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  netdev_info (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_disable_sriov (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qlcnic_sriov_enable_check (struct qlcnic_adapter*) ; 
 int /*<<< orphan*/  qlcnic_sriov_pf_check (struct qlcnic_adapter*) ; 

void qlcnic_sriov_pf_disable(struct qlcnic_adapter *adapter)
{
	if (!qlcnic_sriov_pf_check(adapter))
		return;

	if (!qlcnic_sriov_enable_check(adapter))
		return;

	pci_disable_sriov(adapter->pdev);
	netdev_info(adapter->netdev,
		    "SR-IOV is disabled successfully on port %d\n",
		    adapter->portnum);
}