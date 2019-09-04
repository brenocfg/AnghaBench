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
struct pci_dev {int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/ * acpi_handle ;

/* Variables and functions */
 int /*<<< orphan*/ * ACPI_HANDLE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*) ; 
 int INTEL_DSM_FN_PLATFORM_MUX_INFO ; 
 int /*<<< orphan*/  INTEL_DSM_REVISION_ID ; 
 int /*<<< orphan*/  acpi_check_dsm (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  intel_dsm_guid ; 
 int /*<<< orphan*/  intel_dsm_platform_mux_info (int /*<<< orphan*/ *) ; 

__attribute__((used)) static acpi_handle intel_dsm_pci_probe(struct pci_dev *pdev)
{
	acpi_handle dhandle;

	dhandle = ACPI_HANDLE(&pdev->dev);
	if (!dhandle)
		return NULL;

	if (!acpi_check_dsm(dhandle, &intel_dsm_guid, INTEL_DSM_REVISION_ID,
			    1 << INTEL_DSM_FN_PLATFORM_MUX_INFO)) {
		DRM_DEBUG_KMS("no _DSM method for intel device\n");
		return NULL;
	}

	intel_dsm_platform_mux_info(dhandle);

	return dhandle;
}