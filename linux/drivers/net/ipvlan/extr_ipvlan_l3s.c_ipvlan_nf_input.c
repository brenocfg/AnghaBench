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
struct sk_buff {unsigned int len; int /*<<< orphan*/  dev; } ;
struct nf_hook_state {int dummy; } ;
struct ipvl_addr {TYPE_1__* master; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 unsigned int ETH_HLEN ; 
 unsigned int NF_ACCEPT ; 
 int /*<<< orphan*/  ipvlan_count_rx (TYPE_1__*,unsigned int,int,int) ; 
 struct ipvl_addr* ipvlan_skb_to_addr (struct sk_buff*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int ipvlan_nf_input(void *priv, struct sk_buff *skb,
				    const struct nf_hook_state *state)
{
	struct ipvl_addr *addr;
	unsigned int len;

	addr = ipvlan_skb_to_addr(skb, skb->dev);
	if (!addr)
		goto out;

	skb->dev = addr->master->dev;
	len = skb->len + ETH_HLEN;
	ipvlan_count_rx(addr->master, len, true, false);
out:
	return NF_ACCEPT;
}