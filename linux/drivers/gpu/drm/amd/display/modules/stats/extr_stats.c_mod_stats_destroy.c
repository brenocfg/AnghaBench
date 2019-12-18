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
struct mod_stats {int dummy; } ;
struct core_stats {struct core_stats* events; struct core_stats* time; } ;

/* Variables and functions */
 struct core_stats* MOD_STATS_TO_CORE (struct mod_stats*) ; 
 int /*<<< orphan*/  kfree (struct core_stats*) ; 

void mod_stats_destroy(struct mod_stats *mod_stats)
{
	if (mod_stats != NULL) {
		struct core_stats *core_stats = MOD_STATS_TO_CORE(mod_stats);

		kfree(core_stats->time);
		kfree(core_stats->events);
		kfree(core_stats);
	}
}