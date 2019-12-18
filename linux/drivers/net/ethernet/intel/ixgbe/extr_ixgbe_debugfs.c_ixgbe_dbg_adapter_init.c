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
struct ixgbe_adapter {int /*<<< orphan*/  ixgbe_dbg_adapter; int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  debugfs_create_dir (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugfs_create_file (char*,int,int /*<<< orphan*/ ,struct ixgbe_adapter*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ixgbe_dbg_netdev_ops_fops ; 
 int /*<<< orphan*/  ixgbe_dbg_reg_ops_fops ; 
 int /*<<< orphan*/  ixgbe_dbg_root ; 
 char* pci_name (int /*<<< orphan*/ ) ; 

void ixgbe_dbg_adapter_init(struct ixgbe_adapter *adapter)
{
	const char *name = pci_name(adapter->pdev);

	adapter->ixgbe_dbg_adapter = debugfs_create_dir(name, ixgbe_dbg_root);
	debugfs_create_file("reg_ops", 0600, adapter->ixgbe_dbg_adapter,
			    adapter, &ixgbe_dbg_reg_ops_fops);
	debugfs_create_file("netdev_ops", 0600, adapter->ixgbe_dbg_adapter,
			    adapter, &ixgbe_dbg_netdev_ops_fops);
}