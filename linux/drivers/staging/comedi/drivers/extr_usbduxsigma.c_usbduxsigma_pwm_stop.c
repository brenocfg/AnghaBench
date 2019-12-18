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
struct usbduxsigma_private {scalar_t__ pwm_cmd_running; scalar_t__ pwm_urb; } ;
struct comedi_device {struct usbduxsigma_private* private; } ;

/* Variables and functions */
 int /*<<< orphan*/  usb_kill_urb (scalar_t__) ; 

__attribute__((used)) static void usbduxsigma_pwm_stop(struct comedi_device *dev, int do_unlink)
{
	struct usbduxsigma_private *devpriv = dev->private;

	if (do_unlink) {
		if (devpriv->pwm_urb)
			usb_kill_urb(devpriv->pwm_urb);
	}

	devpriv->pwm_cmd_running = 0;
}