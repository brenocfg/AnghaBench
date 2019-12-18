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
struct TYPE_2__ {int brightness; } ;
struct backlight_device {TYPE_1__ props; } ;
typedef  int /*<<< orphan*/  acpi_status ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int EIO ; 
 int SAMSUNGQ10_BL_MAX_INTENSITY ; 
 int /*<<< orphan*/  acpi_evaluate_object (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ec_handle ; 

__attribute__((used)) static int samsungq10_bl_set_intensity(struct backlight_device *bd)
{

	acpi_status status;
	int i;

	for (i = 0; i < SAMSUNGQ10_BL_MAX_INTENSITY; i++) {
		status = acpi_evaluate_object(ec_handle, "_Q63", NULL, NULL);
		if (ACPI_FAILURE(status))
			return -EIO;
	}
	for (i = 0; i < bd->props.brightness; i++) {
		status = acpi_evaluate_object(ec_handle, "_Q64", NULL, NULL);
		if (ACPI_FAILURE(status))
			return -EIO;
	}

	return 0;
}