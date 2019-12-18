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
struct hisi_hba {TYPE_1__* hw; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* snapshot_restore ) (struct hisi_hba*) ;int /*<<< orphan*/  (* snapshot_prepare ) (struct hisi_hba*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  hisi_sas_debugfs_create_files (struct hisi_hba*) ; 
 int /*<<< orphan*/  hisi_sas_debugfs_snapshot_axi_reg (struct hisi_hba*) ; 
 int /*<<< orphan*/  hisi_sas_debugfs_snapshot_cq_reg (struct hisi_hba*) ; 
 int /*<<< orphan*/  hisi_sas_debugfs_snapshot_dq_reg (struct hisi_hba*) ; 
 int /*<<< orphan*/  hisi_sas_debugfs_snapshot_global_reg (struct hisi_hba*) ; 
 int /*<<< orphan*/  hisi_sas_debugfs_snapshot_iost_reg (struct hisi_hba*) ; 
 int /*<<< orphan*/  hisi_sas_debugfs_snapshot_itct_reg (struct hisi_hba*) ; 
 int /*<<< orphan*/  hisi_sas_debugfs_snapshot_port_reg (struct hisi_hba*) ; 
 int /*<<< orphan*/  hisi_sas_debugfs_snapshot_ras_reg (struct hisi_hba*) ; 
 int /*<<< orphan*/  stub1 (struct hisi_hba*) ; 
 int /*<<< orphan*/  stub2 (struct hisi_hba*) ; 

__attribute__((used)) static void hisi_sas_debugfs_snapshot_regs(struct hisi_hba *hisi_hba)
{
	hisi_hba->hw->snapshot_prepare(hisi_hba);

	hisi_sas_debugfs_snapshot_global_reg(hisi_hba);
	hisi_sas_debugfs_snapshot_port_reg(hisi_hba);
	hisi_sas_debugfs_snapshot_axi_reg(hisi_hba);
	hisi_sas_debugfs_snapshot_ras_reg(hisi_hba);
	hisi_sas_debugfs_snapshot_cq_reg(hisi_hba);
	hisi_sas_debugfs_snapshot_dq_reg(hisi_hba);
	hisi_sas_debugfs_snapshot_itct_reg(hisi_hba);
	hisi_sas_debugfs_snapshot_iost_reg(hisi_hba);

	hisi_sas_debugfs_create_files(hisi_hba);

	hisi_hba->hw->snapshot_restore(hisi_hba);
}