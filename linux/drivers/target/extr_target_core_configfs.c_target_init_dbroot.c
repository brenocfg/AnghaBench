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
struct TYPE_2__ {int /*<<< orphan*/  i_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  DB_ROOT_LEN ; 
 char* DB_ROOT_PREFERRED ; 
 scalar_t__ IS_ERR (struct file*) ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  S_ISDIR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  db_root ; 
 int /*<<< orphan*/  db_root_stage ; 
 TYPE_1__* file_inode (struct file*) ; 
 int /*<<< orphan*/  filp_close (struct file*,int /*<<< orphan*/ *) ; 
 struct file* filp_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void target_init_dbroot(void)
{
	struct file *fp;

	snprintf(db_root_stage, DB_ROOT_LEN, DB_ROOT_PREFERRED);
	fp = filp_open(db_root_stage, O_RDONLY, 0);
	if (IS_ERR(fp)) {
		pr_err("db_root: cannot open: %s\n", db_root_stage);
		return;
	}
	if (!S_ISDIR(file_inode(fp)->i_mode)) {
		filp_close(fp, NULL);
		pr_err("db_root: not a valid directory: %s\n", db_root_stage);
		return;
	}
	filp_close(fp, NULL);

	strncpy(db_root, db_root_stage, DB_ROOT_LEN);
	pr_debug("Target_Core_ConfigFS: db_root set to %s\n", db_root);
}