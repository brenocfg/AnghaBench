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
union acpi_object {TYPE_1__ integer; int /*<<< orphan*/  type; } ;
typedef  int /*<<< orphan*/  u32 ;
struct key_entry {scalar_t__ type; } ;
struct acpi_buffer {scalar_t__ pointer; int /*<<< orphan*/ * member_1; int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/  acpi_status ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_ALLOCATE_BUFFER ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_TYPE_INTEGER ; 
 scalar_t__ KE_KEY ; 
 int /*<<< orphan*/  kfree (scalar_t__) ; 
 int /*<<< orphan*/  pr_debug (char*,long,...) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ) ; 
 struct key_entry* sparse_keymap_entry_from_scancode (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sparse_keymap_report_entry (int /*<<< orphan*/ ,struct key_entry*,int,int) ; 
 int /*<<< orphan*/  wmi_get_event_data (int /*<<< orphan*/ ,struct acpi_buffer*) ; 
 int /*<<< orphan*/  wmi_input_dev ; 

__attribute__((used)) static void wmi_notify(u32 value, void *context)
{
	struct acpi_buffer response = { ACPI_ALLOCATE_BUFFER, NULL };
	union acpi_object *obj;
	acpi_status status;
	long data = (long)context;

	pr_debug("event guid %li\n", data);
	status = wmi_get_event_data(value, &response);
	if (ACPI_FAILURE(status)) {
		pr_err("Bad event status 0x%x\n", status);
		return;
	}

	obj = (union acpi_object *)response.pointer;
	if (!obj)
		return;

	if (obj->type == ACPI_TYPE_INTEGER) {
		int eventcode = obj->integer.value;
		struct key_entry *key;

		key =
		    sparse_keymap_entry_from_scancode(wmi_input_dev, eventcode);
		if (key && key->type == KE_KEY)
			sparse_keymap_report_entry(wmi_input_dev, key, 1, true);
	}

	pr_debug("Type: %i    Eventcode: 0x%llx\n", obj->type,
		 obj->integer.value);
	kfree(response.pointer);
}