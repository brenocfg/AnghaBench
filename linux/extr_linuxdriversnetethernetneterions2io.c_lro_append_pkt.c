#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct swStat {int /*<<< orphan*/  clubbed_frms_cnt; } ;
struct sk_buff {scalar_t__ truesize; struct sk_buff* next; scalar_t__ len; int /*<<< orphan*/  data_len; } ;
struct TYPE_5__ {TYPE_1__* stats_info; } ;
struct s2io_nic {TYPE_2__ mac_control; } ;
struct lro {struct sk_buff* last_frag; int /*<<< orphan*/  frags_len; struct sk_buff* parent; } ;
struct TYPE_6__ {struct sk_buff* frag_list; } ;
struct TYPE_4__ {struct swStat sw_stat; } ;

/* Variables and functions */
 int /*<<< orphan*/  skb_pull (struct sk_buff*,scalar_t__) ; 
 TYPE_3__* skb_shinfo (struct sk_buff*) ; 

__attribute__((used)) static void lro_append_pkt(struct s2io_nic *sp, struct lro *lro,
			   struct sk_buff *skb, u32 tcp_len)
{
	struct sk_buff *first = lro->parent;
	struct swStat *swstats = &sp->mac_control.stats_info->sw_stat;

	first->len += tcp_len;
	first->data_len = lro->frags_len;
	skb_pull(skb, (skb->len - tcp_len));
	if (skb_shinfo(first)->frag_list)
		lro->last_frag->next = skb;
	else
		skb_shinfo(first)->frag_list = skb;
	first->truesize += skb->truesize;
	lro->last_frag = skb;
	swstats->clubbed_frms_cnt++;
}