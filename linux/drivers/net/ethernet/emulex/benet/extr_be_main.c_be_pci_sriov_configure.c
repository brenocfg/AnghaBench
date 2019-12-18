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
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct be_resources {int /*<<< orphan*/  member_0; } ;
struct be_adapter {int num_vfs; int /*<<< orphan*/  pool_res; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  be_calculate_vf_res (struct be_adapter*,int,struct be_resources*) ; 
 int be_cmd_set_sriov_config (struct be_adapter*,int /*<<< orphan*/ ,int,struct be_resources*) ; 
 int be_cmd_status (int) ; 
 int be_get_resources (struct be_adapter*) ; 
 int be_update_queues (struct be_adapter*) ; 
 int /*<<< orphan*/  be_vf_clear (struct be_adapter*) ; 
 int be_vf_setup (struct be_adapter*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 struct be_adapter* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_num_vf (struct pci_dev*) ; 
 scalar_t__ pci_vfs_assigned (struct pci_dev*) ; 
 int /*<<< orphan*/  rtnl_lock () ; 
 int /*<<< orphan*/  rtnl_unlock () ; 
 scalar_t__ skyhawk_chip (struct be_adapter*) ; 

__attribute__((used)) static int be_pci_sriov_configure(struct pci_dev *pdev, int num_vfs)
{
	struct be_adapter *adapter = pci_get_drvdata(pdev);
	struct be_resources vft_res = {0};
	int status;

	if (!num_vfs)
		be_vf_clear(adapter);

	adapter->num_vfs = num_vfs;

	if (adapter->num_vfs == 0 && pci_vfs_assigned(pdev)) {
		dev_warn(&pdev->dev,
			 "Cannot disable VFs while they are assigned\n");
		return -EBUSY;
	}

	/* When the HW is in SRIOV capable configuration, the PF-pool resources
	 * are equally distributed across the max-number of VFs. The user may
	 * request only a subset of the max-vfs to be enabled.
	 * Based on num_vfs, redistribute the resources across num_vfs so that
	 * each VF will have access to more number of resources.
	 * This facility is not available in BE3 FW.
	 * Also, this is done by FW in Lancer chip.
	 */
	if (skyhawk_chip(adapter) && !pci_num_vf(pdev)) {
		be_calculate_vf_res(adapter, adapter->num_vfs,
				    &vft_res);
		status = be_cmd_set_sriov_config(adapter, adapter->pool_res,
						 adapter->num_vfs, &vft_res);
		if (status)
			dev_err(&pdev->dev,
				"Failed to optimize SR-IOV resources\n");
	}

	status = be_get_resources(adapter);
	if (status)
		return be_cmd_status(status);

	/* Updating real_num_tx/rx_queues() requires rtnl_lock() */
	rtnl_lock();
	status = be_update_queues(adapter);
	rtnl_unlock();
	if (status)
		return be_cmd_status(status);

	if (adapter->num_vfs)
		status = be_vf_setup(adapter);

	if (!status)
		return adapter->num_vfs;

	return 0;
}