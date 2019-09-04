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
struct acpi_buffer {int member_0; char* member_1; } ;
typedef  int /*<<< orphan*/  acpi_method_name ;
typedef  int /*<<< orphan*/ * acpi_handle ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_FULL_PATHNAME ; 
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*,char*) ; 
 int PCI_CLASS_DISPLAY_VGA ; 
 int /*<<< orphan*/  acpi_get_name (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct acpi_buffer*) ; 
 scalar_t__ intel_dsm_pci_probe (struct pci_dev*) ; 
 struct pci_dev* pci_get_class (int,struct pci_dev*) ; 

__attribute__((used)) static bool intel_dsm_detect(void)
{
	acpi_handle dhandle = NULL;
	char acpi_method_name[255] = { 0 };
	struct acpi_buffer buffer = {sizeof(acpi_method_name), acpi_method_name};
	struct pci_dev *pdev = NULL;
	int vga_count = 0;

	while ((pdev = pci_get_class(PCI_CLASS_DISPLAY_VGA << 8, pdev)) != NULL) {
		vga_count++;
		dhandle = intel_dsm_pci_probe(pdev) ?: dhandle;
	}

	if (vga_count == 2 && dhandle) {
		acpi_get_name(dhandle, ACPI_FULL_PATHNAME, &buffer);
		DRM_DEBUG_DRIVER("vga_switcheroo: detected DSM switching method %s handle\n",
				 acpi_method_name);
		return true;
	}

	return false;
}