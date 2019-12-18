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
struct TYPE_4__ {int value; } ;
union acpi_object {TYPE_2__ integer; int /*<<< orphan*/  type; } ;
struct led_classdev {TYPE_1__* dev; } ;
struct huawei_wmi_priv {int /*<<< orphan*/  acpi_method; int /*<<< orphan*/  handle; } ;
struct acpi_object_list {int /*<<< orphan*/  count; union acpi_object* pointer; } ;
typedef  enum led_brightness { ____Placeholder_led_brightness } led_brightness ;
typedef  int /*<<< orphan*/  acpi_status ;
struct TYPE_3__ {int /*<<< orphan*/  parent; } ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_TYPE_INTEGER ; 
 int /*<<< orphan*/  ARRAY_SIZE (union acpi_object*) ; 
 int EINVAL ; 
 int ENXIO ; 
 int /*<<< orphan*/  acpi_evaluate_object (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct acpi_object_list*,int /*<<< orphan*/ *) ; 
 struct huawei_wmi_priv* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int huawei_wmi_micmute_led_set(struct led_classdev *led_cdev,
		enum led_brightness brightness)
{
	struct huawei_wmi_priv *priv = dev_get_drvdata(led_cdev->dev->parent);
	acpi_status status;
	union acpi_object args[3];
	struct acpi_object_list arg_list = {
		.pointer = args,
		.count = ARRAY_SIZE(args),
	};

	args[0].type = args[1].type = args[2].type = ACPI_TYPE_INTEGER;
	args[1].integer.value = 0x04;

	if (strcmp(priv->acpi_method, "SPIN") == 0) {
		args[0].integer.value = 0;
		args[2].integer.value = brightness ? 1 : 0;
	} else if (strcmp(priv->acpi_method, "WPIN") == 0) {
		args[0].integer.value = 1;
		args[2].integer.value = brightness ? 0 : 1;
	} else {
		return -EINVAL;
	}

	status = acpi_evaluate_object(priv->handle, priv->acpi_method, &arg_list, NULL);
	if (ACPI_FAILURE(status))
		return -ENXIO;

	return 0;
}