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
typedef  int /*<<< orphan*/  wmax_basic_args ;
struct wmax_led_args {int led_mask; scalar_t__ state; int /*<<< orphan*/  brightness; int /*<<< orphan*/  colors; } ;
struct platform_zone {int location; int /*<<< orphan*/  colors; } ;
struct legacy_led_args {int led_mask; scalar_t__ state; int /*<<< orphan*/  brightness; int /*<<< orphan*/  colors; } ;
struct acpi_buffer {struct wmax_led_args* pointer; void* length; } ;
typedef  int /*<<< orphan*/  legacy_args ;
typedef  int /*<<< orphan*/  acpi_status ;
typedef  void* acpi_size ;

/* Variables and functions */
 int ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 scalar_t__ LEGACY_BOOTING ; 
 char* LEGACY_CONTROL_GUID ; 
 char* LEGACY_POWER_CONTROL_GUID ; 
 scalar_t__ LEGACY_SUSPEND ; 
 scalar_t__ WMAX ; 
 char* WMAX_CONTROL_GUID ; 
 int WMAX_METHOD_ZONE_CONTROL ; 
 int /*<<< orphan*/  global_brightness ; 
 scalar_t__ interface ; 
 scalar_t__ lighting_control_state ; 
 int /*<<< orphan*/  pr_debug (char*,char*,int) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wmi_evaluate_method (char*,int /*<<< orphan*/ ,int,struct acpi_buffer*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int alienware_update_led(struct platform_zone *zone)
{
	int method_id;
	acpi_status status;
	char *guid;
	struct acpi_buffer input;
	struct legacy_led_args legacy_args;
	struct wmax_led_args wmax_basic_args;
	if (interface == WMAX) {
		wmax_basic_args.led_mask = 1 << zone->location;
		wmax_basic_args.colors = zone->colors;
		wmax_basic_args.state = lighting_control_state;
		guid = WMAX_CONTROL_GUID;
		method_id = WMAX_METHOD_ZONE_CONTROL;

		input.length = (acpi_size) sizeof(wmax_basic_args);
		input.pointer = &wmax_basic_args;
	} else {
		legacy_args.colors = zone->colors;
		legacy_args.brightness = global_brightness;
		legacy_args.state = 0;
		if (lighting_control_state == LEGACY_BOOTING ||
		    lighting_control_state == LEGACY_SUSPEND) {
			guid = LEGACY_POWER_CONTROL_GUID;
			legacy_args.state = lighting_control_state;
		} else
			guid = LEGACY_CONTROL_GUID;
		method_id = zone->location + 1;

		input.length = (acpi_size) sizeof(legacy_args);
		input.pointer = &legacy_args;
	}
	pr_debug("alienware-wmi: guid %s method %d\n", guid, method_id);

	status = wmi_evaluate_method(guid, 0, method_id, &input, NULL);
	if (ACPI_FAILURE(status))
		pr_err("alienware-wmi: zone set failure: %u\n", status);
	return ACPI_FAILURE(status);
}