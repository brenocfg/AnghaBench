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
typedef  int /*<<< orphan*/  umode_t ;
struct mmc_test_dbgfs_file {int /*<<< orphan*/  link; struct dentry* file; struct mmc_card* card; } ;
struct mmc_card {scalar_t__ debugfs_root; } ;
struct file_operations {int dummy; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  debugfs_create_file (char const*,int /*<<< orphan*/ ,scalar_t__,struct mmc_card*,struct file_operations const*) ; 
 int /*<<< orphan*/  debugfs_remove (struct dentry*) ; 
 struct mmc_test_dbgfs_file* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mmc_test_file_test ; 

__attribute__((used)) static int __mmc_test_register_dbgfs_file(struct mmc_card *card,
	const char *name, umode_t mode, const struct file_operations *fops)
{
	struct dentry *file = NULL;
	struct mmc_test_dbgfs_file *df;

	if (card->debugfs_root)
		debugfs_create_file(name, mode, card->debugfs_root, card, fops);

	df = kmalloc(sizeof(*df), GFP_KERNEL);
	if (!df) {
		debugfs_remove(file);
		return -ENOMEM;
	}

	df->card = card;
	df->file = file;

	list_add(&df->link, &mmc_test_file_test);
	return 0;
}