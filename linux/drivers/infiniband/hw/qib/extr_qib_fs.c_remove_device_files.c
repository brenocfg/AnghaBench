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
typedef  int /*<<< orphan*/  unit ;
struct super_block {int /*<<< orphan*/  s_root; } ;
struct qib_devdata {int unit; int num_pports; int flags; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct dentry*) ; 
 int PTR_ERR (struct dentry*) ; 
 int QIB_HAS_QSFP ; 
 int /*<<< orphan*/  d_drop (struct dentry*) ; 
 int /*<<< orphan*/  d_inode (struct dentry*) ; 
 struct dentry* dget (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dput (struct dentry*) ; 
 int /*<<< orphan*/  inode_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inode_unlock (int /*<<< orphan*/ ) ; 
 struct dentry* lookup_one_len (char*,struct dentry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,char*) ; 
 int /*<<< orphan*/  remove_file (struct dentry*,char*) ; 
 int simple_rmdir (int /*<<< orphan*/ ,struct dentry*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 int /*<<< orphan*/  strlen (char*) ; 

__attribute__((used)) static int remove_device_files(struct super_block *sb,
			       struct qib_devdata *dd)
{
	struct dentry *dir, *root;
	char unit[10];
	int ret, i;

	root = dget(sb->s_root);
	inode_lock(d_inode(root));
	snprintf(unit, sizeof(unit), "%u", dd->unit);
	dir = lookup_one_len(unit, root, strlen(unit));

	if (IS_ERR(dir)) {
		ret = PTR_ERR(dir);
		pr_err("Lookup of %s failed\n", unit);
		goto bail;
	}

	inode_lock(d_inode(dir));
	remove_file(dir, "counters");
	remove_file(dir, "counter_names");
	remove_file(dir, "portcounter_names");
	for (i = 0; i < dd->num_pports; i++) {
		char fname[24];

		sprintf(fname, "port%dcounters", i + 1);
		remove_file(dir, fname);
		if (dd->flags & QIB_HAS_QSFP) {
			sprintf(fname, "qsfp%d", i + 1);
			remove_file(dir, fname);
		}
	}
	remove_file(dir, "flash");
	inode_unlock(d_inode(dir));
	ret = simple_rmdir(d_inode(root), dir);
	d_drop(dir);
	dput(dir);

bail:
	inode_unlock(d_inode(root));
	dput(root);
	return ret;
}