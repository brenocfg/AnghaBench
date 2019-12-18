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
struct hidpp_device {int /*<<< orphan*/  hid_dev; } ;

/* Variables and functions */
 int HIDPP_SUB_ID_CONSUMER_VENDOR_KEYS ; 
 int /*<<< orphan*/  HID_INPUT_REPORT ; 
 int REPORT_ID_HIDPP_SHORT ; 
 int /*<<< orphan*/  hid_report_raw_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int,int) ; 
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 

__attribute__((used)) static int hidpp10_consumer_keys_raw_event(struct hidpp_device *hidpp,
					   u8 *data, int size)
{
	u8 consumer_report[5];

	if (size < 7)
		return 0;

	if (data[0] != REPORT_ID_HIDPP_SHORT ||
	    data[2] != HIDPP_SUB_ID_CONSUMER_VENDOR_KEYS)
		return 0;

	/*
	 * Build a normal consumer report (3) out of the data, this detour
	 * is necessary to get some keyboards to report their 0x10xx usages.
	 */
	consumer_report[0] = 0x03;
	memcpy(&consumer_report[1], &data[3], 4);
	/* We are called from atomic context */
	hid_report_raw_event(hidpp->hid_dev, HID_INPUT_REPORT,
			     consumer_report, 5, 1);

	return 1;
}