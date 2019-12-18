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
struct hid_device {int dummy; } ;

/* Variables and functions */
 int EAGAIN ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  HID_REQ_SET_REPORT ; 
 int /*<<< orphan*/  hid_err (struct hid_device*,char*,int) ; 
 int hid_hw_raw_request (struct hid_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int wacom_set_report(struct hid_device *hdev, u8 type, u8 *buf,
			    size_t size, unsigned int retries)
{
	int retval;

	do {
		retval = hid_hw_raw_request(hdev, buf[0], buf, size, type,
				HID_REQ_SET_REPORT);
	} while ((retval == -ETIMEDOUT || retval == -EAGAIN) && --retries);

	if (retval < 0)
		hid_err(hdev, "wacom_set_report: ran out of retries "
			"(last error = %d)\n", retval);

	return retval;
}