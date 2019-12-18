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
struct ppp {int /*<<< orphan*/  closing; } ;
struct channel {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  ppp_receive_frame (struct ppp*,struct sk_buff*,struct channel*) ; 
 int /*<<< orphan*/  ppp_recv_lock (struct ppp*) ; 
 int /*<<< orphan*/  ppp_recv_unlock (struct ppp*) ; 

__attribute__((used)) static inline void
ppp_do_recv(struct ppp *ppp, struct sk_buff *skb, struct channel *pch)
{
	ppp_recv_lock(ppp);
	if (!ppp->closing)
		ppp_receive_frame(ppp, skb, pch);
	else
		kfree_skb(skb);
	ppp_recv_unlock(ppp);
}