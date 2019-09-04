#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct pci_dev {scalar_t__ bridge_d3; } ;
struct acpi_buffer {int member_0; char* member_1; } ;
typedef  int /*<<< orphan*/  acpi_method_name ;
struct TYPE_3__ {int /*<<< orphan*/  handle; } ;
struct TYPE_4__ {int atpx_detected; int bridge_pm_usable; TYPE_1__ atpx; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_FULL_PATHNAME ; 
 int PCI_CLASS_DISPLAY_OTHER ; 
 int PCI_CLASS_DISPLAY_VGA ; 
 int /*<<< orphan*/  acpi_get_name (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct acpi_buffer*) ; 
 int /*<<< orphan*/  amdgpu_atpx_get_quirks (struct pci_dev*) ; 
 int /*<<< orphan*/  amdgpu_atpx_init () ; 
 int amdgpu_atpx_pci_probe_handle (struct pci_dev*) ; 
 TYPE_2__ amdgpu_atpx_priv ; 
 struct pci_dev* pci_get_class (int,struct pci_dev*) ; 
 struct pci_dev* pci_upstream_bridge (struct pci_dev*) ; 
 int /*<<< orphan*/  pr_info (char*,char*) ; 

__attribute__((used)) static bool amdgpu_atpx_detect(void)
{
	char acpi_method_name[255] = { 0 };
	struct acpi_buffer buffer = {sizeof(acpi_method_name), acpi_method_name};
	struct pci_dev *pdev = NULL;
	bool has_atpx = false;
	int vga_count = 0;
	bool d3_supported = false;
	struct pci_dev *parent_pdev;

	while ((pdev = pci_get_class(PCI_CLASS_DISPLAY_VGA << 8, pdev)) != NULL) {
		vga_count++;

		has_atpx |= (amdgpu_atpx_pci_probe_handle(pdev) == true);

		parent_pdev = pci_upstream_bridge(pdev);
		d3_supported |= parent_pdev && parent_pdev->bridge_d3;
		amdgpu_atpx_get_quirks(pdev);
	}

	while ((pdev = pci_get_class(PCI_CLASS_DISPLAY_OTHER << 8, pdev)) != NULL) {
		vga_count++;

		has_atpx |= (amdgpu_atpx_pci_probe_handle(pdev) == true);

		parent_pdev = pci_upstream_bridge(pdev);
		d3_supported |= parent_pdev && parent_pdev->bridge_d3;
		amdgpu_atpx_get_quirks(pdev);
	}

	if (has_atpx && vga_count == 2) {
		acpi_get_name(amdgpu_atpx_priv.atpx.handle, ACPI_FULL_PATHNAME, &buffer);
		pr_info("vga_switcheroo: detected switching method %s handle\n",
			acpi_method_name);
		amdgpu_atpx_priv.atpx_detected = true;
		amdgpu_atpx_priv.bridge_pm_usable = d3_supported;
		amdgpu_atpx_init();
		return true;
	}
	return false;
}