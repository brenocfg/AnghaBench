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
struct esd_usb2_msg {int dummy; } ;
struct esd_usb2 {int /*<<< orphan*/  udev; } ;

/* Variables and functions */
 int usb_bulk_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct esd_usb2_msg*,int,int*,int) ; 
 int /*<<< orphan*/  usb_rcvbulkpipe (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int esd_usb2_wait_msg(struct esd_usb2 *dev,
			     struct esd_usb2_msg *msg)
{
	int actual_length;

	return usb_bulk_msg(dev->udev,
			    usb_rcvbulkpipe(dev->udev, 1),
			    msg,
			    sizeof(*msg),
			    &actual_length,
			    1000);
}