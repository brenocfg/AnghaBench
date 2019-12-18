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
struct hid_device {scalar_t__ product; } ;
typedef  int /*<<< orphan*/  __u8 ;

/* Variables and functions */
 scalar_t__ USB_DEVICE_ID_SAMSUNG_IR_REMOTE ; 
 int /*<<< orphan*/ * samsung_irda_report_fixup (struct hid_device*,int /*<<< orphan*/ *,unsigned int*) ; 

__attribute__((used)) static __u8 *samsung_report_fixup(struct hid_device *hdev, __u8 *rdesc,
	unsigned int *rsize)
{
	if (USB_DEVICE_ID_SAMSUNG_IR_REMOTE == hdev->product)
		rdesc = samsung_irda_report_fixup(hdev, rdesc, rsize);
	return rdesc;
}