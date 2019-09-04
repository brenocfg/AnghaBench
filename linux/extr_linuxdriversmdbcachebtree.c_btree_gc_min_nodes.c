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
struct TYPE_2__ {size_t nodes; } ;
struct cache_set {TYPE_1__ gc_stats; } ;

/* Variables and functions */
 size_t MAX_GC_TIMES ; 
 size_t MIN_GC_NODES ; 

__attribute__((used)) static size_t btree_gc_min_nodes(struct cache_set *c)
{
	size_t min_nodes;

	/*
	 * Since incremental GC would stop 100ms when front
	 * side I/O comes, so when there are many btree nodes,
	 * if GC only processes constant (100) nodes each time,
	 * GC would last a long time, and the front side I/Os
	 * would run out of the buckets (since no new bucket
	 * can be allocated during GC), and be blocked again.
	 * So GC should not process constant nodes, but varied
	 * nodes according to the number of btree nodes, which
	 * realized by dividing GC into constant(100) times,
	 * so when there are many btree nodes, GC can process
	 * more nodes each time, otherwise, GC will process less
	 * nodes each time (but no less than MIN_GC_NODES)
	 */
	min_nodes = c->gc_stats.nodes / MAX_GC_TIMES;
	if (min_nodes < MIN_GC_NODES)
		min_nodes = MIN_GC_NODES;

	return min_nodes;
}