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
struct TYPE_3__ {int /*<<< orphan*/  linearize_failed; int /*<<< orphan*/  linearize; } ;
struct ena_ring {int sgl_size; int tx_max_header_size; int /*<<< orphan*/  syncp; TYPE_1__ tx_stats; } ;
struct TYPE_4__ {int nr_frags; } ;

/* Variables and functions */
 int skb_headlen (struct sk_buff*) ; 
 int skb_linearize (struct sk_buff*) ; 
 TYPE_2__* skb_shinfo (struct sk_buff*) ; 
 int /*<<< orphan*/  u64_stats_update_begin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  u64_stats_update_end (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int ena_check_and_linearize_skb(struct ena_ring *tx_ring,
				       struct sk_buff *skb)
{
	int num_frags, header_len, rc;

	num_frags = skb_shinfo(skb)->nr_frags;
	header_len = skb_headlen(skb);

	if (num_frags < tx_ring->sgl_size)
		return 0;

	if ((num_frags == tx_ring->sgl_size) &&
	    (header_len < tx_ring->tx_max_header_size))
		return 0;

	u64_stats_update_begin(&tx_ring->syncp);
	tx_ring->tx_stats.linearize++;
	u64_stats_update_end(&tx_ring->syncp);

	rc = skb_linearize(skb);
	if (unlikely(rc)) {
		u64_stats_update_begin(&tx_ring->syncp);
		tx_ring->tx_stats.linearize_failed++;
		u64_stats_update_end(&tx_ring->syncp);
	}

	return rc;
}