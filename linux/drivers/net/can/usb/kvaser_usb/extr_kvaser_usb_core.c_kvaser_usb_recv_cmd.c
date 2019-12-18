#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct kvaser_usb {TYPE_1__* bulk_in; int /*<<< orphan*/  udev; } ;
struct TYPE_2__ {int /*<<< orphan*/  bEndpointAddress; } ;

/* Variables and functions */
 int /*<<< orphan*/  KVASER_USB_TIMEOUT ; 
 int usb_bulk_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_rcvbulkpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int kvaser_usb_recv_cmd(const struct kvaser_usb *dev, void *cmd, int len,
			int *actual_len)
{
	return usb_bulk_msg(dev->udev,
			    usb_rcvbulkpipe(dev->udev,
					    dev->bulk_in->bEndpointAddress),
			    cmd, len, actual_len, KVASER_USB_TIMEOUT);
}