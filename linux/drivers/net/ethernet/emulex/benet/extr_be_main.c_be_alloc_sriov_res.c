#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct be_resources {int /*<<< orphan*/  member_0; } ;
struct be_adapter {TYPE_1__* pdev; int /*<<< orphan*/  pool_res; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  be_calculate_vf_res (struct be_adapter*,int /*<<< orphan*/ ,struct be_resources*) ; 
 int be_cmd_set_sriov_config (struct be_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct be_resources*) ; 
 int /*<<< orphan*/  be_get_sriov_config (struct be_adapter*) ; 
 scalar_t__ be_max_vfs (struct be_adapter*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int pci_num_vf (TYPE_1__*) ; 
 int /*<<< orphan*/  pci_sriov_set_totalvfs (TYPE_1__*,scalar_t__) ; 
 scalar_t__ skyhawk_chip (struct be_adapter*) ; 

__attribute__((used)) static void be_alloc_sriov_res(struct be_adapter *adapter)
{
	int old_vfs = pci_num_vf(adapter->pdev);
	struct  be_resources vft_res = {0};
	int status;

	be_get_sriov_config(adapter);

	if (!old_vfs)
		pci_sriov_set_totalvfs(adapter->pdev, be_max_vfs(adapter));

	/* When the HW is in SRIOV capable configuration, the PF-pool
	 * resources are given to PF during driver load, if there are no
	 * old VFs. This facility is not available in BE3 FW.
	 * Also, this is done by FW in Lancer chip.
	 */
	if (skyhawk_chip(adapter) && be_max_vfs(adapter) && !old_vfs) {
		be_calculate_vf_res(adapter, 0, &vft_res);
		status = be_cmd_set_sriov_config(adapter, adapter->pool_res, 0,
						 &vft_res);
		if (status)
			dev_err(&adapter->pdev->dev,
				"Failed to optimize SRIOV resources\n");
	}
}