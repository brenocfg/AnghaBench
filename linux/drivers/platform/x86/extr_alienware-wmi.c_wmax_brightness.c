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
struct wmax_brightness_args {int led_mask; int percentage; } ;
struct acpi_buffer {struct wmax_brightness_args* pointer; scalar_t__ length; } ;
typedef  int /*<<< orphan*/  args ;
typedef  int /*<<< orphan*/  acpi_status ;
typedef  scalar_t__ acpi_size ;

/* Variables and functions */
 int ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WMAX_CONTROL_GUID ; 
 int /*<<< orphan*/  WMAX_METHOD_BRIGHTNESS ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wmi_evaluate_method (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct acpi_buffer*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int wmax_brightness(int brightness)
{
	acpi_status status;
	struct acpi_buffer input;
	struct wmax_brightness_args args = {
		.led_mask = 0xFF,
		.percentage = brightness,
	};
	input.length = (acpi_size) sizeof(args);
	input.pointer = &args;
	status = wmi_evaluate_method(WMAX_CONTROL_GUID, 0,
				     WMAX_METHOD_BRIGHTNESS, &input, NULL);
	if (ACPI_FAILURE(status))
		pr_err("alienware-wmi: brightness set failure: %u\n", status);
	return ACPI_FAILURE(status);
}