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
struct platform_device {int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  acpi_handle ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_HANDLE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INTEL_HID_DSM_HEBC_V1_FN ; 
 int /*<<< orphan*/  INTEL_HID_DSM_HEBC_V2_FN ; 
 int /*<<< orphan*/  button_array_table ; 
 scalar_t__ dmi_check_system (int /*<<< orphan*/ ) ; 
 scalar_t__ intel_hid_evaluate_method (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long long*) ; 

__attribute__((used)) static bool button_array_present(struct platform_device *device)
{
	acpi_handle handle = ACPI_HANDLE(&device->dev);
	unsigned long long event_cap;

	if (intel_hid_evaluate_method(handle, INTEL_HID_DSM_HEBC_V2_FN,
				      &event_cap)) {
		/* Check presence of 5 button array or v2 power button */
		if (event_cap & 0x60000)
			return true;
	}

	if (intel_hid_evaluate_method(handle, INTEL_HID_DSM_HEBC_V1_FN,
				      &event_cap)) {
		if (event_cap & 0x20000)
			return true;
	}

	if (dmi_check_system(button_array_table))
		return true;

	return false;
}