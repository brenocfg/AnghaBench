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
struct keyspan_serial_private {int /*<<< orphan*/  glocont_buf; void* glocont_urb; int /*<<< orphan*/  indat_buf; void* indat_urb; int /*<<< orphan*/  instat_buf; void* instat_urb; struct keyspan_device_details* device_details; } ;
struct keyspan_device_details {size_t msg_format; int /*<<< orphan*/  glocont_endpoint; int /*<<< orphan*/  indat_endpoint; int /*<<< orphan*/  instat_endpoint; } ;
struct callbacks {int /*<<< orphan*/  glocont_callback; int /*<<< orphan*/  instat_callback; } ;

/* Variables and functions */
 int /*<<< orphan*/  GLOCONT_BUFLEN ; 
 int /*<<< orphan*/  INDAT49W_BUFLEN ; 
 int /*<<< orphan*/  INSTAT_BUFLEN ; 
 int /*<<< orphan*/  USB_DIR_IN ; 
 int /*<<< orphan*/  USB_DIR_OUT ; 
 struct callbacks* keyspan_callbacks ; 
 void* keyspan_setup_urb (struct usb_serial*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct usb_serial*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usa49wg_indat_callback ; 
 struct keyspan_serial_private* usb_get_serial_data (struct usb_serial*) ; 

__attribute__((used)) static void keyspan_setup_urbs(struct usb_serial *serial)
{
	struct keyspan_serial_private 	*s_priv;
	const struct keyspan_device_details	*d_details;
	struct callbacks		*cback;

	s_priv = usb_get_serial_data(serial);
	d_details = s_priv->device_details;

	/* Setup values for the various callback routines */
	cback = &keyspan_callbacks[d_details->msg_format];

	/* Allocate and set up urbs for each one that is in use,
	   starting with instat endpoints */
	s_priv->instat_urb = keyspan_setup_urb
		(serial, d_details->instat_endpoint, USB_DIR_IN,
		 serial, s_priv->instat_buf, INSTAT_BUFLEN,
		 cback->instat_callback);

	s_priv->indat_urb = keyspan_setup_urb
		(serial, d_details->indat_endpoint, USB_DIR_IN,
		 serial, s_priv->indat_buf, INDAT49W_BUFLEN,
		 usa49wg_indat_callback);

	s_priv->glocont_urb = keyspan_setup_urb
		(serial, d_details->glocont_endpoint, USB_DIR_OUT,
		 serial, s_priv->glocont_buf, GLOCONT_BUFLEN,
		 cback->glocont_callback);
}