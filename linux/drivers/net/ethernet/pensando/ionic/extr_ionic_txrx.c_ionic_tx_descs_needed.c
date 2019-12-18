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
struct sk_buff {int len; } ;
struct ionic_tx_stats {int /*<<< orphan*/  linearize; } ;
struct ionic_queue {int dummy; } ;
struct TYPE_2__ {int gso_size; scalar_t__ nr_frags; } ;

/* Variables and functions */
 scalar_t__ IONIC_TX_MAX_SG_ELEMS ; 
 struct ionic_tx_stats* q_to_tx_stats (struct ionic_queue*) ; 
 scalar_t__ skb_is_gso (struct sk_buff*) ; 
 int skb_linearize (struct sk_buff*) ; 
 TYPE_1__* skb_shinfo (struct sk_buff*) ; 

__attribute__((used)) static int ionic_tx_descs_needed(struct ionic_queue *q, struct sk_buff *skb)
{
	struct ionic_tx_stats *stats = q_to_tx_stats(q);
	int err;

	/* If TSO, need roundup(skb->len/mss) descs */
	if (skb_is_gso(skb))
		return (skb->len / skb_shinfo(skb)->gso_size) + 1;

	/* If non-TSO, just need 1 desc and nr_frags sg elems */
	if (skb_shinfo(skb)->nr_frags <= IONIC_TX_MAX_SG_ELEMS)
		return 1;

	/* Too many frags, so linearize */
	err = skb_linearize(skb);
	if (err)
		return err;

	stats->linearize++;

	/* Need 1 desc and zero sg elems */
	return 1;
}