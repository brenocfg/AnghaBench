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
struct pci_dev {int /*<<< orphan*/  dev; scalar_t__ no_d3cold; } ;
typedef  int /*<<< orphan*/  pci_power_t ;

/* Variables and functions */
#define  ACPI_STATE_D0 132 
#define  ACPI_STATE_D1 131 
#define  ACPI_STATE_D2 130 
#define  ACPI_STATE_D3_COLD 129 
#define  ACPI_STATE_D3_HOT 128 
 int /*<<< orphan*/  PCI_D0 ; 
 int /*<<< orphan*/  PCI_D1 ; 
 int /*<<< orphan*/  PCI_D2 ; 
 int /*<<< orphan*/  PCI_D3cold ; 
 int /*<<< orphan*/  PCI_D3hot ; 
 int /*<<< orphan*/  PCI_POWER_ERROR ; 
 int acpi_pm_device_sleep_state (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static pci_power_t acpi_pci_choose_state(struct pci_dev *pdev)
{
	int acpi_state, d_max;

	if (pdev->no_d3cold)
		d_max = ACPI_STATE_D3_HOT;
	else
		d_max = ACPI_STATE_D3_COLD;
	acpi_state = acpi_pm_device_sleep_state(&pdev->dev, NULL, d_max);
	if (acpi_state < 0)
		return PCI_POWER_ERROR;

	switch (acpi_state) {
	case ACPI_STATE_D0:
		return PCI_D0;
	case ACPI_STATE_D1:
		return PCI_D1;
	case ACPI_STATE_D2:
		return PCI_D2;
	case ACPI_STATE_D3_HOT:
		return PCI_D3hot;
	case ACPI_STATE_D3_COLD:
		return PCI_D3cold;
	}
	return PCI_POWER_ERROR;
}