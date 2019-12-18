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
struct sk_buff {int len; scalar_t__ encapsulation; } ;
struct cpl_tx_tnl_lso {int dummy; } ;
struct cpl_tx_pkt_lso_core {int dummy; } ;
struct cpl_tx_pkt_core {int dummy; } ;
struct cpl_tx_pkt {int dummy; } ;
struct TYPE_2__ {scalar_t__ gso_size; } ;

/* Variables and functions */
 unsigned int CHELSIO_T5 ; 
 int MAX_IMM_TX_PKT_LEN ; 
 TYPE_1__* skb_shinfo (struct sk_buff const*) ; 

__attribute__((used)) static inline int is_eth_imm(const struct sk_buff *skb, unsigned int chip_ver)
{
	int hdrlen = 0;

	if (skb->encapsulation && skb_shinfo(skb)->gso_size &&
	    chip_ver > CHELSIO_T5) {
		hdrlen = sizeof(struct cpl_tx_tnl_lso);
		hdrlen += sizeof(struct cpl_tx_pkt_core);
	} else {
		hdrlen = skb_shinfo(skb)->gso_size ?
			 sizeof(struct cpl_tx_pkt_lso_core) : 0;
		hdrlen += sizeof(struct cpl_tx_pkt);
	}
	if (skb->len <= MAX_IMM_TX_PKT_LEN - hdrlen)
		return hdrlen;
	return 0;
}