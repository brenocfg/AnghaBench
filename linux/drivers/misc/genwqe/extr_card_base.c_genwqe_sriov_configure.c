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
struct genwqe_dev {int dummy; } ;

/* Variables and functions */
 struct genwqe_dev* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  genwqe_setup_vf_jtimer (struct genwqe_dev*) ; 
 int /*<<< orphan*/  pci_disable_sriov (struct pci_dev*) ; 
 int pci_enable_sriov (struct pci_dev*,int) ; 

__attribute__((used)) static int genwqe_sriov_configure(struct pci_dev *dev, int numvfs)
{
	int rc;
	struct genwqe_dev *cd = dev_get_drvdata(&dev->dev);

	if (numvfs > 0) {
		genwqe_setup_vf_jtimer(cd);
		rc = pci_enable_sriov(dev, numvfs);
		if (rc < 0)
			return rc;
		return numvfs;
	}
	if (numvfs == 0) {
		pci_disable_sriov(dev);
		return 0;
	}
	return 0;
}