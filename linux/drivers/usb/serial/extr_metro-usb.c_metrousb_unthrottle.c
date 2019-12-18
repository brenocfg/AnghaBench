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
struct usb_serial_port {int /*<<< orphan*/  interrupt_in_urb; } ;
struct tty_struct {int /*<<< orphan*/  dev; struct usb_serial_port* driver_data; } ;
struct metrousb_private {int /*<<< orphan*/  lock; scalar_t__ throttled; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct metrousb_private* usb_get_serial_port_data (struct usb_serial_port*) ; 
 int usb_submit_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void metrousb_unthrottle(struct tty_struct *tty)
{
	struct usb_serial_port *port = tty->driver_data;
	struct metrousb_private *metro_priv = usb_get_serial_port_data(port);
	unsigned long flags = 0;
	int result = 0;

	/* Set the private information for the port to resume reading data. */
	spin_lock_irqsave(&metro_priv->lock, flags);
	metro_priv->throttled = 0;
	spin_unlock_irqrestore(&metro_priv->lock, flags);

	/* Submit the urb to read from the port. */
	result = usb_submit_urb(port->interrupt_in_urb, GFP_ATOMIC);
	if (result)
		dev_err(tty->dev,
			"failed submitting interrupt in urb error code=%d\n",
			result);
}