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
typedef  int /*<<< orphan*/  pci_ers_result_t ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_ERS_RESULT_DISCONNECT ; 
 int /*<<< orphan*/  PCI_ERS_RESULT_RECOVERED ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 struct genwqe_dev* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int genwqe_pci_setup (struct genwqe_dev*) ; 

__attribute__((used)) static pci_ers_result_t genwqe_err_slot_reset(struct pci_dev *pci_dev)
{
	int rc;
	struct genwqe_dev *cd = dev_get_drvdata(&pci_dev->dev);

	rc = genwqe_pci_setup(cd);
	if (!rc) {
		return PCI_ERS_RESULT_RECOVERED;
	} else {
		dev_err(&pci_dev->dev,
			"err: problems with PCI setup (err=%d)\n", rc);
		return PCI_ERS_RESULT_DISCONNECT;
	}
}