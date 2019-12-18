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
typedef  scalar_t__ u8 ;
struct TYPE_2__ {int /*<<< orphan*/  skb; } ;
struct usb_card_rec {scalar_t__ rx_cmd_ep; TYPE_1__ rx_cmd; int /*<<< orphan*/  rx_cmd_urb_pending; } ;
struct mwifiex_adapter {scalar_t__ card; } ;

/* Variables and functions */
 int /*<<< orphan*/  INTF_HEADER_LEN ; 
 int /*<<< orphan*/  MWIFIEX_RX_CMD_BUF_SIZE ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mwifiex_usb_submit_rx_urb (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_push (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mwifiex_submit_rx_urb(struct mwifiex_adapter *adapter, u8 ep)
{
	struct usb_card_rec *card = (struct usb_card_rec *)adapter->card;

	skb_push(card->rx_cmd.skb, INTF_HEADER_LEN);
	if ((ep == card->rx_cmd_ep) &&
	    (!atomic_read(&card->rx_cmd_urb_pending)))
		mwifiex_usb_submit_rx_urb(&card->rx_cmd,
					  MWIFIEX_RX_CMD_BUF_SIZE);

	return;
}