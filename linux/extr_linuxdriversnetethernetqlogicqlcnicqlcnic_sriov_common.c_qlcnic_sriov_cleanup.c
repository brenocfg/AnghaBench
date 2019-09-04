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

/* Variables and functions */
 int /*<<< orphan*/  __QLCNIC_SRIOV_ENABLE ; 
 int /*<<< orphan*/  qlcnic_sriov_free_vlans (struct qlcnic_adapter*) ; 
 scalar_t__ qlcnic_sriov_pf_check (struct qlcnic_adapter*) ; 
 int /*<<< orphan*/  qlcnic_sriov_pf_cleanup (struct qlcnic_adapter*) ; 
 scalar_t__ qlcnic_sriov_vf_check (struct qlcnic_adapter*) ; 
 int /*<<< orphan*/  qlcnic_sriov_vf_cleanup (struct qlcnic_adapter*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void qlcnic_sriov_cleanup(struct qlcnic_adapter *adapter)
{
	if (!test_bit(__QLCNIC_SRIOV_ENABLE, &adapter->state))
		return;

	qlcnic_sriov_free_vlans(adapter);

	if (qlcnic_sriov_pf_check(adapter))
		qlcnic_sriov_pf_cleanup(adapter);

	if (qlcnic_sriov_vf_check(adapter))
		qlcnic_sriov_vf_cleanup(adapter);
}