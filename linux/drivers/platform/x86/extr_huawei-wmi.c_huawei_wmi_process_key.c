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
struct wmi_device {int /*<<< orphan*/  dev; } ;
struct key_entry {int dummy; } ;
struct huawei_wmi_priv {int /*<<< orphan*/  idev; } ;
struct acpi_buffer {scalar_t__ pointer; int /*<<< orphan*/ * member_1; int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/  acpi_status ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_ALLOCATE_BUFFER ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_TYPE_INTEGER ; 
 int /*<<< orphan*/  WMI0_EXPENSIVE_GUID ; 
 struct huawei_wmi_priv* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  kfree (scalar_t__) ; 
 struct key_entry* sparse_keymap_entry_from_scancode (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sparse_keymap_report_entry (int /*<<< orphan*/ ,struct key_entry const*,int,int) ; 
 int /*<<< orphan*/  wmi_query_block (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct acpi_buffer*) ; 

__attribute__((used)) static void huawei_wmi_process_key(struct wmi_device *wdev, int code)
{
	struct huawei_wmi_priv *priv = dev_get_drvdata(&wdev->dev);
	const struct key_entry *key;

	/*
	 * WMI0 uses code 0x80 to indicate a hotkey event.
	 * The actual key is fetched from the method WQ00
	 * using WMI0_EXPENSIVE_GUID.
	 */
	if (code == 0x80) {
		struct acpi_buffer response = { ACPI_ALLOCATE_BUFFER, NULL };
		union acpi_object *obj;
		acpi_status status;

		status = wmi_query_block(WMI0_EXPENSIVE_GUID, 0, &response);
		if (ACPI_FAILURE(status))
			return;

		obj = (union acpi_object *)response.pointer;
		if (obj && obj->type == ACPI_TYPE_INTEGER)
			code = obj->integer.value;

		kfree(response.pointer);
	}

	key = sparse_keymap_entry_from_scancode(priv->idev, code);
	if (!key) {
		dev_info(&wdev->dev, "Unknown key pressed, code: 0x%04x\n", code);
		return;
	}

	sparse_keymap_report_entry(priv->idev, key, 1, true);
}