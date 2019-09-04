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
struct pci_device_id {int /*<<< orphan*/  driver_data; } ;
struct pci_dev {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  edac_dbg (int /*<<< orphan*/ ,char*) ; 
 int i82975x_probe1 (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * mci_pdev ; 
 int /*<<< orphan*/ * pci_dev_get (struct pci_dev*) ; 
 scalar_t__ pci_enable_device (struct pci_dev*) ; 

__attribute__((used)) static int i82975x_init_one(struct pci_dev *pdev,
			    const struct pci_device_id *ent)
{
	int rc;

	edac_dbg(0, "\n");

	if (pci_enable_device(pdev) < 0)
		return -EIO;

	rc = i82975x_probe1(pdev, ent->driver_data);

	if (mci_pdev == NULL)
		mci_pdev = pci_dev_get(pdev);

	return rc;
}