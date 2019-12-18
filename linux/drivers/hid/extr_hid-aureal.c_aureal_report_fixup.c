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
struct hid_device {int /*<<< orphan*/  dev; } ;
typedef  int __u8 ;

/* Variables and functions */
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static __u8 *aureal_report_fixup(struct hid_device *hdev, __u8 *rdesc,
		unsigned int *rsize)
{
	if (*rsize >= 54 && rdesc[52] == 0x25 && rdesc[53] == 0x01) {
		dev_info(&hdev->dev, "fixing Aureal Cy se W-01RN USB_V3.1 report descriptor.\n");
		rdesc[53] = 0x65;
	}
	return rdesc;
}