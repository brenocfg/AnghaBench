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
typedef  int u8 ;
struct usb_card_rec {TYPE_1__* port; } ;
struct mwifiex_adapter {struct usb_card_rec* card; } ;
struct TYPE_2__ {int /*<<< orphan*/  block_status; } ;

/* Variables and functions */
 int MWIFIEX_TX_DATA_PORT ; 

__attribute__((used)) static inline u8 mwifiex_usb_data_sent(struct mwifiex_adapter *adapter)
{
	struct usb_card_rec *card = adapter->card;
	int i;

	for (i = 0; i < MWIFIEX_TX_DATA_PORT; i++)
		if (!card->port[i].block_status)
			return false;

	return true;
}