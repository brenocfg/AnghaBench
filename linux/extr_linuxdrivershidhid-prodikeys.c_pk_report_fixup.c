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

__attribute__((used)) static __u8 *pk_report_fixup(struct hid_device *hdev, __u8 *rdesc,
		unsigned int *rsize)
{
	if (*rsize == 178 &&
	      rdesc[111] == 0x06 && rdesc[112] == 0x00 &&
	      rdesc[113] == 0xff) {
		hid_info(hdev,
			 "fixing up pc-midi keyboard report descriptor\n");

		rdesc[144] = 0x18; /* report 4: was 0x10 report count */
	}
	return rdesc;
}