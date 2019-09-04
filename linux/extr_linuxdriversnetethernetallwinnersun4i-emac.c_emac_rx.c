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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct sk_buff {void* protocol; } ;
struct TYPE_2__ {int rx_bytes; int /*<<< orphan*/  rx_packets; int /*<<< orphan*/  rx_length_errors; int /*<<< orphan*/  rx_crc_errors; } ;
struct net_device {TYPE_1__ stats; } ;
struct emac_board_info {int emacrx_completed_flag; scalar_t__ membase; int /*<<< orphan*/  dev; struct sk_buff* skb_last; } ;

/* Variables and functions */
 scalar_t__ EMAC_CTL_REG ; 
 unsigned int EMAC_CTL_RX_EN ; 
 scalar_t__ EMAC_INT_CTL_REG ; 
 unsigned int EMAC_RX_CTL_DMA_EN ; 
 scalar_t__ EMAC_RX_CTL_REG ; 
 scalar_t__ EMAC_RX_FBC_REG ; 
 int EMAC_RX_IO_DATA_LEN (int) ; 
 scalar_t__ EMAC_RX_IO_DATA_REG ; 
 int EMAC_RX_IO_DATA_STATUS (int) ; 
 int EMAC_RX_IO_DATA_STATUS_CRC_ERR ; 
 int EMAC_RX_IO_DATA_STATUS_LEN_ERR ; 
 int EMAC_RX_IO_DATA_STATUS_OK ; 
 unsigned int EMAC_UNDOCUMENTED_MAGIC ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  emac_inblk_32bit (scalar_t__,int /*<<< orphan*/ *,int) ; 
 void* eth_type_trans (struct sk_buff*,struct net_device*) ; 
 struct sk_buff* netdev_alloc_skb (struct net_device*,int) ; 
 struct emac_board_info* netdev_priv (struct net_device*) ; 
 scalar_t__ netif_msg_rx_err (struct emac_board_info*) ; 
 scalar_t__ netif_msg_rx_status (struct emac_board_info*) ; 
 int /*<<< orphan*/  netif_rx (struct sk_buff*) ; 
 void* readl (scalar_t__) ; 
 int /*<<< orphan*/ * skb_put (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,int) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  writel (unsigned int,scalar_t__) ; 

__attribute__((used)) static void emac_rx(struct net_device *dev)
{
	struct emac_board_info *db = netdev_priv(dev);
	struct sk_buff *skb;
	u8 *rdptr;
	bool good_packet;
	static int rxlen_last;
	unsigned int reg_val;
	u32 rxhdr, rxstatus, rxcount, rxlen;

	/* Check packet ready or not */
	while (1) {
		/* race warning: the first packet might arrive with
		 * the interrupts disabled, but the second will fix
		 * it
		 */
		rxcount = readl(db->membase + EMAC_RX_FBC_REG);

		if (netif_msg_rx_status(db))
			dev_dbg(db->dev, "RXCount: %x\n", rxcount);

		if ((db->skb_last != NULL) && (rxlen_last > 0)) {
			dev->stats.rx_bytes += rxlen_last;

			/* Pass to upper layer */
			db->skb_last->protocol = eth_type_trans(db->skb_last,
								dev);
			netif_rx(db->skb_last);
			dev->stats.rx_packets++;
			db->skb_last = NULL;
			rxlen_last = 0;

			reg_val = readl(db->membase + EMAC_RX_CTL_REG);
			reg_val &= ~EMAC_RX_CTL_DMA_EN;
			writel(reg_val, db->membase + EMAC_RX_CTL_REG);
		}

		if (!rxcount) {
			db->emacrx_completed_flag = 1;
			reg_val = readl(db->membase + EMAC_INT_CTL_REG);
			reg_val |= (0xf << 0) | (0x01 << 8);
			writel(reg_val, db->membase + EMAC_INT_CTL_REG);

			/* had one stuck? */
			rxcount = readl(db->membase + EMAC_RX_FBC_REG);
			if (!rxcount)
				return;
		}

		reg_val = readl(db->membase + EMAC_RX_IO_DATA_REG);
		if (netif_msg_rx_status(db))
			dev_dbg(db->dev, "receive header: %x\n", reg_val);
		if (reg_val != EMAC_UNDOCUMENTED_MAGIC) {
			/* disable RX */
			reg_val = readl(db->membase + EMAC_CTL_REG);
			writel(reg_val & ~EMAC_CTL_RX_EN,
			       db->membase + EMAC_CTL_REG);

			/* Flush RX FIFO */
			reg_val = readl(db->membase + EMAC_RX_CTL_REG);
			writel(reg_val | (1 << 3),
			       db->membase + EMAC_RX_CTL_REG);

			do {
				reg_val = readl(db->membase + EMAC_RX_CTL_REG);
			} while (reg_val & (1 << 3));

			/* enable RX */
			reg_val = readl(db->membase + EMAC_CTL_REG);
			writel(reg_val | EMAC_CTL_RX_EN,
			       db->membase + EMAC_CTL_REG);
			reg_val = readl(db->membase + EMAC_INT_CTL_REG);
			reg_val |= (0xf << 0) | (0x01 << 8);
			writel(reg_val, db->membase + EMAC_INT_CTL_REG);

			db->emacrx_completed_flag = 1;

			return;
		}

		/* A packet ready now  & Get status/length */
		good_packet = true;

		rxhdr = readl(db->membase + EMAC_RX_IO_DATA_REG);

		if (netif_msg_rx_status(db))
			dev_dbg(db->dev, "rxhdr: %x\n", *((int *)(&rxhdr)));

		rxlen = EMAC_RX_IO_DATA_LEN(rxhdr);
		rxstatus = EMAC_RX_IO_DATA_STATUS(rxhdr);

		if (netif_msg_rx_status(db))
			dev_dbg(db->dev, "RX: status %02x, length %04x\n",
				rxstatus, rxlen);

		/* Packet Status check */
		if (rxlen < 0x40) {
			good_packet = false;
			if (netif_msg_rx_err(db))
				dev_dbg(db->dev, "RX: Bad Packet (runt)\n");
		}

		if (unlikely(!(rxstatus & EMAC_RX_IO_DATA_STATUS_OK))) {
			good_packet = false;

			if (rxstatus & EMAC_RX_IO_DATA_STATUS_CRC_ERR) {
				if (netif_msg_rx_err(db))
					dev_dbg(db->dev, "crc error\n");
				dev->stats.rx_crc_errors++;
			}

			if (rxstatus & EMAC_RX_IO_DATA_STATUS_LEN_ERR) {
				if (netif_msg_rx_err(db))
					dev_dbg(db->dev, "length error\n");
				dev->stats.rx_length_errors++;
			}
		}

		/* Move data from EMAC */
		if (good_packet) {
			skb = netdev_alloc_skb(dev, rxlen + 4);
			if (!skb)
				continue;
			skb_reserve(skb, 2);
			rdptr = skb_put(skb, rxlen - 4);

			/* Read received packet from RX SRAM */
			if (netif_msg_rx_status(db))
				dev_dbg(db->dev, "RxLen %x\n", rxlen);

			emac_inblk_32bit(db->membase + EMAC_RX_IO_DATA_REG,
					rdptr, rxlen);
			dev->stats.rx_bytes += rxlen;

			/* Pass to upper layer */
			skb->protocol = eth_type_trans(skb, dev);
			netif_rx(skb);
			dev->stats.rx_packets++;
		}
	}
}