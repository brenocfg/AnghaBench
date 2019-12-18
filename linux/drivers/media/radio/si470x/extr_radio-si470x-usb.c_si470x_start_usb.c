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
struct si470x_device {int int_in_running; int status_rssi_auto_update; int /*<<< orphan*/  hdl; TYPE_2__* intf; int /*<<< orphan*/  int_in_urb; TYPE_1__* int_in_endpoint; int /*<<< orphan*/  int_in_buffer; int /*<<< orphan*/  usbdev; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  bInterval; int /*<<< orphan*/  wMaxPacketSize; int /*<<< orphan*/  bEndpointAddress; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mb () ; 
 int /*<<< orphan*/  si470x_int_in_callback ; 
 int si470x_start (struct si470x_device*) ; 
 int /*<<< orphan*/  usb_fill_int_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct si470x_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_rcvintpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int usb_submit_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_setup (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int si470x_start_usb(struct si470x_device *radio)
{
	int retval;

	/* initialize interrupt urb */
	usb_fill_int_urb(radio->int_in_urb, radio->usbdev,
			usb_rcvintpipe(radio->usbdev,
				radio->int_in_endpoint->bEndpointAddress),
			radio->int_in_buffer,
			le16_to_cpu(radio->int_in_endpoint->wMaxPacketSize),
			si470x_int_in_callback,
			radio,
			radio->int_in_endpoint->bInterval);

	radio->int_in_running = 1;
	mb();

	retval = usb_submit_urb(radio->int_in_urb, GFP_KERNEL);
	if (retval) {
		dev_info(&radio->intf->dev,
				"submitting int urb failed (%d)\n", retval);
		radio->int_in_running = 0;
	}
	radio->status_rssi_auto_update = radio->int_in_running;

	/* start radio */
	retval = si470x_start(radio);
	if (retval < 0)
		return retval;

	v4l2_ctrl_handler_setup(&radio->hdl);

	return retval;
}