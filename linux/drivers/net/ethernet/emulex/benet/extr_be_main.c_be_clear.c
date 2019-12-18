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
struct pci_dev {int dummy; } ;
struct be_resources {int /*<<< orphan*/  member_0; } ;
struct be_adapter {int /*<<< orphan*/  flags; int /*<<< orphan*/  pool_res; struct pci_dev* pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BE_FLAGS_SETUP_DONE ; 
 int /*<<< orphan*/  be_calculate_vf_res (struct be_adapter*,int /*<<< orphan*/ ,struct be_resources*) ; 
 int /*<<< orphan*/  be_cancel_worker (struct be_adapter*) ; 
 int /*<<< orphan*/  be_clear_queues (struct be_adapter*) ; 
 int /*<<< orphan*/  be_cmd_set_sriov_config (struct be_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct be_resources*) ; 
 int /*<<< orphan*/  be_disable_vxlan_offloads (struct be_adapter*) ; 
 int /*<<< orphan*/  be_if_destroy (struct be_adapter*) ; 
 int /*<<< orphan*/  be_msix_disable (struct be_adapter*) ; 
 scalar_t__ be_physfn (struct be_adapter*) ; 
 int /*<<< orphan*/  be_vf_clear (struct be_adapter*) ; 
 int /*<<< orphan*/  be_wq ; 
 int /*<<< orphan*/  flush_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_sriov_get_totalvfs (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_vfs_assigned (struct pci_dev*) ; 
 scalar_t__ skyhawk_chip (struct be_adapter*) ; 
 scalar_t__ sriov_enabled (struct be_adapter*) ; 

__attribute__((used)) static int be_clear(struct be_adapter *adapter)
{
	struct pci_dev *pdev = adapter->pdev;
	struct  be_resources vft_res = {0};

	be_cancel_worker(adapter);

	flush_workqueue(be_wq);

	if (sriov_enabled(adapter))
		be_vf_clear(adapter);

	/* Re-configure FW to distribute resources evenly across max-supported
	 * number of VFs, only when VFs are not already enabled.
	 */
	if (skyhawk_chip(adapter) && be_physfn(adapter) &&
	    !pci_vfs_assigned(pdev)) {
		be_calculate_vf_res(adapter,
				    pci_sriov_get_totalvfs(pdev),
				    &vft_res);
		be_cmd_set_sriov_config(adapter, adapter->pool_res,
					pci_sriov_get_totalvfs(pdev),
					&vft_res);
	}

	be_disable_vxlan_offloads(adapter);

	be_if_destroy(adapter);

	be_clear_queues(adapter);

	be_msix_disable(adapter);
	adapter->flags &= ~BE_FLAGS_SETUP_DONE;
	return 0;
}