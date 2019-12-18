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
struct hisi_hba {int n_phy; int queue_count; struct hisi_hba* dq; struct hisi_hba* cq; struct hisi_hba* phy; struct dentry* debugfs_dump_dentry; struct dentry* debugfs_dir; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 struct dentry* debugfs_create_dir (char*,struct dentry*) ; 
 int /*<<< orphan*/  debugfs_create_file (char*,int,struct dentry*,struct hisi_hba*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hisi_sas_debugfs_axi_fops ; 
 int /*<<< orphan*/  hisi_sas_debugfs_cq_fops ; 
 int /*<<< orphan*/  hisi_sas_debugfs_dq_fops ; 
 int /*<<< orphan*/  hisi_sas_debugfs_global_fops ; 
 int /*<<< orphan*/  hisi_sas_debugfs_iost_cache_fops ; 
 int /*<<< orphan*/  hisi_sas_debugfs_iost_fops ; 
 int /*<<< orphan*/  hisi_sas_debugfs_itct_cache_fops ; 
 int /*<<< orphan*/  hisi_sas_debugfs_itct_fops ; 
 int /*<<< orphan*/  hisi_sas_debugfs_port_fops ; 
 int /*<<< orphan*/  hisi_sas_debugfs_ras_fops ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 

__attribute__((used)) static void hisi_sas_debugfs_create_files(struct hisi_hba *hisi_hba)
{
	struct dentry *dump_dentry;
	struct dentry *dentry;
	char name[256];
	int p;
	int c;
	int d;

	/* Create dump dir inside device dir */
	dump_dentry = debugfs_create_dir("dump", hisi_hba->debugfs_dir);
	hisi_hba->debugfs_dump_dentry = dump_dentry;

	debugfs_create_file("global", 0400, dump_dentry, hisi_hba,
			    &hisi_sas_debugfs_global_fops);

	/* Create port dir and files */
	dentry = debugfs_create_dir("port", dump_dentry);
	for (p = 0; p < hisi_hba->n_phy; p++) {
		snprintf(name, 256, "%d", p);

		debugfs_create_file(name, 0400, dentry, &hisi_hba->phy[p],
				    &hisi_sas_debugfs_port_fops);
	}

	/* Create CQ dir and files */
	dentry = debugfs_create_dir("cq", dump_dentry);
	for (c = 0; c < hisi_hba->queue_count; c++) {
		snprintf(name, 256, "%d", c);

		debugfs_create_file(name, 0400, dentry, &hisi_hba->cq[c],
				    &hisi_sas_debugfs_cq_fops);
	}

	/* Create DQ dir and files */
	dentry = debugfs_create_dir("dq", dump_dentry);
	for (d = 0; d < hisi_hba->queue_count; d++) {
		snprintf(name, 256, "%d", d);

		debugfs_create_file(name, 0400, dentry, &hisi_hba->dq[d],
				    &hisi_sas_debugfs_dq_fops);
	}

	debugfs_create_file("iost", 0400, dump_dentry, hisi_hba,
			    &hisi_sas_debugfs_iost_fops);

	debugfs_create_file("iost_cache", 0400, dump_dentry, hisi_hba,
			    &hisi_sas_debugfs_iost_cache_fops);

	debugfs_create_file("itct", 0400, dump_dentry, hisi_hba,
			    &hisi_sas_debugfs_itct_fops);

	debugfs_create_file("itct_cache", 0400, dump_dentry, hisi_hba,
			    &hisi_sas_debugfs_itct_cache_fops);

	debugfs_create_file("axi", 0400, dump_dentry, hisi_hba,
			    &hisi_sas_debugfs_axi_fops);

	debugfs_create_file("ras", 0400, dump_dentry, hisi_hba,
			    &hisi_sas_debugfs_ras_fops);

	return;
}