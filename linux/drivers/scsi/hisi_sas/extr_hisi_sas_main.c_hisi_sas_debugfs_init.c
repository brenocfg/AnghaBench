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
struct hisi_hba {int /*<<< orphan*/  debugfs_dir; struct device* dev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  debugfs_create_dir (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugfs_create_file (char*,int,int /*<<< orphan*/ ,struct hisi_hba*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debugfs_remove_recursive (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*) ; 
 int /*<<< orphan*/  dev_name (struct device*) ; 
 scalar_t__ hisi_sas_debugfs_alloc (struct hisi_hba*) ; 
 int /*<<< orphan*/  hisi_sas_debugfs_bist_init (struct hisi_hba*) ; 
 int /*<<< orphan*/  hisi_sas_debugfs_dir ; 
 int /*<<< orphan*/  hisi_sas_debugfs_trigger_dump_fops ; 

void hisi_sas_debugfs_init(struct hisi_hba *hisi_hba)
{
	struct device *dev = hisi_hba->dev;

	hisi_hba->debugfs_dir = debugfs_create_dir(dev_name(dev),
						   hisi_sas_debugfs_dir);
	debugfs_create_file("trigger_dump", 0600,
			    hisi_hba->debugfs_dir,
			    hisi_hba,
			    &hisi_sas_debugfs_trigger_dump_fops);

	/* create bist structures */
	hisi_sas_debugfs_bist_init(hisi_hba);

	if (hisi_sas_debugfs_alloc(hisi_hba)) {
		debugfs_remove_recursive(hisi_hba->debugfs_dir);
		dev_dbg(dev, "failed to init debugfs!\n");
	}
}