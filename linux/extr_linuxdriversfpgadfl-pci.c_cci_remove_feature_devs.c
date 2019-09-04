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
struct cci_drvdata {int /*<<< orphan*/  cdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dfl_fpga_feature_devs_remove (int /*<<< orphan*/ ) ; 
 struct cci_drvdata* pci_get_drvdata (struct pci_dev*) ; 

__attribute__((used)) static void cci_remove_feature_devs(struct pci_dev *pcidev)
{
	struct cci_drvdata *drvdata = pci_get_drvdata(pcidev);

	/* remove all children feature devices */
	dfl_fpga_feature_devs_remove(drvdata->cdev);
}