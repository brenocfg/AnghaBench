#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
typedef  scalar_t__ u32 ;
struct TYPE_7__ {unsigned long first; } ;
struct macb_queue {TYPE_3__ stats; } ;
struct TYPE_5__ {scalar_t__ tx_octets_31_0; } ;
struct TYPE_6__ {TYPE_1__ gem; } ;
struct macb {int (* macb_reg_readl ) (struct macb*,scalar_t__) ;int* ethtool_stats; unsigned int num_queues; struct macb_queue* queues; TYPE_2__ hw_stats; } ;
struct TYPE_8__ {scalar_t__ offset; } ;

/* Variables and functions */
 scalar_t__ GEM_OCTRXL ; 
 scalar_t__ GEM_OCTTXL ; 
 unsigned int GEM_STATS_LEN ; 
 unsigned int QUEUE_STATS_LEN ; 
 TYPE_4__* gem_statistics ; 
 int stub1 (struct macb*,scalar_t__) ; 
 int stub2 (struct macb*,scalar_t__) ; 

__attribute__((used)) static void gem_update_stats(struct macb *bp)
{
	struct macb_queue *queue;
	unsigned int i, q, idx;
	unsigned long *stat;

	u32 *p = &bp->hw_stats.gem.tx_octets_31_0;

	for (i = 0; i < GEM_STATS_LEN; ++i, ++p) {
		u32 offset = gem_statistics[i].offset;
		u64 val = bp->macb_reg_readl(bp, offset);

		bp->ethtool_stats[i] += val;
		*p += val;

		if (offset == GEM_OCTTXL || offset == GEM_OCTRXL) {
			/* Add GEM_OCTTXH, GEM_OCTRXH */
			val = bp->macb_reg_readl(bp, offset + 4);
			bp->ethtool_stats[i] += ((u64)val) << 32;
			*(++p) += val;
		}
	}

	idx = GEM_STATS_LEN;
	for (q = 0, queue = bp->queues; q < bp->num_queues; ++q, ++queue)
		for (i = 0, stat = &queue->stats.first; i < QUEUE_STATS_LEN; ++i, ++stat)
			bp->ethtool_stats[idx++] = *stat;
}