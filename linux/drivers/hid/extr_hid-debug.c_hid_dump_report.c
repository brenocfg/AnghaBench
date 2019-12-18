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
typedef  int u8 ;
struct hid_report_enum {scalar_t__ numbered; } ;
struct hid_device {struct hid_report_enum* report_enum; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 scalar_t__ HID_DEBUG_BUFSIZE ; 
 int /*<<< orphan*/  hid_debug_event (struct hid_device*,char*) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kmalloc (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,scalar_t__,char*,int,...) ; 

void hid_dump_report(struct hid_device *hid, int type, u8 *data,
		int size)
{
	struct hid_report_enum *report_enum;
	char *buf;
	unsigned int i;

	buf = kmalloc(HID_DEBUG_BUFSIZE, GFP_ATOMIC);

	if (!buf)
		return;

	report_enum = hid->report_enum + type;

	/* dump the report */
	snprintf(buf, HID_DEBUG_BUFSIZE - 1,
			"\nreport (size %u) (%snumbered) = ", size,
			report_enum->numbered ? "" : "un");
	hid_debug_event(hid, buf);

	for (i = 0; i < size; i++) {
		snprintf(buf, HID_DEBUG_BUFSIZE - 1,
				" %02x", data[i]);
		hid_debug_event(hid, buf);
	}
	hid_debug_event(hid, "\n");
	kfree(buf);
}