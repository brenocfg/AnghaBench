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
struct hid_field {int /*<<< orphan*/  report; } ;
struct hid_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HID_UP_LED ; 
 int /*<<< orphan*/  USB_DIR_OUT ; 
 int hid_find_field_early (struct hid_device*,int /*<<< orphan*/ ,int,struct hid_field**) ; 
 int /*<<< orphan*/  hid_set_field (struct hid_field*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbhid_submit_report (struct hid_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void usbhid_set_leds(struct hid_device *hid)
{
	struct hid_field *field;
	int offset;

	if ((offset = hid_find_field_early(hid, HID_UP_LED, 0x01, &field)) != -1) {
		hid_set_field(field, offset, 0);
		usbhid_submit_report(hid, field->report, USB_DIR_OUT);
	}
}