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
struct mmc_host {int /*<<< orphan*/  class_dev; struct dentry* debugfs_root; } ;
struct dentry {int dummy; } ;
struct atmel_mci_slot {int /*<<< orphan*/  completed_events; int /*<<< orphan*/  pending_events; int /*<<< orphan*/  state; struct atmel_mci_slot* host; struct mmc_host* mmc; } ;
struct atmel_mci {int /*<<< orphan*/  completed_events; int /*<<< orphan*/  pending_events; int /*<<< orphan*/  state; struct atmel_mci* host; struct mmc_host* mmc; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct dentry*) ; 
 int /*<<< orphan*/  S_IRUSR ; 
 int /*<<< orphan*/  atmci_regs_fops ; 
 int /*<<< orphan*/  atmci_req_fops ; 
 struct dentry* debugfs_create_file (char*,int /*<<< orphan*/ ,struct dentry*,struct atmel_mci_slot*,int /*<<< orphan*/ *) ; 
 struct dentry* debugfs_create_u32 (char*,int /*<<< orphan*/ ,struct dentry*,int /*<<< orphan*/ *) ; 
 struct dentry* debugfs_create_x32 (char*,int /*<<< orphan*/ ,struct dentry*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static void atmci_init_debugfs(struct atmel_mci_slot *slot)
{
	struct mmc_host		*mmc = slot->mmc;
	struct atmel_mci	*host = slot->host;
	struct dentry		*root;
	struct dentry		*node;

	root = mmc->debugfs_root;
	if (!root)
		return;

	node = debugfs_create_file("regs", S_IRUSR, root, host,
			&atmci_regs_fops);
	if (IS_ERR(node))
		return;
	if (!node)
		goto err;

	node = debugfs_create_file("req", S_IRUSR, root, slot, &atmci_req_fops);
	if (!node)
		goto err;

	node = debugfs_create_u32("state", S_IRUSR, root, (u32 *)&host->state);
	if (!node)
		goto err;

	node = debugfs_create_x32("pending_events", S_IRUSR, root,
				     (u32 *)&host->pending_events);
	if (!node)
		goto err;

	node = debugfs_create_x32("completed_events", S_IRUSR, root,
				     (u32 *)&host->completed_events);
	if (!node)
		goto err;

	return;

err:
	dev_err(&mmc->class_dev, "failed to initialize debugfs for slot\n");
}