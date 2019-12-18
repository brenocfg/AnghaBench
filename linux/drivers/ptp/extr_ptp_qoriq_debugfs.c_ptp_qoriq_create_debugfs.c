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
struct ptp_qoriq {int /*<<< orphan*/  dev; struct dentry* debugfs_root; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct dentry*) ; 
 struct dentry* debugfs_create_dir (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debugfs_create_file_unsafe (char*,int,struct dentry*,struct ptp_qoriq*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debugfs_remove_recursive (struct dentry*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ptp_qoriq_fiper1_fops ; 
 int /*<<< orphan*/  ptp_qoriq_fiper2_fops ; 

void ptp_qoriq_create_debugfs(struct ptp_qoriq *ptp_qoriq)
{
	struct dentry *root;

	root = debugfs_create_dir(dev_name(ptp_qoriq->dev), NULL);
	if (IS_ERR(root))
		return;
	if (!root)
		goto err_root;

	ptp_qoriq->debugfs_root = root;

	if (!debugfs_create_file_unsafe("fiper1-loopback", 0600, root,
					ptp_qoriq, &ptp_qoriq_fiper1_fops))
		goto err_node;
	if (!debugfs_create_file_unsafe("fiper2-loopback", 0600, root,
					ptp_qoriq, &ptp_qoriq_fiper2_fops))
		goto err_node;
	return;

err_node:
	debugfs_remove_recursive(root);
	ptp_qoriq->debugfs_root = NULL;
err_root:
	dev_err(ptp_qoriq->dev, "failed to initialize debugfs\n");
}