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
struct i40e_pf {int flags; int /*<<< orphan*/  state; int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
 int EAGAIN ; 
 int EINVAL ; 
 int I40E_FLAG_VEB_MODE_ENABLED ; 
 int /*<<< orphan*/  I40E_PF_RESET_FLAG ; 
 int /*<<< orphan*/  __I40E_VIRTCHNL_OP_PENDING ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  i40e_do_reset_safe (struct i40e_pf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i40e_free_vfs (struct i40e_pf*) ; 
 int i40e_pci_sriov_enable (struct pci_dev*,int) ; 
 struct i40e_pf* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_vfs_assigned (int /*<<< orphan*/ ) ; 
 scalar_t__ test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int i40e_pci_sriov_configure(struct pci_dev *pdev, int num_vfs)
{
	struct i40e_pf *pf = pci_get_drvdata(pdev);
	int ret = 0;

	if (test_and_set_bit(__I40E_VIRTCHNL_OP_PENDING, pf->state)) {
		dev_warn(&pdev->dev, "Unable to configure VFs, other operation is pending.\n");
		return -EAGAIN;
	}

	if (num_vfs) {
		if (!(pf->flags & I40E_FLAG_VEB_MODE_ENABLED)) {
			pf->flags |= I40E_FLAG_VEB_MODE_ENABLED;
			i40e_do_reset_safe(pf, I40E_PF_RESET_FLAG);
		}
		ret = i40e_pci_sriov_enable(pdev, num_vfs);
		goto sriov_configure_out;
	}

	if (!pci_vfs_assigned(pf->pdev)) {
		i40e_free_vfs(pf);
		pf->flags &= ~I40E_FLAG_VEB_MODE_ENABLED;
		i40e_do_reset_safe(pf, I40E_PF_RESET_FLAG);
	} else {
		dev_warn(&pdev->dev, "Unable to free VFs because some are assigned to VMs.\n");
		ret = -EINVAL;
		goto sriov_configure_out;
	}
sriov_configure_out:
	clear_bit(__I40E_VIRTCHNL_OP_PENDING, pf->state);
	return ret;
}