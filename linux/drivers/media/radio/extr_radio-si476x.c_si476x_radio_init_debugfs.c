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
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct si476x_radio {struct dentry* debugfs; TYPE_1__ v4l2dev; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct dentry*) ; 
 int PTR_ERR (struct dentry*) ; 
 int /*<<< orphan*/  S_IRUGO ; 
 struct dentry* debugfs_create_dir (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct dentry* debugfs_create_file (char*,int /*<<< orphan*/ ,struct dentry*,struct si476x_radio*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debugfs_remove_recursive (struct dentry*) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  radio_acf_fops ; 
 int /*<<< orphan*/  radio_agc_fops ; 
 int /*<<< orphan*/  radio_rds_blckcnt_fops ; 
 int /*<<< orphan*/  radio_rsq_fops ; 
 int /*<<< orphan*/  radio_rsq_primary_fops ; 

__attribute__((used)) static int si476x_radio_init_debugfs(struct si476x_radio *radio)
{
	struct dentry	*dentry;
	int		ret;

	dentry = debugfs_create_dir(dev_name(radio->v4l2dev.dev), NULL);
	if (IS_ERR(dentry)) {
		ret = PTR_ERR(dentry);
		goto exit;
	}
	radio->debugfs = dentry;

	dentry = debugfs_create_file("acf", S_IRUGO,
				     radio->debugfs, radio, &radio_acf_fops);
	if (IS_ERR(dentry)) {
		ret = PTR_ERR(dentry);
		goto cleanup;
	}

	dentry = debugfs_create_file("rds_blckcnt", S_IRUGO,
				     radio->debugfs, radio,
				     &radio_rds_blckcnt_fops);
	if (IS_ERR(dentry)) {
		ret = PTR_ERR(dentry);
		goto cleanup;
	}

	dentry = debugfs_create_file("agc", S_IRUGO,
				     radio->debugfs, radio, &radio_agc_fops);
	if (IS_ERR(dentry)) {
		ret = PTR_ERR(dentry);
		goto cleanup;
	}

	dentry = debugfs_create_file("rsq", S_IRUGO,
				     radio->debugfs, radio, &radio_rsq_fops);
	if (IS_ERR(dentry)) {
		ret = PTR_ERR(dentry);
		goto cleanup;
	}

	dentry = debugfs_create_file("rsq_primary", S_IRUGO,
				     radio->debugfs, radio,
				     &radio_rsq_primary_fops);
	if (IS_ERR(dentry)) {
		ret = PTR_ERR(dentry);
		goto cleanup;
	}

	return 0;
cleanup:
	debugfs_remove_recursive(radio->debugfs);
exit:
	return ret;
}