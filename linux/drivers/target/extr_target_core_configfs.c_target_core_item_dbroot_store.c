#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct file {int dummy; } ;
struct config_item {int dummy; } ;
typedef  int ssize_t ;
struct TYPE_2__ {int /*<<< orphan*/  i_mode; } ;

/* Variables and functions */
 int DB_ROOT_LEN ; 
 int EINVAL ; 
 scalar_t__ IS_ERR (struct file*) ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  S_ISDIR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  db_root ; 
 char* db_root_stage ; 
 TYPE_1__* file_inode (struct file*) ; 
 int /*<<< orphan*/  filp_close (struct file*,int /*<<< orphan*/ *) ; 
 struct file* filp_open (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_tf_list ; 
 int /*<<< orphan*/  g_tf_lock ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 int snprintf (char*,int,char*,char const*) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static ssize_t target_core_item_dbroot_store(struct config_item *item,
					const char *page, size_t count)
{
	ssize_t read_bytes;
	struct file *fp;

	mutex_lock(&g_tf_lock);
	if (!list_empty(&g_tf_list)) {
		mutex_unlock(&g_tf_lock);
		pr_err("db_root: cannot be changed: target drivers registered");
		return -EINVAL;
	}

	if (count > (DB_ROOT_LEN - 1)) {
		mutex_unlock(&g_tf_lock);
		pr_err("db_root: count %d exceeds DB_ROOT_LEN-1: %u\n",
		       (int)count, DB_ROOT_LEN - 1);
		return -EINVAL;
	}

	read_bytes = snprintf(db_root_stage, DB_ROOT_LEN, "%s", page);
	if (!read_bytes) {
		mutex_unlock(&g_tf_lock);
		return -EINVAL;
	}
	if (db_root_stage[read_bytes - 1] == '\n')
		db_root_stage[read_bytes - 1] = '\0';

	/* validate new db root before accepting it */
	fp = filp_open(db_root_stage, O_RDONLY, 0);
	if (IS_ERR(fp)) {
		mutex_unlock(&g_tf_lock);
		pr_err("db_root: cannot open: %s\n", db_root_stage);
		return -EINVAL;
	}
	if (!S_ISDIR(file_inode(fp)->i_mode)) {
		filp_close(fp, NULL);
		mutex_unlock(&g_tf_lock);
		pr_err("db_root: not a directory: %s\n", db_root_stage);
		return -EINVAL;
	}
	filp_close(fp, NULL);

	strncpy(db_root, db_root_stage, read_bytes);

	mutex_unlock(&g_tf_lock);

	pr_debug("Target_Core_ConfigFS: db_root set to %s\n", db_root);

	return read_bytes;
}