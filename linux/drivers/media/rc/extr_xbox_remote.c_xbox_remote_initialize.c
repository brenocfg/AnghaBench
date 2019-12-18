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
struct xbox_remote {int /*<<< orphan*/  inbuf; int /*<<< orphan*/  irq_urb; struct usb_device* udev; } ;
struct usb_endpoint_descriptor {int /*<<< orphan*/  bInterval; int /*<<< orphan*/  bEndpointAddress; } ;
struct usb_device {int dummy; } ;

/* Variables and functions */
 int DATA_BUFSIZE ; 
 int /*<<< orphan*/  usb_fill_int_urb (int /*<<< orphan*/ ,struct usb_device*,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct xbox_remote*,int /*<<< orphan*/ ) ; 
 int usb_maxpacket (struct usb_device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_pipeout (int) ; 
 int usb_rcvintpipe (struct usb_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xbox_remote_irq_in ; 

__attribute__((used)) static int xbox_remote_initialize(struct xbox_remote *xbox_remote,
				  struct usb_endpoint_descriptor *endpoint_in)
{
	struct usb_device *udev = xbox_remote->udev;
	int pipe, maxp;

	/* Set up irq_urb */
	pipe = usb_rcvintpipe(udev, endpoint_in->bEndpointAddress);
	maxp = usb_maxpacket(udev, pipe, usb_pipeout(pipe));
	maxp = (maxp > DATA_BUFSIZE) ? DATA_BUFSIZE : maxp;

	usb_fill_int_urb(xbox_remote->irq_urb, udev, pipe, xbox_remote->inbuf,
			 maxp, xbox_remote_irq_in, xbox_remote,
			 endpoint_in->bInterval);

	return 0;
}