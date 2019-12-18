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
struct backlight_device {int dummy; } ;
struct asus_laptop {int /*<<< orphan*/  handle; } ;
typedef  int /*<<< orphan*/  acpi_status ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  METHOD_BRIGHTNESS_GET ; 
 int /*<<< orphan*/  acpi_evaluate_integer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned long long*) ; 
 struct asus_laptop* bl_get_data (struct backlight_device*) ; 
 int /*<<< orphan*/  pr_warn (char*) ; 

__attribute__((used)) static int asus_read_brightness(struct backlight_device *bd)
{
	struct asus_laptop *asus = bl_get_data(bd);
	unsigned long long value;
	acpi_status rv;

	rv = acpi_evaluate_integer(asus->handle, METHOD_BRIGHTNESS_GET,
				   NULL, &value);
	if (ACPI_FAILURE(rv)) {
		pr_warn("Error reading brightness\n");
		return 0;
	}

	return value;
}