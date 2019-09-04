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
struct stats_time_cache {unsigned int v_total_min; unsigned int v_total_max; unsigned int event_triggers; unsigned int min_window; unsigned int max_window; unsigned int lfc_mid_point_in_us; unsigned int num_frames_inserted; unsigned int inserted_duration_in_us; } ;
struct mod_stats {int dummy; } ;
struct core_stats {unsigned int index; unsigned int entries; struct stats_time_cache* time; } ;

/* Variables and functions */
 struct core_stats* MOD_STATS_TO_CORE (struct mod_stats*) ; 

void mod_stats_update_freesync(struct mod_stats *mod_stats,
		unsigned int v_total_min,
		unsigned int v_total_max,
		unsigned int event_triggers,
		unsigned int window_min,
		unsigned int window_max,
		unsigned int lfc_mid_point_in_us,
		unsigned int inserted_frames,
		unsigned int inserted_duration_in_us)
{
	struct core_stats *core_stats = NULL;
	struct stats_time_cache *time = NULL;
	unsigned int index = 0;

	if (mod_stats == NULL)
		return;

	core_stats = MOD_STATS_TO_CORE(mod_stats);

	if (core_stats->index >= core_stats->entries)
		return;

	time = core_stats->time;
	index = core_stats->index;

	time[index].v_total_min = v_total_min;
	time[index].v_total_max = v_total_max;
	time[index].event_triggers = event_triggers;
	time[index].min_window = window_min;
	time[index].max_window = window_max;
	time[index].lfc_mid_point_in_us = lfc_mid_point_in_us;
	time[index].num_frames_inserted = inserted_frames;
	time[index].inserted_duration_in_us = inserted_duration_in_us;
}