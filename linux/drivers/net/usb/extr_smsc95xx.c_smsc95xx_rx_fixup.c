#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
typedef  int u16 ;
struct usbnet {TYPE_2__* net; } ;
struct sk_buff {scalar_t__ len; unsigned char* data; int truesize; } ;
struct TYPE_4__ {int /*<<< orphan*/  rx_length_errors; int /*<<< orphan*/  rx_frame_errors; int /*<<< orphan*/  rx_crc_errors; int /*<<< orphan*/  rx_dropped; int /*<<< orphan*/  rx_errors; } ;
struct TYPE_5__ {scalar_t__ hard_header_len; int features; TYPE_1__ stats; } ;

/* Variables and functions */
 int ETH_FRAME_LEN ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int NETIF_F_RXCSUM ; 
 int NET_IP_ALIGN ; 
 int RX_STS_CRC_ ; 
 int RX_STS_ES_ ; 
 int RX_STS_FL_ ; 
 int RX_STS_FT_ ; 
 int RX_STS_LE_ ; 
 int RX_STS_RF_ ; 
 int RX_STS_TL_ ; 
 int get_unaligned_le32 (unsigned char*) ; 
 int /*<<< orphan*/  netdev_warn (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  netif_dbg (struct usbnet*,int /*<<< orphan*/ ,TYPE_2__*,char*,int) ; 
 int /*<<< orphan*/  rx_err ; 
 struct sk_buff* skb_clone (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_set_tail_pointer (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_trim (struct sk_buff*,int) ; 
 int /*<<< orphan*/  smsc95xx_rx_csum_offload (struct sk_buff*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  usbnet_skb_return (struct usbnet*,struct sk_buff*) ; 

__attribute__((used)) static int smsc95xx_rx_fixup(struct usbnet *dev, struct sk_buff *skb)
{
	/* This check is no longer done by usbnet */
	if (skb->len < dev->net->hard_header_len)
		return 0;

	while (skb->len > 0) {
		u32 header, align_count;
		struct sk_buff *ax_skb;
		unsigned char *packet;
		u16 size;

		header = get_unaligned_le32(skb->data);
		skb_pull(skb, 4 + NET_IP_ALIGN);
		packet = skb->data;

		/* get the packet length */
		size = (u16)((header & RX_STS_FL_) >> 16);
		align_count = (4 - ((size + NET_IP_ALIGN) % 4)) % 4;

		if (unlikely(header & RX_STS_ES_)) {
			netif_dbg(dev, rx_err, dev->net,
				  "Error header=0x%08x\n", header);
			dev->net->stats.rx_errors++;
			dev->net->stats.rx_dropped++;

			if (header & RX_STS_CRC_) {
				dev->net->stats.rx_crc_errors++;
			} else {
				if (header & (RX_STS_TL_ | RX_STS_RF_))
					dev->net->stats.rx_frame_errors++;

				if ((header & RX_STS_LE_) &&
					(!(header & RX_STS_FT_)))
					dev->net->stats.rx_length_errors++;
			}
		} else {
			/* ETH_FRAME_LEN + 4(CRC) + 2(COE) + 4(Vlan) */
			if (unlikely(size > (ETH_FRAME_LEN + 12))) {
				netif_dbg(dev, rx_err, dev->net,
					  "size err header=0x%08x\n", header);
				return 0;
			}

			/* last frame in this batch */
			if (skb->len == size) {
				if (dev->net->features & NETIF_F_RXCSUM)
					smsc95xx_rx_csum_offload(skb);
				skb_trim(skb, skb->len - 4); /* remove fcs */
				skb->truesize = size + sizeof(struct sk_buff);

				return 1;
			}

			ax_skb = skb_clone(skb, GFP_ATOMIC);
			if (unlikely(!ax_skb)) {
				netdev_warn(dev->net, "Error allocating skb\n");
				return 0;
			}

			ax_skb->len = size;
			ax_skb->data = packet;
			skb_set_tail_pointer(ax_skb, size);

			if (dev->net->features & NETIF_F_RXCSUM)
				smsc95xx_rx_csum_offload(ax_skb);
			skb_trim(ax_skb, ax_skb->len - 4); /* remove fcs */
			ax_skb->truesize = size + sizeof(struct sk_buff);

			usbnet_skb_return(dev, ax_skb);
		}

		skb_pull(skb, size);

		/* padding bytes before the next frame starts */
		if (skb->len)
			skb_pull(skb, align_count);
	}

	return 1;
}