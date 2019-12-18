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
struct usb_serial {int dummy; } ;
struct keyspan_serial_private {struct keyspan_serial_private* instat_buf; struct keyspan_serial_private* indat_buf; struct keyspan_serial_private* glocont_buf; struct keyspan_serial_private* ctrl_buf; int /*<<< orphan*/  glocont_urb; int /*<<< orphan*/  indat_urb; int /*<<< orphan*/  instat_urb; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct keyspan_serial_private*) ; 
 int /*<<< orphan*/  usb_free_urb (int /*<<< orphan*/ ) ; 
 struct keyspan_serial_private* usb_get_serial_data (struct usb_serial*) ; 
 int /*<<< orphan*/  usb_kill_urb (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void keyspan_release(struct usb_serial *serial)
{
	struct keyspan_serial_private *s_priv;

	s_priv = usb_get_serial_data(serial);

	/* Make sure to unlink the URBs submitted in attach. */
	usb_kill_urb(s_priv->instat_urb);
	usb_kill_urb(s_priv->indat_urb);

	usb_free_urb(s_priv->instat_urb);
	usb_free_urb(s_priv->indat_urb);
	usb_free_urb(s_priv->glocont_urb);

	kfree(s_priv->ctrl_buf);
	kfree(s_priv->glocont_buf);
	kfree(s_priv->indat_buf);
	kfree(s_priv->instat_buf);

	kfree(s_priv);
}