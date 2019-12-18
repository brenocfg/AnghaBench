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
 int /*<<< orphan*/  hid_info (struct hid_device*,char*) ; 

__attribute__((used)) static __u8 *ortek_report_fixup(struct hid_device *hdev, __u8 *rdesc,
		unsigned int *rsize)
{
	if (*rsize >= 56 && rdesc[54] == 0x25 && rdesc[55] == 0x01) {
		hid_info(hdev, "Fixing up logical maximum in report descriptor (Ortek)\n");
		rdesc[55] = 0x92;
	} else if (*rsize >= 54 && rdesc[52] == 0x25 && rdesc[53] == 0x01) {
		hid_info(hdev, "Fixing up logical maximum in report descriptor (Skycable)\n");
		rdesc[53] = 0x65;
	}
	return rdesc;
}