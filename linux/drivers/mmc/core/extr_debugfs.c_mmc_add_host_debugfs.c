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
struct mmc_host {int /*<<< orphan*/  fail_mmc_request; int /*<<< orphan*/  caps2; int /*<<< orphan*/  caps; struct dentry* debugfs_root; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 int S_IRUSR ; 
 int S_IWUSR ; 
 struct dentry* debugfs_create_dir (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debugfs_create_file (char*,int,struct dentry*,struct mmc_host*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debugfs_create_x32 (char*,int,struct dentry*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fail_default_attr ; 
 scalar_t__ fail_request ; 
 int /*<<< orphan*/  fault_create_debugfs_attr (char*,struct dentry*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mmc_clock_fops ; 
 int /*<<< orphan*/  mmc_hostname (struct mmc_host*) ; 
 int /*<<< orphan*/  mmc_ios_fops ; 
 int /*<<< orphan*/  setup_fault_attr (int /*<<< orphan*/ *,scalar_t__) ; 

void mmc_add_host_debugfs(struct mmc_host *host)
{
	struct dentry *root;

	root = debugfs_create_dir(mmc_hostname(host), NULL);
	host->debugfs_root = root;

	debugfs_create_file("ios", S_IRUSR, root, host, &mmc_ios_fops);
	debugfs_create_x32("caps", S_IRUSR, root, &host->caps);
	debugfs_create_x32("caps2", S_IRUSR, root, &host->caps2);
	debugfs_create_file("clock", S_IRUSR | S_IWUSR, root, host,
			    &mmc_clock_fops);

#ifdef CONFIG_FAIL_MMC_REQUEST
	if (fail_request)
		setup_fault_attr(&fail_default_attr, fail_request);
	host->fail_mmc_request = fail_default_attr;
	fault_create_debugfs_attr("fail_mmc_request", root,
				  &host->fail_mmc_request);
#endif
}