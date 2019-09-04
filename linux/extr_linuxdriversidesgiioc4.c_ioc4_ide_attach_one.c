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
struct ioc4_driver_data {scalar_t__ idd_variant; int /*<<< orphan*/  idd_pdev; } ;

/* Variables and functions */
 scalar_t__ IOC4_VARIANT_PCI_RT ; 
 int pci_init_sgiioc4 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ioc4_ide_attach_one(struct ioc4_driver_data *idd)
{
	/*
	 * PCI-RT does not bring out IDE connection.
	 * Do not attach to this particular IOC4.
	 */
	if (idd->idd_variant == IOC4_VARIANT_PCI_RT)
		return 0;

	return pci_init_sgiioc4(idd->idd_pdev);
}