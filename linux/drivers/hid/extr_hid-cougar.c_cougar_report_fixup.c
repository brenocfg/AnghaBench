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
 int HID_MAX_USAGES ; 
 int /*<<< orphan*/  hid_info (struct hid_device*,char*) ; 

__attribute__((used)) static __u8 *cougar_report_fixup(struct hid_device *hdev, __u8 *rdesc,
				 unsigned int *rsize)
{
	if (rdesc[2] == 0x09 && rdesc[3] == 0x02 &&
	    (rdesc[115] | rdesc[116] << 8) >= HID_MAX_USAGES) {
		hid_info(hdev,
			"usage count exceeds max: fixing up report descriptor\n");
		rdesc[115] = ((HID_MAX_USAGES-1) & 0xff);
		rdesc[116] = ((HID_MAX_USAGES-1) >> 8);
	}
	return rdesc;
}