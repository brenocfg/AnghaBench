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
struct uio_pci_generic_dev {int /*<<< orphan*/  info; } ;
struct pci_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct uio_pci_generic_dev*) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 struct uio_pci_generic_dev* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  uio_unregister_device (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void remove(struct pci_dev *pdev)
{
	struct uio_pci_generic_dev *gdev = pci_get_drvdata(pdev);

	uio_unregister_device(&gdev->info);
	pci_disable_device(pdev);
	kfree(gdev);
}