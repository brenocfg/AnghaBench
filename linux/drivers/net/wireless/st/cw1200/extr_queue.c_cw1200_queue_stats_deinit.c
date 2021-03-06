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
struct cw1200_queue_stats {int /*<<< orphan*/ * link_map_cache; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 

void cw1200_queue_stats_deinit(struct cw1200_queue_stats *stats)
{
	kfree(stats->link_map_cache);
	stats->link_map_cache = NULL;
}