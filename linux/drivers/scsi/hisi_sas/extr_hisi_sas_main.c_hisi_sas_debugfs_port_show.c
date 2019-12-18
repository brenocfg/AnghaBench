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
typedef  int /*<<< orphan*/  u32 ;
struct seq_file {struct hisi_sas_phy* private; } ;
struct TYPE_2__ {size_t id; } ;
struct hisi_sas_phy {TYPE_1__ sas_phy; struct hisi_hba* hisi_hba; } ;
struct hisi_sas_hw {struct hisi_sas_debugfs_reg* debugfs_reg_port; } ;
struct hisi_sas_debugfs_reg {int dummy; } ;
struct hisi_hba {int /*<<< orphan*/ ** debugfs_port_reg; struct hisi_sas_hw* hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  hisi_sas_debugfs_print_reg (int /*<<< orphan*/ *,struct hisi_sas_debugfs_reg const*,struct seq_file*) ; 

__attribute__((used)) static int hisi_sas_debugfs_port_show(struct seq_file *s, void *p)
{
	struct hisi_sas_phy *phy = s->private;
	struct hisi_hba *hisi_hba = phy->hisi_hba;
	const struct hisi_sas_hw *hw = hisi_hba->hw;
	const struct hisi_sas_debugfs_reg *reg_port = hw->debugfs_reg_port;
	u32 *databuf = hisi_hba->debugfs_port_reg[phy->sas_phy.id];

	hisi_sas_debugfs_print_reg(databuf, reg_port, s);

	return 0;
}