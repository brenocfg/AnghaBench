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
union acpi_object {scalar_t__ type; TYPE_1__ integer; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct intel_vbtn_priv {int /*<<< orphan*/  input_dev; } ;
struct acpi_buffer {union acpi_object* pointer; int /*<<< orphan*/ * member_1; int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/  acpi_status ;
typedef  int /*<<< orphan*/  acpi_handle ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_ALLOCATE_BUFFER ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_HANDLE (int /*<<< orphan*/ *) ; 
 scalar_t__ ACPI_TYPE_INTEGER ; 
 int /*<<< orphan*/  DMI_CHASSIS_TYPE ; 
 int DOCK_MODE_FLAG ; 
 int /*<<< orphan*/  SW_DOCK ; 
 int /*<<< orphan*/  SW_TABLET_MODE ; 
 int TABLET_MODE_FLAG ; 
 int /*<<< orphan*/  acpi_evaluate_object (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,struct acpi_buffer*) ; 
 struct intel_vbtn_priv* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 char* dmi_get_system_info (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_report_switch (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  kfree (union acpi_object*) ; 
 scalar_t__ strcmp (char const*,char*) ; 

__attribute__((used)) static void detect_tablet_mode(struct platform_device *device)
{
	const char *chassis_type = dmi_get_system_info(DMI_CHASSIS_TYPE);
	struct intel_vbtn_priv *priv = dev_get_drvdata(&device->dev);
	acpi_handle handle = ACPI_HANDLE(&device->dev);
	struct acpi_buffer vgbs_output = { ACPI_ALLOCATE_BUFFER, NULL };
	union acpi_object *obj;
	acpi_status status;
	int m;

	if (!(chassis_type && strcmp(chassis_type, "31") == 0))
		goto out;

	status = acpi_evaluate_object(handle, "VGBS", NULL, &vgbs_output);
	if (ACPI_FAILURE(status))
		goto out;

	obj = vgbs_output.pointer;
	if (!(obj && obj->type == ACPI_TYPE_INTEGER))
		goto out;

	m = !(obj->integer.value & TABLET_MODE_FLAG);
	input_report_switch(priv->input_dev, SW_TABLET_MODE, m);
	m = (obj->integer.value & DOCK_MODE_FLAG) ? 1 : 0;
	input_report_switch(priv->input_dev, SW_DOCK, m);
out:
	kfree(vgbs_output.pointer);
}