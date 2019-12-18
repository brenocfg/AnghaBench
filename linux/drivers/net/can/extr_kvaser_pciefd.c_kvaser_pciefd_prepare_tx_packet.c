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
struct sk_buff {scalar_t__ data; } ;
struct kvaser_pciefd_tx_packet {int* header; int /*<<< orphan*/  data; } ;
struct TYPE_2__ {int ctrlmode; } ;
struct kvaser_pciefd_can {int echo_idx; TYPE_1__ can; } ;
struct canfd_frame {int can_id; int len; int flags; int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int CANFD_BRS ; 
 int CANFD_ESI ; 
 int CAN_CTRLMODE_ONE_SHOT ; 
 int CAN_EFF_FLAG ; 
 int CAN_EFF_MASK ; 
 int CAN_RTR_FLAG ; 
 int DIV_ROUND_UP (int,int) ; 
 int KVASER_PCIEFD_PACKET_SEQ_MSK ; 
 int KVASER_PCIEFD_RPACKET_BRS ; 
 int KVASER_PCIEFD_RPACKET_DLC_SHIFT ; 
 int KVASER_PCIEFD_RPACKET_ESI ; 
 int KVASER_PCIEFD_RPACKET_FDF ; 
 int KVASER_PCIEFD_RPACKET_IDE ; 
 int KVASER_PCIEFD_RPACKET_RTR ; 
 int KVASER_PCIEFD_TPACKET_AREQ ; 
 int KVASER_PCIEFD_TPACKET_SMS ; 
 scalar_t__ can_is_canfd_skb (struct sk_buff*) ; 
 int can_len2dlc (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (struct kvaser_pciefd_tx_packet*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int kvaser_pciefd_prepare_tx_packet(struct kvaser_pciefd_tx_packet *p,
					   struct kvaser_pciefd_can *can,
					   struct sk_buff *skb)
{
	struct canfd_frame *cf = (struct canfd_frame *)skb->data;
	int packet_size;
	int seq = can->echo_idx;

	memset(p, 0, sizeof(*p));

	if (can->can.ctrlmode & CAN_CTRLMODE_ONE_SHOT)
		p->header[1] |= KVASER_PCIEFD_TPACKET_SMS;

	if (cf->can_id & CAN_RTR_FLAG)
		p->header[0] |= KVASER_PCIEFD_RPACKET_RTR;

	if (cf->can_id & CAN_EFF_FLAG)
		p->header[0] |= KVASER_PCIEFD_RPACKET_IDE;

	p->header[0] |= cf->can_id & CAN_EFF_MASK;
	p->header[1] |= can_len2dlc(cf->len) << KVASER_PCIEFD_RPACKET_DLC_SHIFT;
	p->header[1] |= KVASER_PCIEFD_TPACKET_AREQ;

	if (can_is_canfd_skb(skb)) {
		p->header[1] |= KVASER_PCIEFD_RPACKET_FDF;
		if (cf->flags & CANFD_BRS)
			p->header[1] |= KVASER_PCIEFD_RPACKET_BRS;
		if (cf->flags & CANFD_ESI)
			p->header[1] |= KVASER_PCIEFD_RPACKET_ESI;
	}

	p->header[1] |= seq & KVASER_PCIEFD_PACKET_SEQ_MSK;

	packet_size = cf->len;
	memcpy(p->data, cf->data, packet_size);

	return DIV_ROUND_UP(packet_size, 4);
}