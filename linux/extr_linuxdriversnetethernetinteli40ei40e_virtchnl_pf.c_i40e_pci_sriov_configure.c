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
struct i40e_pf {int flags; int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
 int EINVAL ; 
 int I40E_FLAG_VEB_MODE_ENABLED ; 
 int /*<<< orphan*/  I40E_PF_RESET_FLAG ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  i40e_do_reset_safe (struct i40e_pf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i40e_free_vfs (struct i40e_pf*) ; 
 int i40e_pci_sriov_enable (struct pci_dev*,int) ; 
 struct i40e_pf* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_vfs_assigned (int /*<<< orphan*/ ) ; 

int i40e_pci_sriov_configure(struct pci_dev *pdev, int num_vfs)
{
	struct i40e_pf *pf = pci_get_drvdata(pdev);

	if (num_vfs) {
		if (!(pf->flags & I40E_FLAG_VEB_MODE_ENABLED)) {
			pf->flags |= I40E_FLAG_VEB_MODE_ENABLED;
			i40e_do_reset_safe(pf, I40E_PF_RESET_FLAG);
		}
		return i40e_pci_sriov_enable(pdev, num_vfs);
	}

	if (!pci_vfs_assigned(pf->pdev)) {
		i40e_free_vfs(pf);
		pf->flags &= ~I40E_FLAG_VEB_MODE_ENABLED;
		i40e_do_reset_safe(pf, I40E_PF_RESET_FLAG);
	} else {
		dev_warn(&pdev->dev, "Unable to free VFs because some are assigned to VMs.\n");
		return -EINVAL;
	}
	return 0;
}