#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  nospace; } ;
struct TYPE_3__ {scalar_t__ fulldup; } ;
struct scc_channel {TYPE_2__ stat; TYPE_1__ kiss; } ;

/* Variables and functions */
 scalar_t__ KISS_DUPLEX_OPTIMA ; 
 int /*<<< orphan*/  PARAM_HWEVENT ; 
 struct sk_buff* dev_alloc_skb (int) ; 
 int /*<<< orphan*/  scc_net_rx (struct scc_channel*,struct sk_buff*) ; 
 char* skb_put (struct sk_buff*,int) ; 

__attribute__((used)) static inline void scc_notify(struct scc_channel *scc, int event)
{
	struct sk_buff *skb;
	char *bp;
	
        if (scc->kiss.fulldup != KISS_DUPLEX_OPTIMA)
		return;

	skb = dev_alloc_skb(2);
	if (skb != NULL)
	{
		bp = skb_put(skb, 2);
		*bp++ = PARAM_HWEVENT;
		*bp++ = event;
		scc_net_rx(scc, skb);
	} else
		scc->stat.nospace++;
}