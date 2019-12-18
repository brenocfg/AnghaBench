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
struct bdc_pci {int /*<<< orphan*/  bdc; } ;

/* Variables and functions */
 int /*<<< orphan*/  pci_disable_msi (struct pci_dev*) ; 
 struct bdc_pci* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  platform_device_unregister (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bdc_pci_remove(struct pci_dev *pci)
{
	struct bdc_pci *glue = pci_get_drvdata(pci);

	platform_device_unregister(glue->bdc);
	pci_disable_msi(pci);
}