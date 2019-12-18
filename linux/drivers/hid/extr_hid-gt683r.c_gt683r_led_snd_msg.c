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
struct gt683r_led {int /*<<< orphan*/  hdev; } ;

/* Variables and functions */
 int EIO ; 
 int GT683R_BUFFER_SIZE ; 
 int /*<<< orphan*/  HID_FEATURE_REPORT ; 
 int /*<<< orphan*/  HID_REQ_SET_REPORT ; 
 int /*<<< orphan*/  hid_err (int /*<<< orphan*/ ,char*,int) ; 
 int hid_hw_raw_request (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int gt683r_led_snd_msg(struct gt683r_led *led, u8 *msg)
{
	int ret;

	ret = hid_hw_raw_request(led->hdev, msg[0], msg, GT683R_BUFFER_SIZE,
				HID_FEATURE_REPORT, HID_REQ_SET_REPORT);
	if (ret != GT683R_BUFFER_SIZE) {
		hid_err(led->hdev,
			"failed to send set report request: %i\n", ret);
		if (ret < 0)
			return ret;
		return -EIO;
	}

	return 0;
}