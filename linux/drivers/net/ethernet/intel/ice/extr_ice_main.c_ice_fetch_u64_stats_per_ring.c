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
typedef  scalar_t__ u64 ;
struct TYPE_2__ {scalar_t__ bytes; scalar_t__ pkts; } ;
struct ice_ring {TYPE_1__ stats; int /*<<< orphan*/  syncp; } ;

/* Variables and functions */
 unsigned int u64_stats_fetch_begin_irq (int /*<<< orphan*/ *) ; 
 scalar_t__ u64_stats_fetch_retry_irq (int /*<<< orphan*/ *,unsigned int) ; 

__attribute__((used)) static void
ice_fetch_u64_stats_per_ring(struct ice_ring *ring, u64 *pkts, u64 *bytes)
{
	unsigned int start;
	*pkts = 0;
	*bytes = 0;

	if (!ring)
		return;
	do {
		start = u64_stats_fetch_begin_irq(&ring->syncp);
		*pkts = ring->stats.pkts;
		*bytes = ring->stats.bytes;
	} while (u64_stats_fetch_retry_irq(&ring->syncp, start));
}