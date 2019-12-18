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
struct TYPE_3__ {int value; } ;
union acpi_object {TYPE_1__ integer; int /*<<< orphan*/  type; } ;
struct delayed_led_classdev {int dummy; } ;
struct acpi_object_list {int member_0; union acpi_object* member_1; } ;
struct acpi_device {int /*<<< orphan*/  handle; } ;
typedef  enum led_brightness { ____Placeholder_led_brightness } led_brightness ;
struct TYPE_4__ {struct acpi_device* bus_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_TYPE_INTEGER ; 
 int /*<<< orphan*/  acpi_evaluate_integer (int /*<<< orphan*/ ,char*,struct acpi_object_list*,unsigned long long*) ; 
 TYPE_2__ lis3_dev ; 

__attribute__((used)) static void hpled_set(struct delayed_led_classdev *led_cdev, enum led_brightness value)
{
	struct acpi_device *dev = lis3_dev.bus_priv;
	unsigned long long ret; /* Not used when writing */
	union acpi_object in_obj[1];
	struct acpi_object_list args = { 1, in_obj };

	in_obj[0].type          = ACPI_TYPE_INTEGER;
	in_obj[0].integer.value = !!value;

	acpi_evaluate_integer(dev->handle, "ALED", &args, &ret);
}