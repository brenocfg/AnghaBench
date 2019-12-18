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
struct TYPE_4__ {unsigned int* pointer; int /*<<< orphan*/  length; } ;
struct TYPE_3__ {unsigned int value; } ;
union acpi_object {int type; TYPE_2__ buffer; TYPE_1__ integer; } ;
typedef  int /*<<< orphan*/  u32 ;
struct dell_wmi_event {unsigned int* event; } ;
struct acpi_buffer {scalar_t__ pointer; int /*<<< orphan*/ * member_1; int /*<<< orphan*/  member_0; } ;
typedef  scalar_t__ acpi_status ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_ALLOCATE_BUFFER ; 
#define  ACPI_TYPE_BUFFER 129 
#define  ACPI_TYPE_INTEGER 128 
 scalar_t__ AE_OK ; 
 int /*<<< orphan*/  dell_wmi_aio_event_check (unsigned int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dell_wmi_aio_input_dev ; 
 int /*<<< orphan*/  kfree (union acpi_object*) ; 
 int /*<<< orphan*/  pr_info (char*,scalar_t__) ; 
 int /*<<< orphan*/  sparse_keymap_report_event (int /*<<< orphan*/ ,unsigned int,int,int) ; 
 scalar_t__ wmi_get_event_data (int /*<<< orphan*/ ,struct acpi_buffer*) ; 

__attribute__((used)) static void dell_wmi_aio_notify(u32 value, void *context)
{
	struct acpi_buffer response = { ACPI_ALLOCATE_BUFFER, NULL };
	union acpi_object *obj;
	struct dell_wmi_event *event;
	acpi_status status;

	status = wmi_get_event_data(value, &response);
	if (status != AE_OK) {
		pr_info("bad event status 0x%x\n", status);
		return;
	}

	obj = (union acpi_object *)response.pointer;
	if (obj) {
		unsigned int scancode = 0;

		switch (obj->type) {
		case ACPI_TYPE_INTEGER:
			/* Most All-In-One correctly return integer scancode */
			scancode = obj->integer.value;
			sparse_keymap_report_event(dell_wmi_aio_input_dev,
				scancode, 1, true);
			break;
		case ACPI_TYPE_BUFFER:
			if (dell_wmi_aio_event_check(obj->buffer.pointer,
						obj->buffer.length)) {
				event = (struct dell_wmi_event *)
					obj->buffer.pointer;
				scancode = event->event[0];
			} else {
				/* Broken machines return the scancode in a
				   buffer */
				if (obj->buffer.pointer &&
						obj->buffer.length > 0)
					scancode = obj->buffer.pointer[0];
			}
			if (scancode)
				sparse_keymap_report_event(
					dell_wmi_aio_input_dev,
					scancode, 1, true);
			break;
		}
	}
	kfree(obj);
}