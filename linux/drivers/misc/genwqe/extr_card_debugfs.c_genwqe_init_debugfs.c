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
 char* GENWQE_DEVNAME ; 
 unsigned int GENWQE_MAX_VFS ; 
 int /*<<< orphan*/  S_IRUGO ; 
 int /*<<< orphan*/  curr_dbg_uid0_fops ; 
 int /*<<< orphan*/  curr_dbg_uid1_fops ; 
 int /*<<< orphan*/  curr_dbg_uid2_fops ; 
 int /*<<< orphan*/  curr_regs_fops ; 
 int /*<<< orphan*/  ddcb_info_fops ; 
 struct dentry* debugfs_create_dir (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugfs_create_file (char*,int /*<<< orphan*/ ,struct dentry*,struct genwqe_dev*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debugfs_create_u32 (char*,int,struct dentry*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debugfs_create_x64 (char*,int,struct dentry*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  genwqe_is_privileged (struct genwqe_dev*) ; 
 int /*<<< orphan*/  info_fops ; 
 int /*<<< orphan*/  jtimer_fops ; 
 int /*<<< orphan*/  prev_dbg_uid0_fops ; 
 int /*<<< orphan*/  prev_dbg_uid1_fops ; 
 int /*<<< orphan*/  prev_dbg_uid2_fops ; 
 int /*<<< orphan*/  prev_regs_fops ; 
 int /*<<< orphan*/  queue_working_time_fops ; 
 int /*<<< orphan*/  sprintf (char*,char*,...) ; 

void genwqe_init_debugfs(struct genwqe_dev *cd)
{
	struct dentry *root;
	char card_name[64];
	char name[64];
	unsigned int i;

	sprintf(card_name, "%s%d_card", GENWQE_DEVNAME, cd->card_idx);

	root = debugfs_create_dir(card_name, cd->debugfs_genwqe);

	/* non privileged interfaces are done here */
	debugfs_create_file("ddcb_info", S_IRUGO, root, cd, &ddcb_info_fops);
	debugfs_create_file("info", S_IRUGO, root, cd, &info_fops);
	debugfs_create_x64("err_inject", 0666, root, &cd->err_inject);
	debugfs_create_u32("ddcb_software_timeout", 0666, root,
			   &cd->ddcb_software_timeout);
	debugfs_create_u32("kill_timeout", 0666, root, &cd->kill_timeout);

	/* privileged interfaces follow here */
	if (!genwqe_is_privileged(cd)) {
		cd->debugfs_root = root;
		return;
	}

	debugfs_create_file("curr_regs", S_IRUGO, root, cd, &curr_regs_fops);
	debugfs_create_file("curr_dbg_uid0", S_IRUGO, root, cd,
			    &curr_dbg_uid0_fops);
	debugfs_create_file("curr_dbg_uid1", S_IRUGO, root, cd,
			    &curr_dbg_uid1_fops);
	debugfs_create_file("curr_dbg_uid2", S_IRUGO, root, cd,
			    &curr_dbg_uid2_fops);
	debugfs_create_file("prev_regs", S_IRUGO, root, cd, &prev_regs_fops);
	debugfs_create_file("prev_dbg_uid0", S_IRUGO, root, cd,
			    &prev_dbg_uid0_fops);
	debugfs_create_file("prev_dbg_uid1", S_IRUGO, root, cd,
			    &prev_dbg_uid1_fops);
	debugfs_create_file("prev_dbg_uid2", S_IRUGO, root, cd,
			    &prev_dbg_uid2_fops);

	for (i = 0; i <  GENWQE_MAX_VFS; i++) {
		sprintf(name, "vf%u_jobtimeout_msec", i);
		debugfs_create_u32(name, 0666, root,
				   &cd->vf_jobtimeout_msec[i]);
	}

	debugfs_create_file("jobtimer", S_IRUGO, root, cd, &jtimer_fops);
	debugfs_create_file("queue_working_time", S_IRUGO, root, cd,
			    &queue_working_time_fops);
	debugfs_create_u32("skip_recovery", 0666, root, &cd->skip_recovery);
	debugfs_create_u32("use_platform_recovery", 0666, root,
			   &cd->use_platform_recovery);

	cd->debugfs_root = root;
}