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
struct msi_desc {int dummy; } ;

/* Variables and functions */
 int ia64_setup_msi_irq (struct pci_dev*,struct msi_desc*) ; 
 int platform_setup_msi_irq (struct pci_dev*,struct msi_desc*) ; 

int arch_setup_msi_irq(struct pci_dev *pdev, struct msi_desc *desc)
{
	if (platform_setup_msi_irq)
		return platform_setup_msi_irq(pdev, desc);

	return ia64_setup_msi_irq(pdev, desc);
}