#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct pci_dev {int pcie_mpss; TYPE_1__* bus; } ;
struct TYPE_2__ {struct pci_dev* self; } ;

/* Variables and functions */
 int min (int,int) ; 
 scalar_t__ pci_is_pcie (struct pci_dev*) ; 
 int pcie_get_mps (struct pci_dev*) ; 
 int pcie_set_mps (struct pci_dev*,int) ; 
 int /*<<< orphan*/  pr_debug (char*,int,int,int) ; 
 int /*<<< orphan*/  pr_err (char*,int,int) ; 

__attribute__((used)) static void qtnf_tune_pcie_mps(struct pci_dev *pdev)
{
	struct pci_dev *parent;
	int mps_p, mps_o, mps_m, mps;
	int ret;

	/* current mps */
	mps_o = pcie_get_mps(pdev);

	/* maximum supported mps */
	mps_m = 128 << pdev->pcie_mpss;

	/* suggested new mps value */
	mps = mps_m;

	if (pdev->bus && pdev->bus->self) {
		/* parent (bus) mps */
		parent = pdev->bus->self;

		if (pci_is_pcie(parent)) {
			mps_p = pcie_get_mps(parent);
			mps = min(mps_m, mps_p);
		}
	}

	ret = pcie_set_mps(pdev, mps);
	if (ret) {
		pr_err("failed to set mps to %d, keep using current %d\n",
		       mps, mps_o);
		return;
	}

	pr_debug("set mps to %d (was %d, max %d)\n", mps, mps_o, mps_m);
}