#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int state; } ;
struct acpi_device {TYPE_1__ power; } ;
typedef  int /*<<< orphan*/  const pci_power_t ;

/* Variables and functions */
 struct acpi_device* ACPI_COMPANION (int /*<<< orphan*/ *) ; 
#define  ACPI_STATE_D0 137 
#define  ACPI_STATE_D1 136 
#define  ACPI_STATE_D2 135 
#define  ACPI_STATE_D3_COLD 134 
#define  ACPI_STATE_D3_HOT 133 
 int ACPI_STATE_UNKNOWN ; 
#define  PCI_D0 132 
#define  PCI_D1 131 
#define  PCI_D2 130 
#define  PCI_D3cold 129 
#define  PCI_D3hot 128 
 int /*<<< orphan*/  const PCI_UNKNOWN ; 
 int /*<<< orphan*/  acpi_device_power_manageable (struct acpi_device*) ; 

__attribute__((used)) static pci_power_t acpi_pci_get_power_state(struct pci_dev *dev)
{
	struct acpi_device *adev = ACPI_COMPANION(&dev->dev);
	static const pci_power_t state_conv[] = {
		[ACPI_STATE_D0]      = PCI_D0,
		[ACPI_STATE_D1]      = PCI_D1,
		[ACPI_STATE_D2]      = PCI_D2,
		[ACPI_STATE_D3_HOT]  = PCI_D3hot,
		[ACPI_STATE_D3_COLD] = PCI_D3cold,
	};
	int state;

	if (!adev || !acpi_device_power_manageable(adev))
		return PCI_UNKNOWN;

	state = adev->power.state;
	if (state == ACPI_STATE_UNKNOWN)
		return PCI_UNKNOWN;

	return state_conv[state];
}