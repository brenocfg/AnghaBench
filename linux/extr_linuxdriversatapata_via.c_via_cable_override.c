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
struct pci_dev {int subsystem_vendor; int subsystem_device; } ;

/* Variables and functions */
 int /*<<< orphan*/  cable_dmi_table ; 
 scalar_t__ dmi_check_system (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int via_cable_override(struct pci_dev *pdev)
{
	/* Systems by DMI */
	if (dmi_check_system(cable_dmi_table))
		return 1;
	/* Arima W730-K8/Targa Visionary 811/... */
	if (pdev->subsystem_vendor == 0x161F && pdev->subsystem_device == 0x2032)
		return 1;
	return 0;
}