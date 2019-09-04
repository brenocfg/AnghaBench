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
struct mmc_host {int /*<<< orphan*/  debugfs_root; } ;
struct mmc_card {int /*<<< orphan*/  dev; struct dentry* debugfs_root; int /*<<< orphan*/  state; struct mmc_host* host; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct dentry*) ; 
 int /*<<< orphan*/  S_IRUSR ; 
 struct dentry* debugfs_create_dir (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugfs_create_x32 (char*,int /*<<< orphan*/ ,struct dentry*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debugfs_remove_recursive (struct dentry*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  mmc_card_id (struct mmc_card*) ; 

void mmc_add_card_debugfs(struct mmc_card *card)
{
	struct mmc_host	*host = card->host;
	struct dentry	*root;

	if (!host->debugfs_root)
		return;

	root = debugfs_create_dir(mmc_card_id(card), host->debugfs_root);
	if (IS_ERR(root))
		/* Don't complain -- debugfs just isn't enabled */
		return;
	if (!root)
		/* Complain -- debugfs is enabled, but it failed to
		 * create the directory. */
		goto err;

	card->debugfs_root = root;

	if (!debugfs_create_x32("state", S_IRUSR, root, &card->state))
		goto err;

	return;

err:
	debugfs_remove_recursive(root);
	card->debugfs_root = NULL;
	dev_err(&card->dev, "failed to initialize debugfs\n");
}