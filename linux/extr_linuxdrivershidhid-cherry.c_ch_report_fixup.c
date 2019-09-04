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

__attribute__((used)) static __u8 *ch_report_fixup(struct hid_device *hdev, __u8 *rdesc,
		unsigned int *rsize)
{
	if (*rsize >= 18 && rdesc[11] == 0x3c && rdesc[12] == 0x02) {
		hid_info(hdev, "fixing up Cherry Cymotion report descriptor\n");
		rdesc[11] = rdesc[16] = 0xff;
		rdesc[12] = rdesc[17] = 0x03;
	}
	return rdesc;
}