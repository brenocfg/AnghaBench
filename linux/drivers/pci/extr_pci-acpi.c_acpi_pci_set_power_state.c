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
typedef  int u8 ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct acpi_device {int /*<<< orphan*/  handle; } ;
typedef  int pci_power_t ;

/* Variables and functions */
 struct acpi_device* ACPI_COMPANION (int /*<<< orphan*/ *) ; 
#define  ACPI_STATE_D0 137 
#define  ACPI_STATE_D1 136 
#define  ACPI_STATE_D2 135 
#define  ACPI_STATE_D3_COLD 134 
#define  ACPI_STATE_D3_HOT 133 
 int EBUSY ; 
 int EINVAL ; 
 int ENODEV ; 
#define  PCI_D0 132 
#define  PCI_D1 131 
#define  PCI_D2 130 
#define  PCI_D3cold 129 
#define  PCI_D3hot 128 
 int /*<<< orphan*/  PM_QOS_FLAGS_ALL ; 
 int /*<<< orphan*/  PM_QOS_FLAG_NO_POWER_OFF ; 
 int acpi_device_set_power (struct acpi_device*,int const) ; 
 scalar_t__ acpi_has_method (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  acpi_power_state_string (int const) ; 
 int /*<<< orphan*/  dev_pm_qos_flags (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_dbg (struct pci_dev*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int acpi_pci_set_power_state(struct pci_dev *dev, pci_power_t state)
{
	struct acpi_device *adev = ACPI_COMPANION(&dev->dev);
	static const u8 state_conv[] = {
		[PCI_D0] = ACPI_STATE_D0,
		[PCI_D1] = ACPI_STATE_D1,
		[PCI_D2] = ACPI_STATE_D2,
		[PCI_D3hot] = ACPI_STATE_D3_HOT,
		[PCI_D3cold] = ACPI_STATE_D3_COLD,
	};
	int error = -EINVAL;

	/* If the ACPI device has _EJ0, ignore the device */
	if (!adev || acpi_has_method(adev->handle, "_EJ0"))
		return -ENODEV;

	switch (state) {
	case PCI_D3cold:
		if (dev_pm_qos_flags(&dev->dev, PM_QOS_FLAG_NO_POWER_OFF) ==
				PM_QOS_FLAGS_ALL) {
			error = -EBUSY;
			break;
		}
		/* Fall through */
	case PCI_D0:
	case PCI_D1:
	case PCI_D2:
	case PCI_D3hot:
		error = acpi_device_set_power(adev, state_conv[state]);
	}

	if (!error)
		pci_dbg(dev, "power state changed by ACPI to %s\n",
			 acpi_power_state_string(state_conv[state]));

	return error;
}