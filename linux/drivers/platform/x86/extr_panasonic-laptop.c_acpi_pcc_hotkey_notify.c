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
typedef  int u32 ;
struct pcc_acpi {int dummy; } ;
struct acpi_device {int dummy; } ;

/* Variables and functions */
#define  HKEY_NOTIFY 128 
 struct pcc_acpi* acpi_driver_data (struct acpi_device*) ; 
 int /*<<< orphan*/  acpi_pcc_generate_keyinput (struct pcc_acpi*) ; 

__attribute__((used)) static void acpi_pcc_hotkey_notify(struct acpi_device *device, u32 event)
{
	struct pcc_acpi *pcc = acpi_driver_data(device);

	switch (event) {
	case HKEY_NOTIFY:
		acpi_pcc_generate_keyinput(pcc);
		break;
	default:
		/* nothing to do */
		break;
	}
}