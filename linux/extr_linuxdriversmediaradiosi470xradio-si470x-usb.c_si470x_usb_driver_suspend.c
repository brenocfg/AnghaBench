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
struct usb_interface {int /*<<< orphan*/  dev; } ;
struct si470x_device {int /*<<< orphan*/  read_queue; scalar_t__ int_in_urb; scalar_t__ int_in_running; } ;
typedef  int /*<<< orphan*/  pm_message_t ;

/* Variables and functions */
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  si470x_stop (struct si470x_device*) ; 
 struct si470x_device* usb_get_intfdata (struct usb_interface*) ; 
 int /*<<< orphan*/  usb_kill_urb (scalar_t__) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int si470x_usb_driver_suspend(struct usb_interface *intf,
		pm_message_t message)
{
	struct si470x_device *radio = usb_get_intfdata(intf);

	dev_info(&intf->dev, "suspending now...\n");

	/* shutdown interrupt handler */
	if (radio->int_in_running) {
		radio->int_in_running = 0;
		if (radio->int_in_urb)
			usb_kill_urb(radio->int_in_urb);
	}

	/* cancel read processes */
	wake_up_interruptible(&radio->read_queue);

	/* stop radio */
	si470x_stop(radio);
	return 0;
}