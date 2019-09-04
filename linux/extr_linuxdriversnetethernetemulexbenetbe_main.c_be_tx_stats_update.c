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
typedef  int u32 ;
struct sk_buff {int len; scalar_t__ ip_summed; scalar_t__ encapsulation; } ;
struct be_tx_stats {int tx_pkts; int tx_vxlan_offload_pkts; int /*<<< orphan*/  sync; int /*<<< orphan*/  tx_bytes; int /*<<< orphan*/  tx_reqs; } ;
struct be_tx_obj {int dummy; } ;
struct TYPE_2__ {scalar_t__ gso_segs; } ;

/* Variables and functions */
 scalar_t__ CHECKSUM_PARTIAL ; 
 int be_gso_hdr_len (struct sk_buff*) ; 
 TYPE_1__* skb_shinfo (struct sk_buff*) ; 
 struct be_tx_stats* tx_stats (struct be_tx_obj*) ; 
 int /*<<< orphan*/  u64_stats_update_begin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  u64_stats_update_end (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void be_tx_stats_update(struct be_tx_obj *txo, struct sk_buff *skb)
{
	struct be_tx_stats *stats = tx_stats(txo);
	u32 tx_pkts = skb_shinfo(skb)->gso_segs ? : 1;
	/* Account for headers which get duplicated in TSO pkt */
	u32 dup_hdr_len = tx_pkts > 1 ? be_gso_hdr_len(skb) * (tx_pkts - 1) : 0;

	u64_stats_update_begin(&stats->sync);
	stats->tx_reqs++;
	stats->tx_bytes += skb->len + dup_hdr_len;
	stats->tx_pkts += tx_pkts;
	if (skb->encapsulation && skb->ip_summed == CHECKSUM_PARTIAL)
		stats->tx_vxlan_offload_pkts += tx_pkts;
	u64_stats_update_end(&stats->sync);
}