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
struct ubi_debug_info {char* dfs_dir_name; struct dentry* dfs_dir; struct dentry* dfs_power_cut_max; struct dentry* dfs_power_cut_min; struct dentry* dfs_emulate_power_cut; struct dentry* dfs_emulate_io_failures; struct dentry* dfs_emulate_bitflips; struct dentry* dfs_disable_bgt; struct dentry* dfs_chk_fastmap; struct dentry* dfs_chk_io; struct dentry* dfs_chk_gen; } ;
struct ubi_device {unsigned long ubi_num; struct ubi_debug_info dbg; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_DEBUG_FS ; 
 int /*<<< orphan*/  EINVAL ; 
 int ENODEV ; 
 struct dentry* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IS_ENABLED (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR_OR_NULL (struct dentry*) ; 
 int PTR_ERR (struct dentry*) ; 
 int /*<<< orphan*/  S_IRUSR ; 
 int /*<<< orphan*/  S_IWUSR ; 
 int UBI_DFS_DIR_LEN ; 
 char* UBI_DFS_DIR_NAME ; 
 struct dentry* debugfs_create_dir (char const*,int /*<<< orphan*/ ) ; 
 struct dentry* debugfs_create_file (char const*,int /*<<< orphan*/ ,struct dentry*,void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debugfs_remove_recursive (struct dentry*) ; 
 int /*<<< orphan*/  dfs_fops ; 
 int /*<<< orphan*/  dfs_rootdir ; 
 int /*<<< orphan*/  eraseblk_count_fops ; 
 int snprintf (char*,int,char*,unsigned long) ; 
 int /*<<< orphan*/  ubi_err (struct ubi_device*,char*,char const*,int) ; 

int ubi_debugfs_init_dev(struct ubi_device *ubi)
{
	int err, n;
	unsigned long ubi_num = ubi->ubi_num;
	const char *fname;
	struct dentry *dent;
	struct ubi_debug_info *d = &ubi->dbg;

	if (!IS_ENABLED(CONFIG_DEBUG_FS))
		return 0;

	n = snprintf(d->dfs_dir_name, UBI_DFS_DIR_LEN + 1, UBI_DFS_DIR_NAME,
		     ubi->ubi_num);
	if (n == UBI_DFS_DIR_LEN) {
		/* The array size is too small */
		fname = UBI_DFS_DIR_NAME;
		dent = ERR_PTR(-EINVAL);
		goto out;
	}

	fname = d->dfs_dir_name;
	dent = debugfs_create_dir(fname, dfs_rootdir);
	if (IS_ERR_OR_NULL(dent))
		goto out;
	d->dfs_dir = dent;

	fname = "chk_gen";
	dent = debugfs_create_file(fname, S_IWUSR, d->dfs_dir, (void *)ubi_num,
				   &dfs_fops);
	if (IS_ERR_OR_NULL(dent))
		goto out_remove;
	d->dfs_chk_gen = dent;

	fname = "chk_io";
	dent = debugfs_create_file(fname, S_IWUSR, d->dfs_dir, (void *)ubi_num,
				   &dfs_fops);
	if (IS_ERR_OR_NULL(dent))
		goto out_remove;
	d->dfs_chk_io = dent;

	fname = "chk_fastmap";
	dent = debugfs_create_file(fname, S_IWUSR, d->dfs_dir, (void *)ubi_num,
				   &dfs_fops);
	if (IS_ERR_OR_NULL(dent))
		goto out_remove;
	d->dfs_chk_fastmap = dent;

	fname = "tst_disable_bgt";
	dent = debugfs_create_file(fname, S_IWUSR, d->dfs_dir, (void *)ubi_num,
				   &dfs_fops);
	if (IS_ERR_OR_NULL(dent))
		goto out_remove;
	d->dfs_disable_bgt = dent;

	fname = "tst_emulate_bitflips";
	dent = debugfs_create_file(fname, S_IWUSR, d->dfs_dir, (void *)ubi_num,
				   &dfs_fops);
	if (IS_ERR_OR_NULL(dent))
		goto out_remove;
	d->dfs_emulate_bitflips = dent;

	fname = "tst_emulate_io_failures";
	dent = debugfs_create_file(fname, S_IWUSR, d->dfs_dir, (void *)ubi_num,
				   &dfs_fops);
	if (IS_ERR_OR_NULL(dent))
		goto out_remove;
	d->dfs_emulate_io_failures = dent;

	fname = "tst_emulate_power_cut";
	dent = debugfs_create_file(fname, S_IWUSR, d->dfs_dir, (void *)ubi_num,
				   &dfs_fops);
	if (IS_ERR_OR_NULL(dent))
		goto out_remove;
	d->dfs_emulate_power_cut = dent;

	fname = "tst_emulate_power_cut_min";
	dent = debugfs_create_file(fname, S_IWUSR, d->dfs_dir, (void *)ubi_num,
				   &dfs_fops);
	if (IS_ERR_OR_NULL(dent))
		goto out_remove;
	d->dfs_power_cut_min = dent;

	fname = "tst_emulate_power_cut_max";
	dent = debugfs_create_file(fname, S_IWUSR, d->dfs_dir, (void *)ubi_num,
				   &dfs_fops);
	if (IS_ERR_OR_NULL(dent))
		goto out_remove;
	d->dfs_power_cut_max = dent;

	fname = "detailed_erase_block_info";
	dent = debugfs_create_file(fname, S_IRUSR, d->dfs_dir, (void *)ubi_num,
				   &eraseblk_count_fops);
	if (IS_ERR_OR_NULL(dent))
		goto out_remove;

	return 0;

out_remove:
	debugfs_remove_recursive(d->dfs_dir);
out:
	err = dent ? PTR_ERR(dent) : -ENODEV;
	ubi_err(ubi, "cannot create \"%s\" debugfs file or directory, error %d\n",
		fname, err);
	return err;
}