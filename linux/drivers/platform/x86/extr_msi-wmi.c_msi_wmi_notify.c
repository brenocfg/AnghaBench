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
union acpi_object {scalar_t__ type; TYPE_1__ integer; } ;
typedef  int /*<<< orphan*/  u32 ;
struct key_entry {scalar_t__ type; int keycode; int /*<<< orphan*/  code; } ;
struct acpi_buffer {scalar_t__ pointer; int /*<<< orphan*/ * member_1; int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/  ktime_t ;
typedef  scalar_t__ acpi_status ;
struct TYPE_4__ {scalar_t__ quirk_last_pressed; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_ALLOCATE_BUFFER ; 
 scalar_t__ ACPI_TYPE_INTEGER ; 
 scalar_t__ AE_OK ; 
 scalar_t__ KE_KEY ; 
 int /*<<< orphan*/  MSI_KEY_BRIGHTNESSDOWN ; 
 int /*<<< orphan*/  MSI_KEY_BRIGHTNESSUP ; 
 scalar_t__ backlight ; 
 TYPE_2__* event_wmi ; 
 int /*<<< orphan*/  kfree (scalar_t__) ; 
 int /*<<< orphan*/  ktime_get_real () ; 
 int /*<<< orphan*/  ktime_sub (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ktime_to_us (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  last_pressed ; 
 int /*<<< orphan*/  msi_wmi_input_dev ; 
 int /*<<< orphan*/  pr_debug (char*,int,...) ; 
 int /*<<< orphan*/  pr_info (char*,...) ; 
 struct key_entry* sparse_keymap_entry_from_scancode (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sparse_keymap_report_entry (int /*<<< orphan*/ ,struct key_entry*,int,int) ; 
 scalar_t__ wmi_get_event_data (int /*<<< orphan*/ ,struct acpi_buffer*) ; 

__attribute__((used)) static void msi_wmi_notify(u32 value, void *context)
{
	struct acpi_buffer response = { ACPI_ALLOCATE_BUFFER, NULL };
	struct key_entry *key;
	union acpi_object *obj;
	acpi_status status;

	status = wmi_get_event_data(value, &response);
	if (status != AE_OK) {
		pr_info("bad event status 0x%x\n", status);
		return;
	}

	obj = (union acpi_object *)response.pointer;

	if (obj && obj->type == ACPI_TYPE_INTEGER) {
		int eventcode = obj->integer.value;
		pr_debug("Eventcode: 0x%x\n", eventcode);
		key = sparse_keymap_entry_from_scancode(msi_wmi_input_dev,
				eventcode);
		if (!key) {
			pr_info("Unknown key pressed - %x\n", eventcode);
			goto msi_wmi_notify_exit;
		}

		if (event_wmi->quirk_last_pressed) {
			ktime_t cur = ktime_get_real();
			ktime_t diff = ktime_sub(cur, last_pressed);
			/* Ignore event if any event happened in a 50 ms
			   timeframe -> Key press may result in 10-20 GPEs */
			if (ktime_to_us(diff) < 1000 * 50) {
				pr_debug("Suppressed key event 0x%X - "
					 "Last press was %lld us ago\n",
					 key->code, ktime_to_us(diff));
				goto msi_wmi_notify_exit;
			}
			last_pressed = cur;
		}

		if (key->type == KE_KEY &&
		/* Brightness is served via acpi video driver */
		(backlight ||
		(key->code != MSI_KEY_BRIGHTNESSUP &&
		key->code != MSI_KEY_BRIGHTNESSDOWN))) {
			pr_debug("Send key: 0x%X - Input layer keycode: %d\n",
				 key->code, key->keycode);
			sparse_keymap_report_entry(msi_wmi_input_dev, key, 1,
						   true);
		}
	} else
		pr_info("Unknown event received\n");

msi_wmi_notify_exit:
	kfree(response.pointer);
}