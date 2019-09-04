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
struct mmc_host {int /*<<< orphan*/  class_dev; struct dentry* debugfs_root; int /*<<< orphan*/  caps2; int /*<<< orphan*/  caps; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct dentry*) ; 
 int S_IRUSR ; 
 int S_IWUSR ; 
 struct dentry* debugfs_create_dir (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debugfs_create_file (char*,int,struct dentry*,struct mmc_host*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debugfs_create_x32 (char*,int,struct dentry*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debugfs_remove_recursive (struct dentry*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  mmc_clock_fops ; 
 int /*<<< orphan*/  mmc_hostname (struct mmc_host*) ; 
 int /*<<< orphan*/  mmc_ios_fops ; 

void mmc_add_host_debugfs(struct mmc_host *host)
{
	struct dentry *root;

	root = debugfs_create_dir(mmc_hostname(host), NULL);
	if (IS_ERR(root))
		/* Don't complain -- debugfs just isn't enabled */
		return;
	if (!root)
		/* Complain -- debugfs is enabled, but it failed to
		 * create the directory. */
		goto err_root;

	host->debugfs_root = root;

	if (!debugfs_create_file("ios", S_IRUSR, root, host, &mmc_ios_fops))
		goto err_node;

	if (!debugfs_create_x32("caps", S_IRUSR, root, &host->caps))
		goto err_node;

	if (!debugfs_create_x32("caps2", S_IRUSR, root, &host->caps2))
		goto err_node;

	if (!debugfs_create_file("clock", S_IRUSR | S_IWUSR, root, host,
			&mmc_clock_fops))
		goto err_node;

#ifdef CONFIG_FAIL_MMC_REQUEST
	if (fail_request)
		setup_fault_attr(&fail_default_attr, fail_request);
	host->fail_mmc_request = fail_default_attr;
	if (IS_ERR(fault_create_debugfs_attr("fail_mmc_request",
					     root,
					     &host->fail_mmc_request)))
		goto err_node;
#endif
	return;

err_node:
	debugfs_remove_recursive(root);
	host->debugfs_root = NULL;
err_root:
	dev_err(&host->class_dev, "failed to initialize debugfs\n");
}