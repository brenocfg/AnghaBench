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
struct hisi_hba {int /*<<< orphan*/  debugfs_bist_linkrate; int /*<<< orphan*/  debugfs_bist_dentry; int /*<<< orphan*/  debugfs_bist_cnt; int /*<<< orphan*/  debugfs_dir; } ;

/* Variables and functions */
 int /*<<< orphan*/  SAS_LINK_RATE_1_5_GBPS ; 
 int /*<<< orphan*/  debugfs_create_dir (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugfs_create_file (char*,int,int /*<<< orphan*/ ,struct hisi_hba*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debugfs_create_u32 (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hisi_sas_debugfs_bist_code_mode_ops ; 
 int /*<<< orphan*/  hisi_sas_debugfs_bist_enable_ops ; 
 int /*<<< orphan*/  hisi_sas_debugfs_bist_linkrate_ops ; 
 int /*<<< orphan*/  hisi_sas_debugfs_bist_mode_ops ; 
 int /*<<< orphan*/  hisi_sas_debugfs_bist_phy_ops ; 

__attribute__((used)) static void hisi_sas_debugfs_bist_init(struct hisi_hba *hisi_hba)
{
	hisi_hba->debugfs_bist_dentry =
			debugfs_create_dir("bist", hisi_hba->debugfs_dir);
	debugfs_create_file("link_rate", 0600,
			    hisi_hba->debugfs_bist_dentry, hisi_hba,
			    &hisi_sas_debugfs_bist_linkrate_ops);

	debugfs_create_file("code_mode", 0600,
			    hisi_hba->debugfs_bist_dentry, hisi_hba,
			    &hisi_sas_debugfs_bist_code_mode_ops);

	debugfs_create_file("phy_id", 0600, hisi_hba->debugfs_bist_dentry,
			    hisi_hba, &hisi_sas_debugfs_bist_phy_ops);

	debugfs_create_u32("cnt", 0600, hisi_hba->debugfs_bist_dentry,
			   &hisi_hba->debugfs_bist_cnt);

	debugfs_create_file("loopback_mode", 0600,
			    hisi_hba->debugfs_bist_dentry,
			    hisi_hba, &hisi_sas_debugfs_bist_mode_ops);

	debugfs_create_file("enable", 0600, hisi_hba->debugfs_bist_dentry,
			    hisi_hba, &hisi_sas_debugfs_bist_enable_ops);

	hisi_hba->debugfs_bist_linkrate = SAS_LINK_RATE_1_5_GBPS;
}