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
typedef  size_t u32 ;
struct sk_buff {int /*<<< orphan*/  protocol; } ;
struct rx_status_t {int statusinfo; } ;
struct netdata_local {int /*<<< orphan*/  net_base; scalar_t__ rx_buff_v; struct rx_status_t* rx_stat_v; } ;
struct TYPE_2__ {size_t rx_bytes; int /*<<< orphan*/  rx_packets; int /*<<< orphan*/  rx_dropped; int /*<<< orphan*/  rx_errors; int /*<<< orphan*/  rx_length_errors; int /*<<< orphan*/  rx_crc_errors; int /*<<< orphan*/  rx_fifo_errors; } ;
struct net_device {TYPE_1__ stats; } ;

/* Variables and functions */
 size_t ENET_MAXF_SIZE ; 
 size_t ENET_RX_DESC ; 
 int /*<<< orphan*/  LPC_ENET_RXCONSUMEINDEX (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LPC_ENET_RXPRODUCEINDEX (int /*<<< orphan*/ ) ; 
 int RXSTATUS_CRC ; 
 size_t RXSTATUS_ERROR ; 
 int RXSTATUS_LENGTH ; 
 int RXSTATUS_OVERRUN ; 
 size_t RXSTATUS_RANGE ; 
 int RXSTATUS_SIZE ; 
 size_t RXSTATUS_STATUS_ERROR ; 
 struct sk_buff* dev_alloc_skb (size_t) ; 
 int /*<<< orphan*/  eth_type_trans (struct sk_buff*,struct net_device*) ; 
 struct netdata_local* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_receive_skb (struct sk_buff*) ; 
 size_t readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_put_data (struct sk_buff*,scalar_t__,size_t) ; 
 int /*<<< orphan*/  writel (size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int __lpc_handle_recv(struct net_device *ndev, int budget)
{
	struct netdata_local *pldat = netdev_priv(ndev);
	struct sk_buff *skb;
	u32 rxconsidx, len, ethst;
	struct rx_status_t *prxstat;
	int rx_done = 0;

	/* Get the current RX buffer indexes */
	rxconsidx = readl(LPC_ENET_RXCONSUMEINDEX(pldat->net_base));
	while (rx_done < budget && rxconsidx !=
			readl(LPC_ENET_RXPRODUCEINDEX(pldat->net_base))) {
		/* Get pointer to receive status */
		prxstat = &pldat->rx_stat_v[rxconsidx];
		len = (prxstat->statusinfo & RXSTATUS_SIZE) + 1;

		/* Status error? */
		ethst = prxstat->statusinfo;
		if ((ethst & (RXSTATUS_ERROR | RXSTATUS_STATUS_ERROR)) ==
		    (RXSTATUS_ERROR | RXSTATUS_RANGE))
			ethst &= ~RXSTATUS_ERROR;

		if (ethst & RXSTATUS_ERROR) {
			int si = prxstat->statusinfo;
			/* Check statuses */
			if (si & RXSTATUS_OVERRUN) {
				/* Overrun error */
				ndev->stats.rx_fifo_errors++;
			} else if (si & RXSTATUS_CRC) {
				/* CRC error */
				ndev->stats.rx_crc_errors++;
			} else if (si & RXSTATUS_LENGTH) {
				/* Length error */
				ndev->stats.rx_length_errors++;
			} else if (si & RXSTATUS_ERROR) {
				/* Other error */
				ndev->stats.rx_length_errors++;
			}
			ndev->stats.rx_errors++;
		} else {
			/* Packet is good */
			skb = dev_alloc_skb(len);
			if (!skb) {
				ndev->stats.rx_dropped++;
			} else {
				/* Copy packet from buffer */
				skb_put_data(skb,
					     pldat->rx_buff_v + rxconsidx * ENET_MAXF_SIZE,
					     len);

				/* Pass to upper layer */
				skb->protocol = eth_type_trans(skb, ndev);
				netif_receive_skb(skb);
				ndev->stats.rx_packets++;
				ndev->stats.rx_bytes += len;
			}
		}

		/* Increment consume index */
		rxconsidx = rxconsidx + 1;
		if (rxconsidx >= ENET_RX_DESC)
			rxconsidx = 0;
		writel(rxconsidx,
		       LPC_ENET_RXCONSUMEINDEX(pldat->net_base));
		rx_done++;
	}

	return rx_done;
}