#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct usb_tx_data_port {TYPE_3__* tx_data_list; } ;
struct TYPE_8__ {int /*<<< orphan*/ * urb; } ;
struct TYPE_5__ {int /*<<< orphan*/ * urb; } ;
struct usb_card_rec {TYPE_4__ tx_cmd; struct usb_tx_data_port* port; TYPE_2__* rx_data_list; int /*<<< orphan*/  rx_data_urb_pending; TYPE_1__ rx_cmd; int /*<<< orphan*/  rx_cmd_urb_pending; } ;
struct TYPE_7__ {int /*<<< orphan*/ * urb; } ;
struct TYPE_6__ {int /*<<< orphan*/ * urb; } ;

/* Variables and functions */
 int MWIFIEX_RX_DATA_URB ; 
 int MWIFIEX_TX_DATA_PORT ; 
 int MWIFIEX_TX_DATA_URB ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_free_urb (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_kill_urb (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mwifiex_usb_free(struct usb_card_rec *card)
{
	struct usb_tx_data_port *port;
	int i, j;

	if (atomic_read(&card->rx_cmd_urb_pending) && card->rx_cmd.urb)
		usb_kill_urb(card->rx_cmd.urb);

	usb_free_urb(card->rx_cmd.urb);
	card->rx_cmd.urb = NULL;

	if (atomic_read(&card->rx_data_urb_pending))
		for (i = 0; i < MWIFIEX_RX_DATA_URB; i++)
			if (card->rx_data_list[i].urb)
				usb_kill_urb(card->rx_data_list[i].urb);

	for (i = 0; i < MWIFIEX_RX_DATA_URB; i++) {
		usb_free_urb(card->rx_data_list[i].urb);
		card->rx_data_list[i].urb = NULL;
	}

	for (i = 0; i < MWIFIEX_TX_DATA_PORT; i++) {
		port = &card->port[i];
		for (j = 0; j < MWIFIEX_TX_DATA_URB; j++) {
			usb_kill_urb(port->tx_data_list[j].urb);
			usb_free_urb(port->tx_data_list[j].urb);
			port->tx_data_list[j].urb = NULL;
		}
	}

	usb_free_urb(card->tx_cmd.urb);
	card->tx_cmd.urb = NULL;

	return;
}