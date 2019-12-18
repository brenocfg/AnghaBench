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
struct hisi_hba {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  DLVRY_QUEUE_ENABLE ; 
 int /*<<< orphan*/  HISI_SAS_REJECT_CMD_BIT ; 
 int /*<<< orphan*/  hisi_sas_kill_tasklets (struct hisi_hba*) ; 
 int /*<<< orphan*/  hisi_sas_write32 (struct hisi_hba*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_cmds_complete_timeout_v3_hw (struct hisi_hba*,int,int) ; 

__attribute__((used)) static void debugfs_snapshot_prepare_v3_hw(struct hisi_hba *hisi_hba)
{
	set_bit(HISI_SAS_REJECT_CMD_BIT, &hisi_hba->flags);

	hisi_sas_write32(hisi_hba, DLVRY_QUEUE_ENABLE, 0);

	wait_cmds_complete_timeout_v3_hw(hisi_hba, 100, 5000);

	hisi_sas_kill_tasklets(hisi_hba);
}