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
struct sk_buff {int /*<<< orphan*/  csum; } ;
struct mlx5e_rq_stats {int /*<<< orphan*/  csum_complete_tail_slow; } ;

/* Variables and functions */
 int /*<<< orphan*/  csum_block_add (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  skb_checksum (struct sk_buff*,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
tail_padding_csum_slow(struct sk_buff *skb, int offset, int len,
		       struct mlx5e_rq_stats *stats)
{
	stats->csum_complete_tail_slow++;
	skb->csum = csum_block_add(skb->csum,
				   skb_checksum(skb, offset, len, 0),
				   offset);
}