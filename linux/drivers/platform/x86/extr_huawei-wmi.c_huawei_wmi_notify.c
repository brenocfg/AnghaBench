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
struct TYPE_2__ {int /*<<< orphan*/  value; } ;
union acpi_object {scalar_t__ type; TYPE_1__ integer; } ;
struct wmi_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ ACPI_TYPE_INTEGER ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,scalar_t__) ; 
 int /*<<< orphan*/  huawei_wmi_process_key (struct wmi_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void huawei_wmi_notify(struct wmi_device *wdev,
		union acpi_object *obj)
{
	if (obj->type == ACPI_TYPE_INTEGER)
		huawei_wmi_process_key(wdev, obj->integer.value);
	else
		dev_info(&wdev->dev, "Bad response type %d\n", obj->type);
}