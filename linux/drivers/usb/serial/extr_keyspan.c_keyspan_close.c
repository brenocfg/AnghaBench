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
struct usb_serial_port {int dummy; } ;
struct keyspan_port_private {int /*<<< orphan*/ * out_urbs; int /*<<< orphan*/ * in_urbs; int /*<<< orphan*/  inack_urb; scalar_t__ in_flip; scalar_t__ out_flip; scalar_t__ dtr_state; scalar_t__ rts_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  keyspan_send_setup (struct usb_serial_port*,int) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 struct keyspan_port_private* usb_get_serial_port_data (struct usb_serial_port*) ; 
 int /*<<< orphan*/  usb_kill_urb (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void keyspan_close(struct usb_serial_port *port)
{
	int			i;
	struct keyspan_port_private 	*p_priv;

	p_priv = usb_get_serial_port_data(port);

	p_priv->rts_state = 0;
	p_priv->dtr_state = 0;

	keyspan_send_setup(port, 2);
	/* pilot-xfer seems to work best with this delay */
	mdelay(100);

	p_priv->out_flip = 0;
	p_priv->in_flip = 0;

	usb_kill_urb(p_priv->inack_urb);
	for (i = 0; i < 2; i++) {
		usb_kill_urb(p_priv->in_urbs[i]);
		usb_kill_urb(p_priv->out_urbs[i]);
	}
}