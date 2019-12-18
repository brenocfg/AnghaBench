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
struct sk_buff {int dummy; } ;
struct llt_ndlc {int /*<<< orphan*/  sm_work; int /*<<< orphan*/  send_q; } ;

/* Variables and functions */
 int PCB_DATAFRAME_RETRANSMIT_NO ; 
 int PCB_FRAME_CRC_INFO_NOTPRESENT ; 
 int PCB_TYPE_DATAFRAME ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 scalar_t__ skb_push (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_queue_tail (int /*<<< orphan*/ *,struct sk_buff*) ; 

int ndlc_send(struct llt_ndlc *ndlc, struct sk_buff *skb)
{
	/* add ndlc header */
	u8 pcb = PCB_TYPE_DATAFRAME | PCB_DATAFRAME_RETRANSMIT_NO |
		PCB_FRAME_CRC_INFO_NOTPRESENT;

	*(u8 *)skb_push(skb, 1) = pcb;
	skb_queue_tail(&ndlc->send_q, skb);

	schedule_work(&ndlc->sm_work);

	return 0;
}