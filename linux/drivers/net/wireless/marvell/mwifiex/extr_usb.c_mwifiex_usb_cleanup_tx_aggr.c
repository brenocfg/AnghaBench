#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int is_hold_timer_set; scalar_t__ hold_tmo_msecs; int /*<<< orphan*/  hold_timer; } ;
struct TYPE_6__ {TYPE_2__ timer_cnxt; int /*<<< orphan*/  aggr_list; } ;
struct usb_tx_data_port {TYPE_3__ tx_aggr; } ;
struct usb_card_rec {struct usb_tx_data_port* port; } ;
struct sk_buff {int dummy; } ;
struct TYPE_4__ {scalar_t__ enable; } ;
struct mwifiex_adapter {TYPE_1__ bus_aggr; scalar_t__ card; } ;

/* Variables and functions */
 int MWIFIEX_TX_DATA_PORT ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mwifiex_write_data_complete (struct mwifiex_adapter*,struct sk_buff*,int /*<<< orphan*/ ,int) ; 
 struct sk_buff* skb_dequeue (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mwifiex_usb_cleanup_tx_aggr(struct mwifiex_adapter *adapter)
{
	struct usb_card_rec *card = (struct usb_card_rec *)adapter->card;
	struct usb_tx_data_port *port;
	struct sk_buff *skb_tmp;
	int idx;

	for (idx = 0; idx < MWIFIEX_TX_DATA_PORT; idx++) {
		port = &card->port[idx];
		if (adapter->bus_aggr.enable)
			while ((skb_tmp =
				skb_dequeue(&port->tx_aggr.aggr_list)))
				mwifiex_write_data_complete(adapter, skb_tmp,
							    0, -1);
		del_timer_sync(&port->tx_aggr.timer_cnxt.hold_timer);
		port->tx_aggr.timer_cnxt.is_hold_timer_set = false;
		port->tx_aggr.timer_cnxt.hold_tmo_msecs = 0;
	}
}