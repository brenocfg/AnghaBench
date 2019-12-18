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
struct sk_buff {int /*<<< orphan*/  ip_summed; int /*<<< orphan*/  protocol; int /*<<< orphan*/  data; } ;
struct nps_enet_priv {int dummy; } ;
struct TYPE_2__ {int rx_bytes; int /*<<< orphan*/  rx_packets; int /*<<< orphan*/  rx_dropped; int /*<<< orphan*/  rx_errors; int /*<<< orphan*/  rx_length_errors; int /*<<< orphan*/  rx_crc_errors; } ;
struct net_device {TYPE_1__ stats; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHECKSUM_UNNECESSARY ; 
 int ETH_ZLEN ; 
 int /*<<< orphan*/  NPS_ENET_REG_RX_CTL ; 
 int RX_CTL_CRC_MASK ; 
 int RX_CTL_CRC_SHIFT ; 
 int RX_CTL_CR_MASK ; 
 int RX_CTL_CR_SHIFT ; 
 int RX_CTL_ER_MASK ; 
 int RX_CTL_ER_SHIFT ; 
 int RX_CTL_NR_MASK ; 
 int RX_CTL_NR_SHIFT ; 
 int /*<<< orphan*/  eth_type_trans (struct sk_buff*,struct net_device*) ; 
 struct sk_buff* netdev_alloc_skb_ip_align (struct net_device*,int) ; 
 struct nps_enet_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_receive_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  nps_enet_clean_rx_fifo (struct net_device*,int) ; 
 int /*<<< orphan*/  nps_enet_read_rx_fifo (struct net_device*,int /*<<< orphan*/ ,int) ; 
 int nps_enet_reg_get (struct nps_enet_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nps_enet_reg_set (struct nps_enet_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static u32 nps_enet_rx_handler(struct net_device *ndev)
{
	u32 frame_len, err = 0;
	u32 work_done = 0;
	struct nps_enet_priv *priv = netdev_priv(ndev);
	struct sk_buff *skb;
	u32 rx_ctrl_value = nps_enet_reg_get(priv, NPS_ENET_REG_RX_CTL);
	u32 rx_ctrl_cr = (rx_ctrl_value & RX_CTL_CR_MASK) >> RX_CTL_CR_SHIFT;
	u32 rx_ctrl_er = (rx_ctrl_value & RX_CTL_ER_MASK) >> RX_CTL_ER_SHIFT;
	u32 rx_ctrl_crc = (rx_ctrl_value & RX_CTL_CRC_MASK) >> RX_CTL_CRC_SHIFT;

	frame_len = (rx_ctrl_value & RX_CTL_NR_MASK) >> RX_CTL_NR_SHIFT;

	/* Check if we got RX */
	if (!rx_ctrl_cr)
		return work_done;

	/* If we got here there is a work for us */
	work_done++;

	/* Check Rx error */
	if (rx_ctrl_er) {
		ndev->stats.rx_errors++;
		err = 1;
	}

	/* Check Rx CRC error */
	if (rx_ctrl_crc) {
		ndev->stats.rx_crc_errors++;
		ndev->stats.rx_dropped++;
		err = 1;
	}

	/* Check Frame length Min 64b */
	if (unlikely(frame_len < ETH_ZLEN)) {
		ndev->stats.rx_length_errors++;
		ndev->stats.rx_dropped++;
		err = 1;
	}

	if (err)
		goto rx_irq_clean;

	/* Skb allocation */
	skb = netdev_alloc_skb_ip_align(ndev, frame_len);
	if (unlikely(!skb)) {
		ndev->stats.rx_errors++;
		ndev->stats.rx_dropped++;
		goto rx_irq_clean;
	}

	/* Copy frame from Rx fifo into the skb */
	nps_enet_read_rx_fifo(ndev, skb->data, frame_len);

	skb_put(skb, frame_len);
	skb->protocol = eth_type_trans(skb, ndev);
	skb->ip_summed = CHECKSUM_UNNECESSARY;

	ndev->stats.rx_packets++;
	ndev->stats.rx_bytes += frame_len;
	netif_receive_skb(skb);

	goto rx_irq_frame_done;

rx_irq_clean:
	/* Clean Rx fifo */
	nps_enet_clean_rx_fifo(ndev, frame_len);

rx_irq_frame_done:
	/* Ack Rx ctrl register */
	nps_enet_reg_set(priv, NPS_ENET_REG_RX_CTL, 0);

	return work_done;
}