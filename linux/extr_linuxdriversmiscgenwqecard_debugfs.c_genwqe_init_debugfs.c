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
struct genwqe_dev {struct dentry* debugfs_root; int /*<<< orphan*/  use_platform_recovery; int /*<<< orphan*/  skip_recovery; int /*<<< orphan*/ * vf_jobtimeout_msec; int /*<<< orphan*/  kill_timeout; int /*<<< orphan*/  ddcb_software_timeout; int /*<<< orphan*/  err_inject; int /*<<< orphan*/  debugfs_genwqe; int /*<<< orphan*/  card_idx; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 char* GENWQE_DEVNAME ; 
 unsigned int GENWQE_MAX_VFS ; 
 int /*<<< orphan*/  S_IRUGO ; 
 struct dentry* debugfs_create_dir (char*,int /*<<< orphan*/ ) ; 
 struct dentry* debugfs_create_file (char*,int /*<<< orphan*/ ,struct dentry*,struct genwqe_dev*,int /*<<< orphan*/ *) ; 
 struct dentry* debugfs_create_u32 (char*,int,struct dentry*,int /*<<< orphan*/ *) ; 
 struct dentry* debugfs_create_x64 (char*,int,struct dentry*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debugfs_remove_recursive (struct dentry*) ; 
 int /*<<< orphan*/  genwqe_curr_dbg_uid0_fops ; 
 int /*<<< orphan*/  genwqe_curr_dbg_uid1_fops ; 
 int /*<<< orphan*/  genwqe_curr_dbg_uid2_fops ; 
 int /*<<< orphan*/  genwqe_curr_regs_fops ; 
 int /*<<< orphan*/  genwqe_ddcb_info_fops ; 
 int /*<<< orphan*/  genwqe_info_fops ; 
 int /*<<< orphan*/  genwqe_is_privileged (struct genwqe_dev*) ; 
 int /*<<< orphan*/  genwqe_jtimer_fops ; 
 int /*<<< orphan*/  genwqe_prev_dbg_uid0_fops ; 
 int /*<<< orphan*/  genwqe_prev_dbg_uid1_fops ; 
 int /*<<< orphan*/  genwqe_prev_dbg_uid2_fops ; 
 int /*<<< orphan*/  genwqe_prev_regs_fops ; 
 int /*<<< orphan*/  genwqe_queue_working_time_fops ; 
 int /*<<< orphan*/  sprintf (char*,char*,...) ; 

int genwqe_init_debugfs(struct genwqe_dev *cd)
{
	struct dentry *root;
	struct dentry *file;
	int ret;
	char card_name[64];
	char name[64];
	unsigned int i;

	sprintf(card_name, "%s%d_card", GENWQE_DEVNAME, cd->card_idx);

	root = debugfs_create_dir(card_name, cd->debugfs_genwqe);
	if (!root) {
		ret = -ENOMEM;
		goto err0;
	}

	/* non privileged interfaces are done here */
	file = debugfs_create_file("ddcb_info", S_IRUGO, root, cd,
				   &genwqe_ddcb_info_fops);
	if (!file) {
		ret = -ENOMEM;
		goto err1;
	}

	file = debugfs_create_file("info", S_IRUGO, root, cd,
				   &genwqe_info_fops);
	if (!file) {
		ret = -ENOMEM;
		goto err1;
	}

	file = debugfs_create_x64("err_inject", 0666, root, &cd->err_inject);
	if (!file) {
		ret = -ENOMEM;
		goto err1;
	}

	file = debugfs_create_u32("ddcb_software_timeout", 0666, root,
				  &cd->ddcb_software_timeout);
	if (!file) {
		ret = -ENOMEM;
		goto err1;
	}

	file = debugfs_create_u32("kill_timeout", 0666, root,
				  &cd->kill_timeout);
	if (!file) {
		ret = -ENOMEM;
		goto err1;
	}

	/* privileged interfaces follow here */
	if (!genwqe_is_privileged(cd)) {
		cd->debugfs_root = root;
		return 0;
	}

	file = debugfs_create_file("curr_regs", S_IRUGO, root, cd,
				   &genwqe_curr_regs_fops);
	if (!file) {
		ret = -ENOMEM;
		goto err1;
	}

	file = debugfs_create_file("curr_dbg_uid0", S_IRUGO, root, cd,
				   &genwqe_curr_dbg_uid0_fops);
	if (!file) {
		ret = -ENOMEM;
		goto err1;
	}

	file = debugfs_create_file("curr_dbg_uid1", S_IRUGO, root, cd,
				   &genwqe_curr_dbg_uid1_fops);
	if (!file) {
		ret = -ENOMEM;
		goto err1;
	}

	file = debugfs_create_file("curr_dbg_uid2", S_IRUGO, root, cd,
				   &genwqe_curr_dbg_uid2_fops);
	if (!file) {
		ret = -ENOMEM;
		goto err1;
	}

	file = debugfs_create_file("prev_regs", S_IRUGO, root, cd,
				   &genwqe_prev_regs_fops);
	if (!file) {
		ret = -ENOMEM;
		goto err1;
	}

	file = debugfs_create_file("prev_dbg_uid0", S_IRUGO, root, cd,
				   &genwqe_prev_dbg_uid0_fops);
	if (!file) {
		ret = -ENOMEM;
		goto err1;
	}

	file = debugfs_create_file("prev_dbg_uid1", S_IRUGO, root, cd,
				   &genwqe_prev_dbg_uid1_fops);
	if (!file) {
		ret = -ENOMEM;
		goto err1;
	}

	file = debugfs_create_file("prev_dbg_uid2", S_IRUGO, root, cd,
				   &genwqe_prev_dbg_uid2_fops);
	if (!file) {
		ret = -ENOMEM;
		goto err1;
	}

	for (i = 0; i <  GENWQE_MAX_VFS; i++) {
		sprintf(name, "vf%u_jobtimeout_msec", i);

		file = debugfs_create_u32(name, 0666, root,
					  &cd->vf_jobtimeout_msec[i]);
		if (!file) {
			ret = -ENOMEM;
			goto err1;
		}
	}

	file = debugfs_create_file("jobtimer", S_IRUGO, root, cd,
				   &genwqe_jtimer_fops);
	if (!file) {
		ret = -ENOMEM;
		goto err1;
	}

	file = debugfs_create_file("queue_working_time", S_IRUGO, root, cd,
				   &genwqe_queue_working_time_fops);
	if (!file) {
		ret = -ENOMEM;
		goto err1;
	}

	file = debugfs_create_u32("skip_recovery", 0666, root,
				  &cd->skip_recovery);
	if (!file) {
		ret = -ENOMEM;
		goto err1;
	}

	file = debugfs_create_u32("use_platform_recovery", 0666, root,
				  &cd->use_platform_recovery);
	if (!file) {
		ret = -ENOMEM;
		goto err1;
	}

	cd->debugfs_root = root;
	return 0;
err1:
	debugfs_remove_recursive(root);
err0:
	return ret;
}