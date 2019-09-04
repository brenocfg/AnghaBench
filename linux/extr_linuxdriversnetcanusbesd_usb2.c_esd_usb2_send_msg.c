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
struct TYPE_3__ {int len; } ;
struct TYPE_4__ {TYPE_1__ hdr; } ;
struct esd_usb2_msg {TYPE_2__ msg; } ;
struct esd_usb2 {int /*<<< orphan*/  udev; } ;

/* Variables and functions */
 int usb_bulk_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct esd_usb2_msg*,int,int*,int) ; 
 int /*<<< orphan*/  usb_sndbulkpipe (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int esd_usb2_send_msg(struct esd_usb2 *dev, struct esd_usb2_msg *msg)
{
	int actual_length;

	return usb_bulk_msg(dev->udev,
			    usb_sndbulkpipe(dev->udev, 2),
			    msg,
			    msg->msg.hdr.len << 2,
			    &actual_length,
			    1000);
}