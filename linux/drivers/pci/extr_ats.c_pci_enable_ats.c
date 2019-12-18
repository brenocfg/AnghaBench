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
typedef  int /*<<< orphan*/  u16 ;
struct pci_dev {int ats_enabled; int ats_stu; scalar_t__ ats_cap; int /*<<< orphan*/  ats_ref_cnt; scalar_t__ is_virtfn; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 scalar_t__ PCI_ATS_CTRL ; 
 int /*<<< orphan*/  PCI_ATS_CTRL_ENABLE ; 
 int /*<<< orphan*/  PCI_ATS_CTRL_STU (int) ; 
 int PCI_ATS_MIN_STU ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 struct pci_dev* pci_physfn (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_write_config_word (struct pci_dev*,scalar_t__,int /*<<< orphan*/ ) ; 

int pci_enable_ats(struct pci_dev *dev, int ps)
{
	u16 ctrl;
	struct pci_dev *pdev;

	if (!dev->ats_cap)
		return -EINVAL;

	if (WARN_ON(dev->ats_enabled))
		return -EBUSY;

	if (ps < PCI_ATS_MIN_STU)
		return -EINVAL;

	/*
	 * Note that enabling ATS on a VF fails unless it's already enabled
	 * with the same STU on the PF.
	 */
	ctrl = PCI_ATS_CTRL_ENABLE;
	if (dev->is_virtfn) {
		pdev = pci_physfn(dev);
		if (pdev->ats_stu != ps)
			return -EINVAL;

		atomic_inc(&pdev->ats_ref_cnt);  /* count enabled VFs */
	} else {
		dev->ats_stu = ps;
		ctrl |= PCI_ATS_CTRL_STU(dev->ats_stu - PCI_ATS_MIN_STU);
	}
	pci_write_config_word(dev, dev->ats_cap + PCI_ATS_CTRL, ctrl);

	dev->ats_enabled = 1;
	return 0;
}