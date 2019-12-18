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
struct stats_time_cache {int dummy; } ;
struct stats_event_cache {int dummy; } ;
struct mod_stats {int dummy; } ;
struct core_stats {int entries; int event_entries; int index; scalar_t__ entry_id; scalar_t__ event_index; int /*<<< orphan*/  events; int /*<<< orphan*/  time; } ;

/* Variables and functions */
 struct core_stats* MOD_STATS_TO_CORE (struct mod_stats*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void mod_stats_reset_data(struct mod_stats *mod_stats)
{
	struct core_stats *core_stats = NULL;
	struct stats_time_cache *time = NULL;
	unsigned int index = 0;

	if (mod_stats == NULL)
		return;

	core_stats = MOD_STATS_TO_CORE(mod_stats);

	memset(core_stats->time, 0,
		sizeof(struct stats_time_cache) * core_stats->entries);

	memset(core_stats->events, 0,
		sizeof(struct stats_event_cache) * core_stats->event_entries);

	core_stats->index = 1;
	core_stats->event_index = 0;

	// Keeps track of ordering within the different stats structures
	core_stats->entry_id = 0;
}