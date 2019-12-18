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
struct urb {scalar_t__ transfer_buffer; struct usb_serial_port* context; } ;
struct garmin_data {scalar_t__ mode; } ;
typedef  int /*<<< orphan*/  __u8 ;

/* Variables and functions */
 scalar_t__ GARMIN_LAYERID_APPL ; 
 scalar_t__ MODE_GARMIN_SERIAL ; 
 scalar_t__ getLayerId (scalar_t__) ; 
 int /*<<< orphan*/  gsp_send_ack (struct garmin_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (scalar_t__) ; 
 struct garmin_data* usb_get_serial_port_data (struct usb_serial_port*) ; 
 int /*<<< orphan*/  usb_serial_port_softint (struct usb_serial_port*) ; 

__attribute__((used)) static void garmin_write_bulk_callback(struct urb *urb)
{
	struct usb_serial_port *port = urb->context;

	if (port) {
		struct garmin_data *garmin_data_p =
					usb_get_serial_port_data(port);

		if (getLayerId(urb->transfer_buffer) == GARMIN_LAYERID_APPL) {

			if (garmin_data_p->mode == MODE_GARMIN_SERIAL) {
				gsp_send_ack(garmin_data_p,
					((__u8 *)urb->transfer_buffer)[4]);
			}
		}
		usb_serial_port_softint(port);
	}

	/* Ignore errors that resulted from garmin_write_bulk with
	   dismiss_ack = 1 */

	/* free up the transfer buffer, as usb_free_urb() does not do this */
	kfree(urb->transfer_buffer);
}