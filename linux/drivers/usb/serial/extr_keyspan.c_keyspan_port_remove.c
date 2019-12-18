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
struct keyspan_port_private {struct keyspan_port_private** in_buffer; struct keyspan_port_private** out_buffer; struct keyspan_port_private* inack_buffer; struct keyspan_port_private* outcont_buffer; int /*<<< orphan*/ * out_urbs; int /*<<< orphan*/ * in_urbs; int /*<<< orphan*/  outcont_urb; int /*<<< orphan*/  inack_urb; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct keyspan_port_private**) ; 
 int /*<<< orphan*/  kfree (struct keyspan_port_private*) ; 
 int /*<<< orphan*/  usb_free_urb (int /*<<< orphan*/ ) ; 
 struct keyspan_port_private* usb_get_serial_port_data (struct usb_serial_port*) ; 
 int /*<<< orphan*/  usb_kill_urb (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int keyspan_port_remove(struct usb_serial_port *port)
{
	struct keyspan_port_private *p_priv;
	int i;

	p_priv = usb_get_serial_port_data(port);

	usb_kill_urb(p_priv->inack_urb);
	usb_kill_urb(p_priv->outcont_urb);
	for (i = 0; i < 2; i++) {
		usb_kill_urb(p_priv->in_urbs[i]);
		usb_kill_urb(p_priv->out_urbs[i]);
	}

	usb_free_urb(p_priv->inack_urb);
	usb_free_urb(p_priv->outcont_urb);
	for (i = 0; i < 2; i++) {
		usb_free_urb(p_priv->in_urbs[i]);
		usb_free_urb(p_priv->out_urbs[i]);
	}

	kfree(p_priv->outcont_buffer);
	kfree(p_priv->inack_buffer);
	for (i = 0; i < ARRAY_SIZE(p_priv->out_buffer); ++i)
		kfree(p_priv->out_buffer[i]);
	for (i = 0; i < ARRAY_SIZE(p_priv->in_buffer); ++i)
		kfree(p_priv->in_buffer[i]);

	kfree(p_priv);

	return 0;
}