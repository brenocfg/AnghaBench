#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct sk_buff {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  atomic_orig; int /*<<< orphan*/  msn; } ;
struct TYPE_6__ {int /*<<< orphan*/  dest_qp_num; } ;
struct TYPE_5__ {int /*<<< orphan*/  device; } ;
struct rxe_qp {TYPE_3__ resp; TYPE_2__ attr; int /*<<< orphan*/  pri_av; TYPE_1__ ibqp; } ;
struct rxe_pkt_info {int opcode; int mask; int paylen; int /*<<< orphan*/  psn; scalar_t__ offset; int /*<<< orphan*/  hdr; struct rxe_qp* qp; } ;
struct rxe_dev {int dummy; } ;
struct TYPE_8__ {int length; int mask; } ;

/* Variables and functions */
 int RXE_AETH_MASK ; 
 int RXE_ATMACK_MASK ; 
 scalar_t__ RXE_BTH_BYTES ; 
 int RXE_ICRC_SIZE ; 
 int /*<<< orphan*/  aeth_set_msn (struct rxe_pkt_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aeth_set_syn (struct rxe_pkt_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atmack_set_orig (struct rxe_pkt_info*,int /*<<< orphan*/ ) ; 
 int bth_pad (struct rxe_pkt_info*) ; 
 int /*<<< orphan*/  bth_set_ack (struct rxe_pkt_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bth_set_opcode (struct rxe_pkt_info*,int) ; 
 int /*<<< orphan*/  bth_set_pad (struct rxe_pkt_info*,int) ; 
 int /*<<< orphan*/  bth_set_psn (struct rxe_pkt_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bth_set_qpn (struct rxe_pkt_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bth_set_se (struct rxe_pkt_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/ * payload_addr (struct rxe_pkt_info*) ; 
 struct sk_buff* rxe_init_packet (struct rxe_dev*,int /*<<< orphan*/ *,int,struct rxe_pkt_info*) ; 
 TYPE_4__* rxe_opcode ; 
 int rxe_prepare (struct rxe_pkt_info*,struct sk_buff*,int /*<<< orphan*/ *) ; 
 struct rxe_dev* to_rdev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct sk_buff *prepare_ack_packet(struct rxe_qp *qp,
					  struct rxe_pkt_info *pkt,
					  struct rxe_pkt_info *ack,
					  int opcode,
					  int payload,
					  u32 psn,
					  u8 syndrome,
					  u32 *crcp)
{
	struct rxe_dev *rxe = to_rdev(qp->ibqp.device);
	struct sk_buff *skb;
	u32 crc = 0;
	u32 *p;
	int paylen;
	int pad;
	int err;

	/*
	 * allocate packet
	 */
	pad = (-payload) & 0x3;
	paylen = rxe_opcode[opcode].length + payload + pad + RXE_ICRC_SIZE;

	skb = rxe_init_packet(rxe, &qp->pri_av, paylen, ack);
	if (!skb)
		return NULL;

	ack->qp = qp;
	ack->opcode = opcode;
	ack->mask = rxe_opcode[opcode].mask;
	ack->offset = pkt->offset;
	ack->paylen = paylen;

	/* fill in bth using the request packet headers */
	memcpy(ack->hdr, pkt->hdr, pkt->offset + RXE_BTH_BYTES);

	bth_set_opcode(ack, opcode);
	bth_set_qpn(ack, qp->attr.dest_qp_num);
	bth_set_pad(ack, pad);
	bth_set_se(ack, 0);
	bth_set_psn(ack, psn);
	bth_set_ack(ack, 0);
	ack->psn = psn;

	if (ack->mask & RXE_AETH_MASK) {
		aeth_set_syn(ack, syndrome);
		aeth_set_msn(ack, qp->resp.msn);
	}

	if (ack->mask & RXE_ATMACK_MASK)
		atmack_set_orig(ack, qp->resp.atomic_orig);

	err = rxe_prepare(ack, skb, &crc);
	if (err) {
		kfree_skb(skb);
		return NULL;
	}

	if (crcp) {
		/* CRC computation will be continued by the caller */
		*crcp = crc;
	} else {
		p = payload_addr(ack) + payload + bth_pad(ack);
		*p = ~crc;
	}

	return skb;
}