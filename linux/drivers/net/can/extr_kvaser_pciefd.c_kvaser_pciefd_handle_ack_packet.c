#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u8 ;
struct net_device_stats {int tx_bytes; int /*<<< orphan*/  tx_packets; } ;
struct kvaser_pciefd_rx_packet {int* header; } ;
struct TYPE_6__ {TYPE_2__* dev; } ;
struct kvaser_pciefd_can {TYPE_1__ can; scalar_t__ reg_base; } ;
struct kvaser_pciefd {size_t nr_channels; struct kvaser_pciefd_can** can; } ;
struct TYPE_7__ {struct net_device_stats stats; } ;

/* Variables and functions */
 int EIO ; 
 int KVASER_PCIEFD_APACKET_CT ; 
 int KVASER_PCIEFD_APACKET_FLU ; 
 int KVASER_PCIEFD_APACKET_NACK ; 
 size_t KVASER_PCIEFD_CAN_TX_MAX_COUNT ; 
 scalar_t__ KVASER_PCIEFD_KCAN_TX_NPACKETS_REG ; 
 int KVASER_PCIEFD_PACKET_CHID_SHIFT ; 
 int KVASER_PCIEFD_PACKET_SEQ_MSK ; 
 int can_get_echo_skb (TYPE_2__*,int) ; 
 int ioread32 (scalar_t__) ; 
 int /*<<< orphan*/  kvaser_pciefd_handle_nack_packet (struct kvaser_pciefd_can*,struct kvaser_pciefd_rx_packet*) ; 
 int /*<<< orphan*/  netdev_dbg (TYPE_2__*,char*) ; 
 scalar_t__ netif_queue_stopped (TYPE_2__*) ; 
 int /*<<< orphan*/  netif_wake_queue (TYPE_2__*) ; 

__attribute__((used)) static int kvaser_pciefd_handle_ack_packet(struct kvaser_pciefd *pcie,
					   struct kvaser_pciefd_rx_packet *p)
{
	struct kvaser_pciefd_can *can;
	bool one_shot_fail = false;
	u8 ch_id = (p->header[1] >> KVASER_PCIEFD_PACKET_CHID_SHIFT) & 0x7;

	if (ch_id >= pcie->nr_channels)
		return -EIO;

	can = pcie->can[ch_id];
	/* Ignore control packet ACK */
	if (p->header[0] & KVASER_PCIEFD_APACKET_CT)
		return 0;

	if (p->header[0] & KVASER_PCIEFD_APACKET_NACK) {
		kvaser_pciefd_handle_nack_packet(can, p);
		one_shot_fail = true;
	}

	if (p->header[0] & KVASER_PCIEFD_APACKET_FLU) {
		netdev_dbg(can->can.dev, "Packet was flushed\n");
	} else {
		int echo_idx = p->header[0] & KVASER_PCIEFD_PACKET_SEQ_MSK;
		int dlc = can_get_echo_skb(can->can.dev, echo_idx);
		u8 count = ioread32(can->reg_base +
				    KVASER_PCIEFD_KCAN_TX_NPACKETS_REG) & 0xff;

		if (count < KVASER_PCIEFD_CAN_TX_MAX_COUNT &&
		    netif_queue_stopped(can->can.dev))
			netif_wake_queue(can->can.dev);

		if (!one_shot_fail) {
			struct net_device_stats *stats = &can->can.dev->stats;

			stats->tx_bytes += dlc;
			stats->tx_packets++;
		}
	}

	return 0;
}