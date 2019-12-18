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
struct sk_buff {int dummy; } ;
struct rxe_pkt_info {int mask; int /*<<< orphan*/  qp; } ;

/* Variables and functions */
 int RXE_REQ_MASK ; 
 int /*<<< orphan*/  rxe_comp_queue_pkt (int /*<<< orphan*/ ,struct sk_buff*) ; 
 int /*<<< orphan*/  rxe_resp_queue_pkt (int /*<<< orphan*/ ,struct sk_buff*) ; 

__attribute__((used)) static inline void rxe_rcv_pkt(struct rxe_pkt_info *pkt, struct sk_buff *skb)
{
	if (pkt->mask & RXE_REQ_MASK)
		rxe_resp_queue_pkt(pkt->qp, skb);
	else
		rxe_comp_queue_pkt(pkt->qp, skb);
}