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
typedef  int u16 ;
struct qlcnic_vf_info {int /*<<< orphan*/  state; int /*<<< orphan*/  flr_work; scalar_t__ tx_ctx_id; scalar_t__ rx_ctx_id; } ;
struct qlcnic_sriov {int num_vfs; struct qlcnic_vf_info* vf_info; } ;
struct qlcnic_hardware_context {int num_msix; int /*<<< orphan*/  pci_func; struct qlcnic_sriov* sriov; } ;
struct qlcnic_adapter {struct qlcnic_hardware_context* ahw; } ;

/* Variables and functions */
 int /*<<< orphan*/  QLCNIC_MBX_INTR_ENBL ; 
 int /*<<< orphan*/  QLCWRX (struct qlcnic_hardware_context*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  QLC_BC_VF_STATE ; 
 int /*<<< orphan*/  __qlcnic_sriov_process_flr (struct qlcnic_vf_info*) ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qlcnic_sriov_pf_reset_vport_handle (struct qlcnic_adapter*,int /*<<< orphan*/ ) ; 

void qlcnic_sriov_pf_reset(struct qlcnic_adapter *adapter)
{
	struct qlcnic_hardware_context *ahw = adapter->ahw;
	struct qlcnic_sriov *sriov = ahw->sriov;
	struct qlcnic_vf_info *vf;
	u16 num_vfs = sriov->num_vfs;
	int i;

	for (i = 0; i < num_vfs; i++) {
		vf = &sriov->vf_info[i];
		vf->rx_ctx_id = 0;
		vf->tx_ctx_id = 0;
		cancel_work_sync(&vf->flr_work);
		__qlcnic_sriov_process_flr(vf);
		clear_bit(QLC_BC_VF_STATE, &vf->state);
	}

	qlcnic_sriov_pf_reset_vport_handle(adapter, ahw->pci_func);
	QLCWRX(ahw, QLCNIC_MBX_INTR_ENBL, (ahw->num_msix - 1) << 8);
}