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
struct hnae3_handle {int /*<<< orphan*/  hnae3_dbgfs; int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  debugfs_create_dir (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugfs_create_file (char*,int,int /*<<< orphan*/ ,struct hnae3_handle*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hns3_dbg_cmd_fops ; 
 int /*<<< orphan*/  hns3_dbgfs_root ; 
 char* pci_name (int /*<<< orphan*/ ) ; 

void hns3_dbg_init(struct hnae3_handle *handle)
{
	const char *name = pci_name(handle->pdev);

	handle->hnae3_dbgfs = debugfs_create_dir(name, hns3_dbgfs_root);

	debugfs_create_file("cmd", 0600, handle->hnae3_dbgfs, handle,
			    &hns3_dbg_cmd_fops);
}