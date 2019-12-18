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
struct hisi_hba {int queue_count; int n_phy; int /*<<< orphan*/ * debugfs_port_reg; int /*<<< orphan*/ * debugfs_regs; int /*<<< orphan*/ * debugfs_complete_hdr; int /*<<< orphan*/ * debugfs_cmd_hdr; int /*<<< orphan*/  debugfs_iost; int /*<<< orphan*/  debugfs_itct_cache; int /*<<< orphan*/  debugfs_iost_cache; struct device* dev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int DEBUGFS_REGS_NUM ; 
 int /*<<< orphan*/  devm_kfree (struct device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hisi_sas_debugfs_release(struct hisi_hba *hisi_hba)
{
	struct device *dev = hisi_hba->dev;
	int i;

	devm_kfree(dev, hisi_hba->debugfs_iost_cache);
	devm_kfree(dev, hisi_hba->debugfs_itct_cache);
	devm_kfree(dev, hisi_hba->debugfs_iost);

	for (i = 0; i < hisi_hba->queue_count; i++)
		devm_kfree(dev, hisi_hba->debugfs_cmd_hdr[i]);

	for (i = 0; i < hisi_hba->queue_count; i++)
		devm_kfree(dev, hisi_hba->debugfs_complete_hdr[i]);

	for (i = 0; i < DEBUGFS_REGS_NUM; i++)
		devm_kfree(dev, hisi_hba->debugfs_regs[i]);

	for (i = 0; i < hisi_hba->n_phy; i++)
		devm_kfree(dev, hisi_hba->debugfs_port_reg[i]);
}