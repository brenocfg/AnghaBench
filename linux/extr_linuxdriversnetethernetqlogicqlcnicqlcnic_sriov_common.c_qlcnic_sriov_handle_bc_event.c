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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct qlcnic_vf_info {int /*<<< orphan*/  ch_free_cmpl; int /*<<< orphan*/  pci_func; } ;
struct qlcnic_sriov {struct qlcnic_vf_info* vf_info; } ;
struct qlcnic_adapter {TYPE_1__* ahw; } ;
struct TYPE_2__ {struct qlcnic_sriov* sriov; } ;

/* Variables and functions */
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 scalar_t__ qlcnic_sriov_bc_msg_check (int /*<<< orphan*/ ) ; 
 scalar_t__ qlcnic_sriov_channel_free_check (int /*<<< orphan*/ ) ; 
 scalar_t__ qlcnic_sriov_flr_check (int /*<<< orphan*/ ) ; 
 int qlcnic_sriov_func_to_index (struct qlcnic_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qlcnic_sriov_handle_flr_event (struct qlcnic_sriov*,struct qlcnic_vf_info*) ; 
 int /*<<< orphan*/  qlcnic_sriov_handle_msg_event (struct qlcnic_sriov*,struct qlcnic_vf_info*) ; 
 int /*<<< orphan*/  qlcnic_sriov_target_func_id (int /*<<< orphan*/ ) ; 

void qlcnic_sriov_handle_bc_event(struct qlcnic_adapter *adapter, u32 event)
{
	struct qlcnic_vf_info *vf;
	struct qlcnic_sriov *sriov;
	int index;
	u8 pci_func;

	sriov = adapter->ahw->sriov;
	pci_func = qlcnic_sriov_target_func_id(event);
	index = qlcnic_sriov_func_to_index(adapter, pci_func);

	if (index < 0)
		return;

	vf = &sriov->vf_info[index];
	vf->pci_func = pci_func;

	if (qlcnic_sriov_channel_free_check(event))
		complete(&vf->ch_free_cmpl);

	if (qlcnic_sriov_flr_check(event)) {
		qlcnic_sriov_handle_flr_event(sriov, vf);
		return;
	}

	if (qlcnic_sriov_bc_msg_check(event))
		qlcnic_sriov_handle_msg_event(sriov, vf);
}