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
typedef  union acpi_object {int dummy; } acpi_object ;
struct xiaomi_wmi {int /*<<< orphan*/  input_dev; int /*<<< orphan*/  key_code; } ;
struct wmi_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 struct xiaomi_wmi* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  input_report_key (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_sync (int /*<<< orphan*/ ) ; 

void xiaomi_wmi_notify(struct wmi_device *wdev, union acpi_object *dummy)
{
	struct xiaomi_wmi *data;

	if (wdev == NULL)
		return;

	data = dev_get_drvdata(&wdev->dev);
	if (data == NULL)
		return;

	input_report_key(data->input_dev, data->key_code, 1);
	input_sync(data->input_dev);
	input_report_key(data->input_dev, data->key_code, 0);
	input_sync(data->input_dev);
}