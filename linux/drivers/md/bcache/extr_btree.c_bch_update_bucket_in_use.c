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
struct gc_stat {int in_use; } ;
struct cache_set {int nbuckets; int avail_nbuckets; } ;

/* Variables and functions */

void bch_update_bucket_in_use(struct cache_set *c, struct gc_stat *stats)
{
	stats->in_use = (c->nbuckets - c->avail_nbuckets) * 100 / c->nbuckets;
}