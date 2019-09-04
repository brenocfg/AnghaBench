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

/* Variables and functions */

__attribute__((used)) static int i40e_pci_sriov_enable(struct pci_dev *pdev, int num_vfs)
{
#ifdef CONFIG_PCI_IOV
	struct i40e_pf *pf = pci_get_drvdata(pdev);
	int pre_existing_vfs = pci_num_vf(pdev);
	int err = 0;

	if (test_bit(__I40E_TESTING, pf->state)) {
		dev_warn(&pdev->dev,
			 "Cannot enable SR-IOV virtual functions while the device is undergoing diagnostic testing\n");
		err = -EPERM;
		goto err_out;
	}

	if (pre_existing_vfs && pre_existing_vfs != num_vfs)
		i40e_free_vfs(pf);
	else if (pre_existing_vfs && pre_existing_vfs == num_vfs)
		goto out;

	if (num_vfs > pf->num_req_vfs) {
		dev_warn(&pdev->dev, "Unable to enable %d VFs. Limited to %d VFs due to device resource constraints.\n",
			 num_vfs, pf->num_req_vfs);
		err = -EPERM;
		goto err_out;
	}

	dev_info(&pdev->dev, "Allocating %d VFs.\n", num_vfs);
	err = i40e_alloc_vfs(pf, num_vfs);
	if (err) {
		dev_warn(&pdev->dev, "Failed to enable SR-IOV: %d\n", err);
		goto err_out;
	}

out:
	return num_vfs;

err_out:
	return err;
#endif
	return 0;
}