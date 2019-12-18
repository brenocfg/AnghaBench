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
struct keyspan_serial_private {int /*<<< orphan*/  indat_urb; int /*<<< orphan*/  glocont_urb; int /*<<< orphan*/  instat_urb; } ;

/* Variables and functions */
 struct keyspan_serial_private* usb_get_serial_data (struct usb_serial*) ; 
 int /*<<< orphan*/  usb_kill_urb (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void keyspan_disconnect(struct usb_serial *serial)
{
	struct keyspan_serial_private *s_priv;

	s_priv = usb_get_serial_data(serial);

	usb_kill_urb(s_priv->instat_urb);
	usb_kill_urb(s_priv->glocont_urb);
	usb_kill_urb(s_priv->indat_urb);
}