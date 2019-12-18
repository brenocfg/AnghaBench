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
struct dchannel {int /*<<< orphan*/  rqueue; } ;

/* Variables and functions */
 int /*<<< orphan*/  FLG_RECVQUEUE ; 
 int /*<<< orphan*/  schedule_event (struct dchannel*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_queue_tail (int /*<<< orphan*/ *,struct sk_buff*) ; 

void
recv_Dchannel_skb(struct dchannel *dch, struct sk_buff *skb)
{
	skb_queue_tail(&dch->rqueue, skb);
	schedule_event(dch, FLG_RECVQUEUE);
}