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
typedef  size_t u8 ;
struct skb_shared_hwtstamps {int /*<<< orphan*/  hwtstamp; } ;
struct sk_buff {int dummy; } ;
struct net_device_stats {int /*<<< orphan*/  rx_packets; int /*<<< orphan*/  rx_bytes; int /*<<< orphan*/  rx_dropped; } ;
struct kvaser_pciefd_rx_packet {int* header; int timestamp; } ;
struct kvaser_pciefd {size_t nr_channels; int /*<<< orphan*/  freq_to_ticks_div; TYPE_1__** can; } ;
struct canfd_frame {int can_id; scalar_t__ len; int /*<<< orphan*/  data; int /*<<< orphan*/  flags; } ;
struct can_priv {TYPE_2__* dev; } ;
struct can_frame {int dummy; } ;
typedef  int /*<<< orphan*/  __le32 ;
struct TYPE_5__ {struct net_device_stats stats; } ;
struct TYPE_4__ {struct can_priv can; } ;

/* Variables and functions */
 int /*<<< orphan*/  CANFD_BRS ; 
 int /*<<< orphan*/  CANFD_ESI ; 
 int CAN_EFF_FLAG ; 
 int CAN_EFF_MASK ; 
 int CAN_RTR_FLAG ; 
 int EIO ; 
 int ENOMEM ; 
 int KVASER_PCIEFD_PACKET_CHID_SHIFT ; 
 int KVASER_PCIEFD_RPACKET_BRS ; 
 int KVASER_PCIEFD_RPACKET_DLC_SHIFT ; 
 int KVASER_PCIEFD_RPACKET_ESI ; 
 int KVASER_PCIEFD_RPACKET_FDF ; 
 int KVASER_PCIEFD_RPACKET_IDE ; 
 int KVASER_PCIEFD_RPACKET_RTR ; 
 struct sk_buff* alloc_can_skb (TYPE_2__*,struct can_frame**) ; 
 struct sk_buff* alloc_canfd_skb (TYPE_2__*,struct canfd_frame**) ; 
 scalar_t__ can_dlc2len (int) ; 
 int /*<<< orphan*/  div_u64 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ; 
 int netif_rx (struct sk_buff*) ; 
 int /*<<< orphan*/  ns_to_ktime (int /*<<< orphan*/ ) ; 
 struct skb_shared_hwtstamps* skb_hwtstamps (struct sk_buff*) ; 

__attribute__((used)) static int kvaser_pciefd_handle_data_packet(struct kvaser_pciefd *pcie,
					    struct kvaser_pciefd_rx_packet *p,
					    __le32 *data)
{
	struct sk_buff *skb;
	struct canfd_frame *cf;
	struct can_priv *priv;
	struct net_device_stats *stats;
	struct skb_shared_hwtstamps *shhwtstamps;
	u8 ch_id = (p->header[1] >> KVASER_PCIEFD_PACKET_CHID_SHIFT) & 0x7;

	if (ch_id >= pcie->nr_channels)
		return -EIO;

	priv = &pcie->can[ch_id]->can;
	stats = &priv->dev->stats;

	if (p->header[1] & KVASER_PCIEFD_RPACKET_FDF) {
		skb = alloc_canfd_skb(priv->dev, &cf);
		if (!skb) {
			stats->rx_dropped++;
			return -ENOMEM;
		}

		if (p->header[1] & KVASER_PCIEFD_RPACKET_BRS)
			cf->flags |= CANFD_BRS;

		if (p->header[1] & KVASER_PCIEFD_RPACKET_ESI)
			cf->flags |= CANFD_ESI;
	} else {
		skb = alloc_can_skb(priv->dev, (struct can_frame **)&cf);
		if (!skb) {
			stats->rx_dropped++;
			return -ENOMEM;
		}
	}

	cf->can_id = p->header[0] & CAN_EFF_MASK;
	if (p->header[0] & KVASER_PCIEFD_RPACKET_IDE)
		cf->can_id |= CAN_EFF_FLAG;

	cf->len = can_dlc2len(p->header[1] >> KVASER_PCIEFD_RPACKET_DLC_SHIFT);

	if (p->header[0] & KVASER_PCIEFD_RPACKET_RTR)
		cf->can_id |= CAN_RTR_FLAG;
	else
		memcpy(cf->data, data, cf->len);

	shhwtstamps = skb_hwtstamps(skb);

	shhwtstamps->hwtstamp =
		ns_to_ktime(div_u64(p->timestamp * 1000,
				    pcie->freq_to_ticks_div));

	stats->rx_bytes += cf->len;
	stats->rx_packets++;

	return netif_rx(skb);
}