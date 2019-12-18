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
struct usb_card_rec {int /*<<< orphan*/ * adapter; } ;
struct mwifiex_adapter {scalar_t__ card; } ;

/* Variables and functions */
 int /*<<< orphan*/  mwifiex_usb_cleanup_tx_aggr (struct mwifiex_adapter*) ; 
 int /*<<< orphan*/  mwifiex_usb_free (struct usb_card_rec*) ; 

__attribute__((used)) static void mwifiex_unregister_dev(struct mwifiex_adapter *adapter)
{
	struct usb_card_rec *card = (struct usb_card_rec *)adapter->card;

	mwifiex_usb_free(card);

	mwifiex_usb_cleanup_tx_aggr(adapter);

	card->adapter = NULL;
}