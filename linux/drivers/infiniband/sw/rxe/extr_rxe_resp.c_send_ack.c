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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct sk_buff {int dummy; } ;
struct rxe_qp {int dummy; } ;
struct rxe_pkt_info {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  IB_OPCODE_RC_ACKNOWLEDGE ; 
 int /*<<< orphan*/  pr_err_ratelimited (char*) ; 
 struct sk_buff* prepare_ack_packet (struct rxe_qp*,struct rxe_pkt_info*,struct rxe_pkt_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int rxe_xmit_packet (struct rxe_qp*,struct rxe_pkt_info*,struct sk_buff*) ; 

__attribute__((used)) static int send_ack(struct rxe_qp *qp, struct rxe_pkt_info *pkt,
		    u8 syndrome, u32 psn)
{
	int err = 0;
	struct rxe_pkt_info ack_pkt;
	struct sk_buff *skb;

	skb = prepare_ack_packet(qp, pkt, &ack_pkt, IB_OPCODE_RC_ACKNOWLEDGE,
				 0, psn, syndrome, NULL);
	if (!skb) {
		err = -ENOMEM;
		goto err1;
	}

	err = rxe_xmit_packet(qp, &ack_pkt, skb);
	if (err)
		pr_err_ratelimited("Failed sending ack\n");

err1:
	return err;
}