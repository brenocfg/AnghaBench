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
typedef  int /*<<< orphan*/  u8 ;
struct hidpp_device {int quirks; } ;
struct hid_device {scalar_t__ group; } ;

/* Variables and functions */
 int HIDPP_QUIRK_HIDPP_CONSUMER_VENDOR_KEYS ; 
 scalar_t__ HID_GROUP_LOGITECH_27MHZ_DEVICE ; 
 struct hidpp_device* hid_get_drvdata (struct hid_device*) ; 
 int /*<<< orphan*/ * hidpp10_consumer_keys_report_fixup (struct hidpp_device*,int /*<<< orphan*/ *,unsigned int*) ; 

__attribute__((used)) static u8 *hidpp_report_fixup(struct hid_device *hdev, u8 *rdesc,
			      unsigned int *rsize)
{
	struct hidpp_device *hidpp = hid_get_drvdata(hdev);

	if (!hidpp)
		return rdesc;

	/* For 27 MHz keyboards the quirk gets set after hid_parse. */
	if (hdev->group == HID_GROUP_LOGITECH_27MHZ_DEVICE ||
	    (hidpp->quirks & HIDPP_QUIRK_HIDPP_CONSUMER_VENDOR_KEYS))
		rdesc = hidpp10_consumer_keys_report_fixup(hidpp, rdesc, rsize);

	return rdesc;
}