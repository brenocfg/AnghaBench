#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u8 ;
struct net_device_stats {int tx_bytes; int /*<<< orphan*/  tx_packets; } ;
struct kvaser_pciefd_rx_packet {int* header; } ;
struct TYPE_5__ {TYPE_2__* dev; } ;
struct kvaser_pciefd_can {TYPE_1__ can; scalar_t__ reg_base; } ;
struct kvaser_pciefd {size_t nr_channels; struct kvaser_pciefd_can** can; } ;
struct TYPE_6__ {struct net_device_stats stats; } ;

/* Variables and functions */
 int EIO ; 
 int KVASER_PCIEFD_APACKET_FLU ; 
 int /*<<< orphan*/  KVASER_PCIEFD_KCAN_CTRL_EFLUSH ; 
 scalar_t__ KVASER_PCIEFD_KCAN_CTRL_REG ; 
 scalar_t__ KVASER_PCIEFD_KCAN_TX_NPACKETS_REG ; 
 int KVASER_PCIEFD_PACKET_CHID_SHIFT ; 
 int KVASER_PCIEFD_PACKET_SEQ_MSK ; 
 int can_get_echo_skb (TYPE_2__*,int) ; 
 int ioread32 (scalar_t__) ; 
 int /*<<< orphan*/  iowrite32 (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ netif_queue_stopped (TYPE_2__*) ; 
 int /*<<< orphan*/  netif_wake_queue (TYPE_2__*) ; 

__attribute__((used)) static int kvaser_pciefd_handle_eack_packet(struct kvaser_pciefd *pcie,
					    struct kvaser_pciefd_rx_packet *p)
{
	struct kvaser_pciefd_can *can;
	u8 ch_id = (p->header[1] >> KVASER_PCIEFD_PACKET_CHID_SHIFT) & 0x7;

	if (ch_id >= pcie->nr_channels)
		return -EIO;

	can = pcie->can[ch_id];

	/* If this is the last flushed packet, send end of flush */
	if (p->header[0] & KVASER_PCIEFD_APACKET_FLU) {
		u8 count = ioread32(can->reg_base +
				    KVASER_PCIEFD_KCAN_TX_NPACKETS_REG) & 0xff;

		if (count == 0)
			iowrite32(KVASER_PCIEFD_KCAN_CTRL_EFLUSH,
				  can->reg_base + KVASER_PCIEFD_KCAN_CTRL_REG);
	} else {
		int echo_idx = p->header[0] & KVASER_PCIEFD_PACKET_SEQ_MSK;
		int dlc = can_get_echo_skb(can->can.dev, echo_idx);
		struct net_device_stats *stats = &can->can.dev->stats;

		stats->tx_bytes += dlc;
		stats->tx_packets++;

		if (netif_queue_stopped(can->can.dev))
			netif_wake_queue(can->can.dev);
	}

	return 0;
}