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
struct ixgbe_adapter {scalar_t__ ixgbe_dbg_adapter; int /*<<< orphan*/  pdev; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 scalar_t__ debugfs_create_dir (char const*,int /*<<< orphan*/ ) ; 
 struct dentry* debugfs_create_file (char*,int,scalar_t__,struct ixgbe_adapter*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  e_dev_err (char*,char const*) ; 
 int /*<<< orphan*/  ixgbe_dbg_netdev_ops_fops ; 
 int /*<<< orphan*/  ixgbe_dbg_reg_ops_fops ; 
 int /*<<< orphan*/  ixgbe_dbg_root ; 
 char* pci_name (int /*<<< orphan*/ ) ; 

void ixgbe_dbg_adapter_init(struct ixgbe_adapter *adapter)
{
	const char *name = pci_name(adapter->pdev);
	struct dentry *pfile;
	adapter->ixgbe_dbg_adapter = debugfs_create_dir(name, ixgbe_dbg_root);
	if (adapter->ixgbe_dbg_adapter) {
		pfile = debugfs_create_file("reg_ops", 0600,
					    adapter->ixgbe_dbg_adapter, adapter,
					    &ixgbe_dbg_reg_ops_fops);
		if (!pfile)
			e_dev_err("debugfs reg_ops for %s failed\n", name);
		pfile = debugfs_create_file("netdev_ops", 0600,
					    adapter->ixgbe_dbg_adapter, adapter,
					    &ixgbe_dbg_netdev_ops_fops);
		if (!pfile)
			e_dev_err("debugfs netdev_ops for %s failed\n", name);
	} else {
		e_dev_err("debugfs entry for %s failed\n", name);
	}
}