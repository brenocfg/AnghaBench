#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct urb {scalar_t__ actual_length; } ;
struct TYPE_2__ {scalar_t__ count; } ;
struct hso_serial {scalar_t__ rx_state; TYPE_1__ port; struct urb** rx_urb; } ;

/* Variables and functions */
 scalar_t__ RX_IDLE ; 
 scalar_t__ RX_PENDING ; 
 scalar_t__ RX_SENT ; 
 int /*<<< orphan*/  hso_mux_serial_read (struct hso_serial*) ; 
 int put_rxbuf_data (struct urb*,struct hso_serial*) ; 

__attribute__((used)) static void put_rxbuf_data_and_resubmit_ctrl_urb(struct hso_serial *serial)
{
	int count = 0;
	struct urb *urb;

	urb = serial->rx_urb[0];
	if (serial->port.count > 0) {
		count = put_rxbuf_data(urb, serial);
		if (count == -1)
			return;
	}
	/* Re issue a read as long as we receive data. */

	if (count == 0 && ((urb->actual_length != 0) ||
			   (serial->rx_state == RX_PENDING))) {
		serial->rx_state = RX_SENT;
		hso_mux_serial_read(serial);
	} else
		serial->rx_state = RX_IDLE;
}