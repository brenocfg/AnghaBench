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
struct net_device {int dummy; } ;
struct fst_port_info {scalar_t__ mode; struct fst_card_info* card; } ;
struct fst_card_info {int /*<<< orphan*/  dmarx_in_progress; int /*<<< orphan*/  dmatx_in_progress; scalar_t__ pci_conf; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_OPEN ; 
 scalar_t__ DMACSR0 ; 
 scalar_t__ DMACSR1 ; 
 scalar_t__ FST_RAW ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,unsigned char,int /*<<< orphan*/ ,unsigned char) ; 
 struct fst_port_info* dev_to_port (struct net_device*) ; 
 int /*<<< orphan*/  fst_closeport (struct fst_port_info*) ; 
 int /*<<< orphan*/  hdlc_close (struct net_device*) ; 
 unsigned char inb (scalar_t__) ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 

__attribute__((used)) static int
fst_close(struct net_device *dev)
{
	struct fst_port_info *port;
	struct fst_card_info *card;
	unsigned char tx_dma_done;
	unsigned char rx_dma_done;

	port = dev_to_port(dev);
	card = port->card;

	tx_dma_done = inb(card->pci_conf + DMACSR1);
	rx_dma_done = inb(card->pci_conf + DMACSR0);
	dbg(DBG_OPEN,
	    "Port Close: tx_dma_in_progress = %d (%x) rx_dma_in_progress = %d (%x)\n",
	    card->dmatx_in_progress, tx_dma_done, card->dmarx_in_progress,
	    rx_dma_done);

	netif_stop_queue(dev);
	fst_closeport(dev_to_port(dev));
	if (port->mode != FST_RAW) {
		hdlc_close(dev);
	}
	module_put(THIS_MODULE);
	return 0;
}