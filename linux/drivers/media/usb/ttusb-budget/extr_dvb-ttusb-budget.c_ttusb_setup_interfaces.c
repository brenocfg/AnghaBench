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
struct ttusb {int /*<<< orphan*/  dev; int /*<<< orphan*/  isoc_in_pipe; int /*<<< orphan*/  bulk_in_pipe; int /*<<< orphan*/  bulk_out_pipe; } ;

/* Variables and functions */
 int /*<<< orphan*/  usb_rcvbulkpipe (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usb_rcvisocpipe (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usb_set_interface (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  usb_sndbulkpipe (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ttusb_setup_interfaces(struct ttusb *ttusb)
{
	usb_set_interface(ttusb->dev, 1, 1);

	ttusb->bulk_out_pipe = usb_sndbulkpipe(ttusb->dev, 1);
	ttusb->bulk_in_pipe = usb_rcvbulkpipe(ttusb->dev, 1);
	ttusb->isoc_in_pipe = usb_rcvisocpipe(ttusb->dev, 2);

	return 0;
}