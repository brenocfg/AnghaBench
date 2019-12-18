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
struct asus_wmi {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 int WMI_EVENT_MASK ; 
 int WMI_EVENT_QUEUE_END ; 
 int WMI_EVENT_QUEUE_SIZE ; 
 int /*<<< orphan*/  WMI_EVENT_VALUE_ATK ; 
 int asus_wmi_get_event_code (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_warn (char*,...) ; 

__attribute__((used)) static int asus_wmi_notify_queue_flush(struct asus_wmi *asus)
{
	int code;
	int i;

	for (i = 0; i < WMI_EVENT_QUEUE_SIZE + 1; i++) {
		code = asus_wmi_get_event_code(WMI_EVENT_VALUE_ATK);
		if (code < 0) {
			pr_warn("Failed to get event during flush: %d\n", code);
			return code;
		}

		if (code == WMI_EVENT_QUEUE_END || code == WMI_EVENT_MASK)
			return 0;
	}

	pr_warn("Failed to flush event queue\n");
	return -EIO;
}