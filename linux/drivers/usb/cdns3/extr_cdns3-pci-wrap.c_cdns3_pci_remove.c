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
struct pci_dev {scalar_t__ devfn; } ;
struct cdns3_wrap {scalar_t__ devfn; int /*<<< orphan*/  plat_dev; } ;

/* Variables and functions */
 struct pci_dev* cdns3_get_second_fun (struct pci_dev*) ; 
 int /*<<< orphan*/  kfree (struct cdns3_wrap*) ; 
 scalar_t__ pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_is_enabled (struct pci_dev*) ; 
 int /*<<< orphan*/  platform_device_unregister (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cdns3_pci_remove(struct pci_dev *pdev)
{
	struct cdns3_wrap *wrap;
	struct pci_dev *func;

	func = cdns3_get_second_fun(pdev);

	wrap = (struct cdns3_wrap *)pci_get_drvdata(pdev);
	if (wrap->devfn == pdev->devfn)
		platform_device_unregister(wrap->plat_dev);

	if (!pci_is_enabled(func))
		kfree(wrap);
}