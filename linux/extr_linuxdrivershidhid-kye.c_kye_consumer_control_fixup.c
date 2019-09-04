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
struct hid_device {int dummy; } ;
typedef  int __u8 ;

/* Variables and functions */
 int /*<<< orphan*/  hid_info (struct hid_device*,char*,char const*) ; 

__attribute__((used)) static __u8 *kye_consumer_control_fixup(struct hid_device *hdev, __u8 *rdesc,
		unsigned int *rsize, int offset, const char *device_name) {
	/*
	 * the fixup that need to be done:
	 *   - change Usage Maximum in the Consumer Control
	 *     (report ID 3) to a reasonable value
	 */
	if (*rsize >= offset + 31 &&
	    /* Usage Page (Consumer Devices) */
	    rdesc[offset] == 0x05 && rdesc[offset + 1] == 0x0c &&
	    /* Usage (Consumer Control) */
	    rdesc[offset + 2] == 0x09 && rdesc[offset + 3] == 0x01 &&
	    /*   Usage Maximum > 12287 */
	    rdesc[offset + 10] == 0x2a && rdesc[offset + 12] > 0x2f) {
		hid_info(hdev, "fixing up %s report descriptor\n", device_name);
		rdesc[offset + 12] = 0x2f;
	}
	return rdesc;
}