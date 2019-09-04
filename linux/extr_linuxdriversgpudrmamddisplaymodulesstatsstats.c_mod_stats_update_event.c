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
struct stats_event_cache {char* event_string; int /*<<< orphan*/  entry_id; } ;
struct mod_stats {int dummy; } ;
struct core_stats {unsigned int event_index; unsigned int event_entries; int /*<<< orphan*/  entry_id; struct stats_event_cache* events; } ;

/* Variables and functions */
 unsigned int MOD_STATS_EVENT_STRING_MAX ; 
 struct core_stats* MOD_STATS_TO_CORE (struct mod_stats*) ; 
 int /*<<< orphan*/  memcpy (char**,char*,unsigned int) ; 

void mod_stats_update_event(struct mod_stats *mod_stats,
		char *event_string,
		unsigned int length)
{
	struct core_stats *core_stats = NULL;
	struct stats_event_cache *events = NULL;
	unsigned int index = 0;
	unsigned int copy_length = 0;

	if (mod_stats == NULL)
		return;

	core_stats = MOD_STATS_TO_CORE(mod_stats);

	if (core_stats->event_index >= core_stats->event_entries)
		return;

	events = core_stats->events;
	index = core_stats->event_index;

	copy_length = length;
	if (length > MOD_STATS_EVENT_STRING_MAX)
		copy_length = MOD_STATS_EVENT_STRING_MAX;

	memcpy(&events[index].event_string, event_string, copy_length);
	events[index].event_string[copy_length - 1] = '\0';

	events[index].entry_id = core_stats->entry_id;
	core_stats->event_index++;
	core_stats->entry_id++;
}