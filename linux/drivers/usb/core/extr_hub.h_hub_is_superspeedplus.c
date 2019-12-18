#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ bDeviceProtocol; int /*<<< orphan*/  bcdUSB; } ;
struct usb_device {TYPE_2__* bos; TYPE_1__ descriptor; } ;
struct TYPE_4__ {scalar_t__ ssp_cap; } ;

/* Variables and functions */
 scalar_t__ USB_HUB_PR_SS ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int hub_is_superspeedplus(struct usb_device *hdev)
{
	return (hdev->descriptor.bDeviceProtocol == USB_HUB_PR_SS &&
		le16_to_cpu(hdev->descriptor.bcdUSB) >= 0x0310 &&
		hdev->bos->ssp_cap);
}