#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int /*<<< orphan*/  protocol; } ;
struct TYPE_3__ {int rx_bytes; int /*<<< orphan*/  rx_dropped; int /*<<< orphan*/  rx_packets; } ;
struct net_device {TYPE_1__ stats; int /*<<< orphan*/  name; } ;
struct fst_port_info {int index; scalar_t__ mode; } ;
struct fst_card_info {int /*<<< orphan*/  rx_dma_handle_host; } ;
struct TYPE_4__ {int /*<<< orphan*/  bits; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_RX ; 
 int /*<<< orphan*/  DBG_TX ; 
 int /*<<< orphan*/  DMA_OWN ; 
 scalar_t__ FST_RAW ; 
 int /*<<< orphan*/  FST_WRB (struct fst_card_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int NET_RX_DROP ; 
 int /*<<< orphan*/  dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  farsync_type_trans (struct sk_buff*,struct net_device*) ; 
 int /*<<< orphan*/  fst_process_rx_status (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hdlc_type_trans (struct sk_buff*,struct net_device*) ; 
 int netif_rx (struct sk_buff*) ; 
 struct net_device* port_to_dev (struct fst_port_info*) ; 
 TYPE_2__** rxDescrRing ; 
 int /*<<< orphan*/  skb_put_data (struct sk_buff*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
fst_rx_dma_complete(struct fst_card_info *card, struct fst_port_info *port,
		    int len, struct sk_buff *skb, int rxp)
{
	struct net_device *dev = port_to_dev(port);
	int pi;
	int rx_status;

	dbg(DBG_TX, "fst_rx_dma_complete\n");
	pi = port->index;
	skb_put_data(skb, card->rx_dma_handle_host, len);

	/* Reset buffer descriptor */
	FST_WRB(card, rxDescrRing[pi][rxp].bits, DMA_OWN);

	/* Update stats */
	dev->stats.rx_packets++;
	dev->stats.rx_bytes += len;

	/* Push upstream */
	dbg(DBG_RX, "Pushing the frame up the stack\n");
	if (port->mode == FST_RAW)
		skb->protocol = farsync_type_trans(skb, dev);
	else
		skb->protocol = hdlc_type_trans(skb, dev);
	rx_status = netif_rx(skb);
	fst_process_rx_status(rx_status, port_to_dev(port)->name);
	if (rx_status == NET_RX_DROP)
		dev->stats.rx_dropped++;
}