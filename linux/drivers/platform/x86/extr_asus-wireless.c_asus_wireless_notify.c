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
typedef  int u32 ;
struct asus_wireless_data {int /*<<< orphan*/  idev; } ;
struct acpi_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  KEY_RFKILL ; 
 struct asus_wireless_data* acpi_driver_data (struct acpi_device*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  dev_notice (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  input_report_key (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_sync (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void asus_wireless_notify(struct acpi_device *adev, u32 event)
{
	struct asus_wireless_data *data = acpi_driver_data(adev);

	dev_dbg(&adev->dev, "event=%#x\n", event);
	if (event != 0x88) {
		dev_notice(&adev->dev, "Unknown ASHS event: %#x\n", event);
		return;
	}
	input_report_key(data->idev, KEY_RFKILL, 1);
	input_sync(data->idev);
	input_report_key(data->idev, KEY_RFKILL, 0);
	input_sync(data->idev);
}