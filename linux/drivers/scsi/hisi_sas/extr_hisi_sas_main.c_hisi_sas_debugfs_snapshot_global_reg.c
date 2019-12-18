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
typedef  int /*<<< orphan*/  u32 ;
struct hisi_sas_hw {struct hisi_sas_debugfs_reg** debugfs_reg_array; } ;
struct hisi_sas_debugfs_reg {int count; int /*<<< orphan*/  (* read_global_reg ) (struct hisi_hba*,int) ;} ;
struct hisi_hba {struct hisi_sas_hw* hw; int /*<<< orphan*/ ** debugfs_regs; } ;

/* Variables and functions */
 size_t DEBUGFS_GLOBAL ; 
 int /*<<< orphan*/  stub1 (struct hisi_hba*,int) ; 

__attribute__((used)) static void hisi_sas_debugfs_snapshot_global_reg(struct hisi_hba *hisi_hba)
{
	u32 *databuf = hisi_hba->debugfs_regs[DEBUGFS_GLOBAL];
	const struct hisi_sas_hw *hw = hisi_hba->hw;
	const struct hisi_sas_debugfs_reg *global =
			hw->debugfs_reg_array[DEBUGFS_GLOBAL];
	int i;

	for (i = 0; i < global->count; i++, databuf++)
		*databuf = global->read_global_reg(hisi_hba, 4 * i);
}