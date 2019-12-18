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
typedef  scalar_t__ u32 ;
struct asus_wmi {int /*<<< orphan*/  wmi_event_queue; } ;

/* Variables and functions */
 int WMI_EVENT_MASK ; 
 int WMI_EVENT_QUEUE_END ; 
 int WMI_EVENT_QUEUE_SIZE ; 
 scalar_t__ WMI_EVENT_VALUE_ATK ; 
 int asus_wmi_get_event_code (scalar_t__) ; 
 int /*<<< orphan*/  asus_wmi_handle_event_code (int,struct asus_wmi*) ; 
 int /*<<< orphan*/  pr_warn (char*,int) ; 

__attribute__((used)) static void asus_wmi_notify(u32 value, void *context)
{
	struct asus_wmi *asus = context;
	int code;
	int i;

	for (i = 0; i < WMI_EVENT_QUEUE_SIZE + 1; i++) {
		code = asus_wmi_get_event_code(value);
		if (code < 0) {
			pr_warn("Failed to get notify code: %d\n", code);
			return;
		}

		if (code == WMI_EVENT_QUEUE_END || code == WMI_EVENT_MASK)
			return;

		asus_wmi_handle_event_code(code, asus);

		/*
		 * Double check that queue is present:
		 * ATK (with queue) uses 0xff, ASUSWMI (without) 0xd2.
		 */
		if (!asus->wmi_event_queue || value != WMI_EVENT_VALUE_ATK)
			return;
	}

	pr_warn("Failed to process event queue, last code: 0x%x\n", code);
}