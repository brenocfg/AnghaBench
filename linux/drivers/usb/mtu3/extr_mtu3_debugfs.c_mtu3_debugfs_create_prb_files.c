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
struct ssusb_mtk {int /*<<< orphan*/  dbgfs_root; } ;
struct mtu3 {int /*<<< orphan*/  ippc_base; struct ssusb_mtk* ssusb; } ;
struct dentry {int dummy; } ;
struct debugfs_reg32 {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct debugfs_reg32*) ; 
 struct dentry* debugfs_create_dir (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugfs_create_file (int /*<<< orphan*/ ,int,struct dentry*,struct mtu3*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtu3_debugfs_regset (struct mtu3*,int /*<<< orphan*/ ,struct debugfs_reg32*,int,char*,struct dentry*) ; 
 struct debugfs_reg32* mtu3_prb_regs ; 
 int /*<<< orphan*/  mtu3_probe_fops ; 

__attribute__((used)) static void mtu3_debugfs_create_prb_files(struct mtu3 *mtu)
{
	struct ssusb_mtk *ssusb = mtu->ssusb;
	struct debugfs_reg32 *regs;
	struct dentry *dir_prb;
	int i;

	dir_prb = debugfs_create_dir("probe", ssusb->dbgfs_root);

	for (i = 0; i < ARRAY_SIZE(mtu3_prb_regs); i++) {
		regs = &mtu3_prb_regs[i];
		debugfs_create_file(regs->name, 0644, dir_prb,
				    mtu, &mtu3_probe_fops);
	}

	mtu3_debugfs_regset(mtu, mtu->ippc_base, mtu3_prb_regs,
			    ARRAY_SIZE(mtu3_prb_regs), "regs", dir_prb);
}