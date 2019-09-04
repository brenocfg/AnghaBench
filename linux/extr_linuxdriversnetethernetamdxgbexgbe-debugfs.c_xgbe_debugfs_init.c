#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct xgbe_prv_data {int debugfs_xpcs_mmd; TYPE_2__* netdev; int /*<<< orphan*/  debugfs_an_cdr_track_early; int /*<<< orphan*/  xgbe_debugfs; int /*<<< orphan*/  debugfs_an_cdr_workaround; TYPE_1__* vdata; scalar_t__ xi2c_regs; scalar_t__ xprop_regs; scalar_t__ debugfs_xpcs_reg; scalar_t__ debugfs_xgmac_reg; } ;
struct dentry {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  name; } ;
struct TYPE_3__ {scalar_t__ an_cdr_workaround; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct dentry* debugfs_create_bool (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debugfs_create_dir (char*,int /*<<< orphan*/ *) ; 
 struct dentry* debugfs_create_file (char*,int,int /*<<< orphan*/ ,struct xgbe_prv_data*,int /*<<< orphan*/ *) ; 
 char* kasprintf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 int /*<<< orphan*/  netdev_err (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  xgmac_reg_addr_fops ; 
 int /*<<< orphan*/  xgmac_reg_value_fops ; 
 int /*<<< orphan*/  xi2c_reg_addr_fops ; 
 int /*<<< orphan*/  xi2c_reg_value_fops ; 
 int /*<<< orphan*/  xpcs_mmd_fops ; 
 int /*<<< orphan*/  xpcs_reg_addr_fops ; 
 int /*<<< orphan*/  xpcs_reg_value_fops ; 
 int /*<<< orphan*/  xprop_reg_addr_fops ; 
 int /*<<< orphan*/  xprop_reg_value_fops ; 

void xgbe_debugfs_init(struct xgbe_prv_data *pdata)
{
	struct dentry *pfile;
	char *buf;

	/* Set defaults */
	pdata->debugfs_xgmac_reg = 0;
	pdata->debugfs_xpcs_mmd = 1;
	pdata->debugfs_xpcs_reg = 0;

	buf = kasprintf(GFP_KERNEL, "amd-xgbe-%s", pdata->netdev->name);
	if (!buf)
		return;

	pdata->xgbe_debugfs = debugfs_create_dir(buf, NULL);
	if (!pdata->xgbe_debugfs) {
		netdev_err(pdata->netdev, "debugfs_create_dir failed\n");
		kfree(buf);
		return;
	}

	pfile = debugfs_create_file("xgmac_register", 0600,
				    pdata->xgbe_debugfs, pdata,
				    &xgmac_reg_addr_fops);
	if (!pfile)
		netdev_err(pdata->netdev, "debugfs_create_file failed\n");

	pfile = debugfs_create_file("xgmac_register_value", 0600,
				    pdata->xgbe_debugfs, pdata,
				    &xgmac_reg_value_fops);
	if (!pfile)
		netdev_err(pdata->netdev, "debugfs_create_file failed\n");

	pfile = debugfs_create_file("xpcs_mmd", 0600,
				    pdata->xgbe_debugfs, pdata,
				    &xpcs_mmd_fops);
	if (!pfile)
		netdev_err(pdata->netdev, "debugfs_create_file failed\n");

	pfile = debugfs_create_file("xpcs_register", 0600,
				    pdata->xgbe_debugfs, pdata,
				    &xpcs_reg_addr_fops);
	if (!pfile)
		netdev_err(pdata->netdev, "debugfs_create_file failed\n");

	pfile = debugfs_create_file("xpcs_register_value", 0600,
				    pdata->xgbe_debugfs, pdata,
				    &xpcs_reg_value_fops);
	if (!pfile)
		netdev_err(pdata->netdev, "debugfs_create_file failed\n");

	if (pdata->xprop_regs) {
		pfile = debugfs_create_file("xprop_register", 0600,
					    pdata->xgbe_debugfs, pdata,
					    &xprop_reg_addr_fops);
		if (!pfile)
			netdev_err(pdata->netdev,
				   "debugfs_create_file failed\n");

		pfile = debugfs_create_file("xprop_register_value", 0600,
					    pdata->xgbe_debugfs, pdata,
					    &xprop_reg_value_fops);
		if (!pfile)
			netdev_err(pdata->netdev,
				   "debugfs_create_file failed\n");
	}

	if (pdata->xi2c_regs) {
		pfile = debugfs_create_file("xi2c_register", 0600,
					    pdata->xgbe_debugfs, pdata,
					    &xi2c_reg_addr_fops);
		if (!pfile)
			netdev_err(pdata->netdev,
				   "debugfs_create_file failed\n");

		pfile = debugfs_create_file("xi2c_register_value", 0600,
					    pdata->xgbe_debugfs, pdata,
					    &xi2c_reg_value_fops);
		if (!pfile)
			netdev_err(pdata->netdev,
				   "debugfs_create_file failed\n");
	}

	if (pdata->vdata->an_cdr_workaround) {
		pfile = debugfs_create_bool("an_cdr_workaround", 0600,
					    pdata->xgbe_debugfs,
					    &pdata->debugfs_an_cdr_workaround);
		if (!pfile)
			netdev_err(pdata->netdev,
				   "debugfs_create_bool failed\n");

		pfile = debugfs_create_bool("an_cdr_track_early", 0600,
					    pdata->xgbe_debugfs,
					    &pdata->debugfs_an_cdr_track_early);
		if (!pfile)
			netdev_err(pdata->netdev,
				   "debugfs_create_bool failed\n");
	}

	kfree(buf);
}