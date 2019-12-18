#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct qlcnic_sriov {int num_vfs; int num_allowed_vlans; } ;
struct qlcnic_info {int max_rx_mcast_mac_filters; } ;
struct qlcnic_adapter {int /*<<< orphan*/  netdev; TYPE_1__* ahw; } ;
struct TYPE_2__ {struct qlcnic_sriov* sriov; } ;

/* Variables and functions */
 int QLCNIC_SRIOV_VF_MAX_MAC ; 
 int /*<<< orphan*/  netdev_info (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ qlcnic_83xx_pf_check (struct qlcnic_adapter*) ; 

__attribute__((used)) static void qlcnic_sriov_set_vf_max_vlan(struct qlcnic_adapter *adapter,
					 struct qlcnic_info *npar_info)
{
	struct qlcnic_sriov *sriov = adapter->ahw->sriov;
	int temp, total_fn;

	temp = npar_info->max_rx_mcast_mac_filters;
	total_fn = sriov->num_vfs + 1;

	temp = temp / (QLCNIC_SRIOV_VF_MAX_MAC * total_fn);
	sriov->num_allowed_vlans = temp - 1;

	if (qlcnic_83xx_pf_check(adapter))
		sriov->num_allowed_vlans = 1;

	netdev_info(adapter->netdev, "Max Guest VLANs supported per VF = %d\n",
		    sriov->num_allowed_vlans);
}