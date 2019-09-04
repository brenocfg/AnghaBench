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
typedef  int u8 ;
typedef  int u32 ;
typedef  scalar_t__ u16 ;
struct sky2_status_le {int opcode; unsigned int css; int /*<<< orphan*/  status; int /*<<< orphan*/  length; } ;
struct sky2_port {int dummy; } ;
struct sky2_hw {scalar_t__ st_idx; int flags; struct net_device** dev; int /*<<< orphan*/  st_size; struct sky2_status_le* st_le; } ;
struct sk_buff {int /*<<< orphan*/  protocol; int /*<<< orphan*/  ip_summed; } ;
struct net_device {int features; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHECKSUM_NONE ; 
 int /*<<< orphan*/  CHECKSUM_UNNECESSARY ; 
 int CSS_ISIPV4 ; 
 int CSS_ISIPV6 ; 
 unsigned int CSS_LINK_BIT ; 
 int CSS_TCPUDPCSOK ; 
 int HW_OWNER ; 
 int NETIF_F_RXCSUM ; 
#define  OP_RSS_HASH 133 
#define  OP_RXCHKS 132 
#define  OP_RXCHKSVLAN 131 
#define  OP_RXSTAT 130 
#define  OP_RXVLAN 129 
#define  OP_TXINDEXLE 128 
 int RING_NEXT (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SC_STAT_CLR_IRQ ; 
 int SKY2_HW_NEW_LE ; 
 int /*<<< orphan*/  STAT_CTRL ; 
 int /*<<< orphan*/  eth_type_trans (struct sk_buff*,struct net_device*) ; 
 scalar_t__ le16_to_cpu (int /*<<< orphan*/ ) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  likely (int) ; 
 int /*<<< orphan*/  net_ratelimit () ; 
 struct sky2_port* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  pr_warn (char*,int) ; 
 int /*<<< orphan*/  rmb () ; 
 struct sk_buff* sky2_receive (struct net_device*,scalar_t__,int) ; 
 int /*<<< orphan*/  sky2_rx_checksum (struct sky2_port*,int) ; 
 int /*<<< orphan*/  sky2_rx_done (struct sky2_hw*,int,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  sky2_rx_hash (struct sky2_port*,int) ; 
 int /*<<< orphan*/  sky2_rx_tag (struct sky2_port*,scalar_t__) ; 
 int /*<<< orphan*/  sky2_skb_rx (struct sky2_port*,struct sk_buff*) ; 
 int /*<<< orphan*/  sky2_tx_done (struct net_device*,int) ; 
 int /*<<< orphan*/  sky2_write32 (struct sky2_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sky2_status_intr(struct sky2_hw *hw, int to_do, u16 idx)
{
	int work_done = 0;
	unsigned int total_bytes[2] = { 0 };
	unsigned int total_packets[2] = { 0 };

	if (to_do <= 0)
		return work_done;

	rmb();
	do {
		struct sky2_port *sky2;
		struct sky2_status_le *le  = hw->st_le + hw->st_idx;
		unsigned port;
		struct net_device *dev;
		struct sk_buff *skb;
		u32 status;
		u16 length;
		u8 opcode = le->opcode;

		if (!(opcode & HW_OWNER))
			break;

		hw->st_idx = RING_NEXT(hw->st_idx, hw->st_size);

		port = le->css & CSS_LINK_BIT;
		dev = hw->dev[port];
		sky2 = netdev_priv(dev);
		length = le16_to_cpu(le->length);
		status = le32_to_cpu(le->status);

		le->opcode = 0;
		switch (opcode & ~HW_OWNER) {
		case OP_RXSTAT:
			total_packets[port]++;
			total_bytes[port] += length;

			skb = sky2_receive(dev, length, status);
			if (!skb)
				break;

			/* This chip reports checksum status differently */
			if (hw->flags & SKY2_HW_NEW_LE) {
				if ((dev->features & NETIF_F_RXCSUM) &&
				    (le->css & (CSS_ISIPV4 | CSS_ISIPV6)) &&
				    (le->css & CSS_TCPUDPCSOK))
					skb->ip_summed = CHECKSUM_UNNECESSARY;
				else
					skb->ip_summed = CHECKSUM_NONE;
			}

			skb->protocol = eth_type_trans(skb, dev);
			sky2_skb_rx(sky2, skb);

			/* Stop after net poll weight */
			if (++work_done >= to_do)
				goto exit_loop;
			break;

		case OP_RXVLAN:
			sky2_rx_tag(sky2, length);
			break;

		case OP_RXCHKSVLAN:
			sky2_rx_tag(sky2, length);
			/* fall through */
		case OP_RXCHKS:
			if (likely(dev->features & NETIF_F_RXCSUM))
				sky2_rx_checksum(sky2, status);
			break;

		case OP_RSS_HASH:
			sky2_rx_hash(sky2, status);
			break;

		case OP_TXINDEXLE:
			/* TX index reports status for both ports */
			sky2_tx_done(hw->dev[0], status & 0xfff);
			if (hw->dev[1])
				sky2_tx_done(hw->dev[1],
				     ((status >> 24) & 0xff)
					     | (u16)(length & 0xf) << 8);
			break;

		default:
			if (net_ratelimit())
				pr_warn("unknown status opcode 0x%x\n", opcode);
		}
	} while (hw->st_idx != idx);

	/* Fully processed status ring so clear irq */
	sky2_write32(hw, STAT_CTRL, SC_STAT_CLR_IRQ);

exit_loop:
	sky2_rx_done(hw, 0, total_packets[0], total_bytes[0]);
	sky2_rx_done(hw, 1, total_packets[1], total_bytes[1]);

	return work_done;
}