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
struct tcp_sock {int /*<<< orphan*/  write_seq; int /*<<< orphan*/  snd_up; } ;
struct sk_buff {int dummy; } ;
struct TYPE_2__ {int flags; } ;

/* Variables and functions */
 int MSG_OOB ; 
 int ULPCB_FLAG_BARRIER ; 
 int ULPCB_FLAG_NEED_HDR ; 
 int ULPCB_FLAG_NO_APPEND ; 
 int ULPCB_FLAG_URG ; 
 TYPE_1__* ULP_SKB_CB (struct sk_buff*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void mark_urg(struct tcp_sock *tp, int flags,
		     struct sk_buff *skb)
{
	if (unlikely(flags & MSG_OOB)) {
		tp->snd_up = tp->write_seq;
		ULP_SKB_CB(skb)->flags = ULPCB_FLAG_URG |
					 ULPCB_FLAG_BARRIER |
					 ULPCB_FLAG_NO_APPEND |
					 ULPCB_FLAG_NEED_HDR;
	}
}