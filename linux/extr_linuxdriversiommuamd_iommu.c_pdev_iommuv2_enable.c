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
 int /*<<< orphan*/  AMD_PRI_DEV_ERRATUM_ENABLE_RESET ; 
 int /*<<< orphan*/  AMD_PRI_DEV_ERRATUM_LIMIT_REQ_ONE ; 
 int /*<<< orphan*/  PAGE_SHIFT ; 
 int /*<<< orphan*/  pci_disable_pasid (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_disable_pri (struct pci_dev*) ; 
 int pci_enable_ats (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int pci_enable_pasid (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int pci_enable_pri (struct pci_dev*,int) ; 
 int pci_reset_pri (struct pci_dev*) ; 
 int pdev_pri_erratum (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int pri_reset_while_enabled (struct pci_dev*) ; 

__attribute__((used)) static int pdev_iommuv2_enable(struct pci_dev *pdev)
{
	bool reset_enable;
	int reqs, ret;

	/* FIXME: Hardcode number of outstanding requests for now */
	reqs = 32;
	if (pdev_pri_erratum(pdev, AMD_PRI_DEV_ERRATUM_LIMIT_REQ_ONE))
		reqs = 1;
	reset_enable = pdev_pri_erratum(pdev, AMD_PRI_DEV_ERRATUM_ENABLE_RESET);

	/* Only allow access to user-accessible pages */
	ret = pci_enable_pasid(pdev, 0);
	if (ret)
		goto out_err;

	/* First reset the PRI state of the device */
	ret = pci_reset_pri(pdev);
	if (ret)
		goto out_err;

	/* Enable PRI */
	ret = pci_enable_pri(pdev, reqs);
	if (ret)
		goto out_err;

	if (reset_enable) {
		ret = pri_reset_while_enabled(pdev);
		if (ret)
			goto out_err;
	}

	ret = pci_enable_ats(pdev, PAGE_SHIFT);
	if (ret)
		goto out_err;

	return 0;

out_err:
	pci_disable_pri(pdev);
	pci_disable_pasid(pdev);

	return ret;
}