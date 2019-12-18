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
struct hso_serial {int num_rx_urbs; int /*<<< orphan*/  port; int /*<<< orphan*/  tx_data; int /*<<< orphan*/  tx_buffer; int /*<<< orphan*/  tx_urb; int /*<<< orphan*/ * rx_data; int /*<<< orphan*/ * rx_urb; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tty_port_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_free_urb (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hso_serial_common_free(struct hso_serial *serial)
{
	int i;

	for (i = 0; i < serial->num_rx_urbs; i++) {
		/* unlink and free RX URB */
		usb_free_urb(serial->rx_urb[i]);
		/* free the RX buffer */
		kfree(serial->rx_data[i]);
	}

	/* unlink and free TX URB */
	usb_free_urb(serial->tx_urb);
	kfree(serial->tx_buffer);
	kfree(serial->tx_data);
	tty_port_destroy(&serial->port);
}