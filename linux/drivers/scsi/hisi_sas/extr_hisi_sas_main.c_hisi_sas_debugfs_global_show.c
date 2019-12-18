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
struct seq_file {struct hisi_hba* private; } ;
struct hisi_sas_hw {void** debugfs_reg_array; } ;
struct hisi_hba {int /*<<< orphan*/ * debugfs_regs; struct hisi_sas_hw* hw; } ;

/* Variables and functions */
 size_t DEBUGFS_GLOBAL ; 
 int /*<<< orphan*/  hisi_sas_debugfs_print_reg (int /*<<< orphan*/ ,void const*,struct seq_file*) ; 

__attribute__((used)) static int hisi_sas_debugfs_global_show(struct seq_file *s, void *p)
{
	struct hisi_hba *hisi_hba = s->private;
	const struct hisi_sas_hw *hw = hisi_hba->hw;
	const void *reg_global = hw->debugfs_reg_array[DEBUGFS_GLOBAL];

	hisi_sas_debugfs_print_reg(hisi_hba->debugfs_regs[DEBUGFS_GLOBAL],
				   reg_global, s);

	return 0;
}