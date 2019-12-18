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
typedef  int u32 ;
struct uli526x_board_info {int cr6_data; struct rx_desc* rx_ready_ptr; int /*<<< orphan*/  pdev; int /*<<< orphan*/  interval_rx_cnt; scalar_t__ rx_avail_cnt; } ;
struct sk_buff {int /*<<< orphan*/  protocol; } ;
struct rx_desc {struct rx_desc* next_rx_desc; struct sk_buff* rx_skb_ptr; int /*<<< orphan*/  rdes2; int /*<<< orphan*/  rdes0; } ;
struct TYPE_2__ {int rx_bytes; int /*<<< orphan*/  rx_packets; int /*<<< orphan*/  rx_length_errors; int /*<<< orphan*/  rx_crc_errors; int /*<<< orphan*/  rx_fifo_errors; int /*<<< orphan*/  rx_errors; } ;
struct net_device {TYPE_1__ stats; } ;

/* Variables and functions */
 int CR6_PM ; 
 int /*<<< orphan*/  PCI_DMA_FROMDEVICE ; 
 int /*<<< orphan*/  RX_ALLOC_SIZE ; 
 int RX_COPY_SIZE ; 
 int /*<<< orphan*/  ULI526X_DBUG (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  eth_type_trans (struct sk_buff*,struct net_device*) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 struct sk_buff* netdev_alloc_skb (struct net_device*,int) ; 
 int /*<<< orphan*/  netif_rx (struct sk_buff*) ; 
 int /*<<< orphan*/  pci_unmap_single (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_put_data (struct sk_buff*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_tail_pointer (struct sk_buff*) ; 
 int /*<<< orphan*/  uli526x_reuse_skb (struct uli526x_board_info*,struct sk_buff*) ; 

__attribute__((used)) static void uli526x_rx_packet(struct net_device *dev, struct uli526x_board_info * db)
{
	struct rx_desc *rxptr;
	struct sk_buff *skb;
	int rxlen;
	u32 rdes0;

	rxptr = db->rx_ready_ptr;

	while(db->rx_avail_cnt) {
		rdes0 = le32_to_cpu(rxptr->rdes0);
		if (rdes0 & 0x80000000)	/* packet owner check */
		{
			break;
		}

		db->rx_avail_cnt--;
		db->interval_rx_cnt++;

		pci_unmap_single(db->pdev, le32_to_cpu(rxptr->rdes2), RX_ALLOC_SIZE, PCI_DMA_FROMDEVICE);
		if ( (rdes0 & 0x300) != 0x300) {
			/* A packet without First/Last flag */
			/* reuse this SKB */
			ULI526X_DBUG(0, "Reuse SK buffer, rdes0", rdes0);
			uli526x_reuse_skb(db, rxptr->rx_skb_ptr);
		} else {
			/* A packet with First/Last flag */
			rxlen = ( (rdes0 >> 16) & 0x3fff) - 4;

			/* error summary bit check */
			if (rdes0 & 0x8000) {
				/* This is a error packet */
				dev->stats.rx_errors++;
				if (rdes0 & 1)
					dev->stats.rx_fifo_errors++;
				if (rdes0 & 2)
					dev->stats.rx_crc_errors++;
				if (rdes0 & 0x80)
					dev->stats.rx_length_errors++;
			}

			if ( !(rdes0 & 0x8000) ||
				((db->cr6_data & CR6_PM) && (rxlen>6)) ) {
				struct sk_buff *new_skb = NULL;

				skb = rxptr->rx_skb_ptr;

				/* Good packet, send to upper layer */
				/* Shorst packet used new SKB */
				if ((rxlen < RX_COPY_SIZE) &&
				    (((new_skb = netdev_alloc_skb(dev, rxlen + 2)) != NULL))) {
					skb = new_skb;
					/* size less than COPY_SIZE, allocate a rxlen SKB */
					skb_reserve(skb, 2); /* 16byte align */
					skb_put_data(skb,
						     skb_tail_pointer(rxptr->rx_skb_ptr),
						     rxlen);
					uli526x_reuse_skb(db, rxptr->rx_skb_ptr);
				} else
					skb_put(skb, rxlen);

				skb->protocol = eth_type_trans(skb, dev);
				netif_rx(skb);
				dev->stats.rx_packets++;
				dev->stats.rx_bytes += rxlen;

			} else {
				/* Reuse SKB buffer when the packet is error */
				ULI526X_DBUG(0, "Reuse SK buffer, rdes0", rdes0);
				uli526x_reuse_skb(db, rxptr->rx_skb_ptr);
			}
		}

		rxptr = rxptr->next_rx_desc;
	}

	db->rx_ready_ptr = rxptr;
}