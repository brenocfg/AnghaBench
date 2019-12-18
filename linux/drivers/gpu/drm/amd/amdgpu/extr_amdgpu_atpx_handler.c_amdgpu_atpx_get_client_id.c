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
typedef  enum vga_switcheroo_client_id { ____Placeholder_vga_switcheroo_client_id } vga_switcheroo_client_id ;
struct TYPE_2__ {scalar_t__ dhandle; } ;

/* Variables and functions */
 scalar_t__ ACPI_HANDLE (int /*<<< orphan*/ *) ; 
 int VGA_SWITCHEROO_DIS ; 
 int VGA_SWITCHEROO_IGD ; 
 TYPE_1__ amdgpu_atpx_priv ; 

__attribute__((used)) static enum vga_switcheroo_client_id amdgpu_atpx_get_client_id(struct pci_dev *pdev)
{
	if (amdgpu_atpx_priv.dhandle == ACPI_HANDLE(&pdev->dev))
		return VGA_SWITCHEROO_IGD;
	else
		return VGA_SWITCHEROO_DIS;
}