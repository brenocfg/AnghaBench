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
struct ssusb_mtk {int /*<<< orphan*/  dbgfs_root; struct mtu3* u3d; } ;
struct mtu3 {int /*<<< orphan*/  mac_base; int /*<<< orphan*/  ippc_base; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 struct dentry* debugfs_create_dir (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugfs_create_file (char*,int,int /*<<< orphan*/ ,struct mtu3*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtu3_csr_regs ; 
 int /*<<< orphan*/  mtu3_debugfs_create_ep_dirs (struct mtu3*) ; 
 int /*<<< orphan*/  mtu3_debugfs_create_prb_files (struct mtu3*) ; 
 int /*<<< orphan*/  mtu3_debugfs_regset (struct mtu3*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct dentry*) ; 
 int /*<<< orphan*/  mtu3_dev_regs ; 
 int /*<<< orphan*/  mtu3_ep_used_fops ; 
 int /*<<< orphan*/  mtu3_ippc_regs ; 
 int /*<<< orphan*/  mtu3_link_state_fops ; 

void ssusb_dev_debugfs_init(struct ssusb_mtk *ssusb)
{
	struct mtu3 *mtu = ssusb->u3d;
	struct dentry *dir_regs;

	dir_regs = debugfs_create_dir("regs", ssusb->dbgfs_root);

	mtu3_debugfs_regset(mtu, mtu->ippc_base,
			    mtu3_ippc_regs, ARRAY_SIZE(mtu3_ippc_regs),
			    "reg-ippc", dir_regs);

	mtu3_debugfs_regset(mtu, mtu->mac_base,
			    mtu3_dev_regs, ARRAY_SIZE(mtu3_dev_regs),
			    "reg-dev", dir_regs);

	mtu3_debugfs_regset(mtu, mtu->mac_base,
			    mtu3_csr_regs, ARRAY_SIZE(mtu3_csr_regs),
			    "reg-csr", dir_regs);

	mtu3_debugfs_create_ep_dirs(mtu);

	mtu3_debugfs_create_prb_files(mtu);

	debugfs_create_file("link-state", 0444, ssusb->dbgfs_root,
			    mtu, &mtu3_link_state_fops);
	debugfs_create_file("ep-used", 0444, ssusb->dbgfs_root,
			    mtu, &mtu3_ep_used_fops);
}