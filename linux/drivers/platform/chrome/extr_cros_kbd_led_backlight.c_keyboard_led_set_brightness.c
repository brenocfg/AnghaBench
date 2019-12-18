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
struct TYPE_2__ {int value; } ;
union acpi_object {TYPE_1__ integer; int /*<<< orphan*/  type; } ;
struct led_classdev {int /*<<< orphan*/  dev; } ;
struct acpi_object_list {int count; union acpi_object* pointer; } ;
typedef  enum led_brightness { ____Placeholder_led_brightness } led_brightness ;
typedef  int /*<<< orphan*/  acpi_status ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_KEYBOARD_BACKLIGHT_WRITE ; 
 int /*<<< orphan*/  ACPI_TYPE_INTEGER ; 
 int /*<<< orphan*/  acpi_evaluate_object (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct acpi_object_list*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void keyboard_led_set_brightness(struct led_classdev *cdev,
					enum led_brightness brightness)
{
	union acpi_object param;
	struct acpi_object_list input;
	acpi_status status;

	param.type = ACPI_TYPE_INTEGER;
	param.integer.value = brightness;
	input.count = 1;
	input.pointer = &param;

	status = acpi_evaluate_object(NULL, ACPI_KEYBOARD_BACKLIGHT_WRITE,
				      &input, NULL);
	if (ACPI_FAILURE(status))
		dev_err(cdev->dev, "Error setting keyboard LED value: %d\n",
			status);
}