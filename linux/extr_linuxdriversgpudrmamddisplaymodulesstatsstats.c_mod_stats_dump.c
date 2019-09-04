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
struct stats_time_cache {int entry_id; char* render_time_in_us; char* avg_render_time_in_us_last_ten; char* min_window; char* lfc_mid_point_in_us; char* max_window; char* vsync_to_flip_time_in_us; char* flip_to_vsync_time_in_us; char* num_vsync_between_flips; char* num_frames_inserted; char* inserted_duration_in_us; char* v_total_min; char* v_total_max; char* event_triggers; char** v_sync_time_in_us; char* flags; } ;
struct stats_event_cache {int entry_id; int /*<<< orphan*/  event_string; } ;
struct mod_stats {int dummy; } ;
struct log_entry {int dummy; } ;
struct dc {TYPE_1__* ctx; } ;
struct dal_logger {int dummy; } ;
struct core_stats {int entry_id; unsigned int event_index; unsigned int index; struct stats_event_cache* events; struct stats_time_cache* time; struct dc* dc; } ;
struct TYPE_2__ {struct dal_logger* logger; } ;

/* Variables and functions */
 int /*<<< orphan*/  DISPLAY_STATS (char*,...) ; 
 int /*<<< orphan*/  DISPLAY_STATS_BEGIN (struct log_entry) ; 
 int /*<<< orphan*/  DISPLAY_STATS_END (struct log_entry) ; 
 struct core_stats* MOD_STATS_TO_CORE (struct mod_stats*) ; 

void mod_stats_dump(struct mod_stats *mod_stats)
{
	struct dc  *dc = NULL;
	struct dal_logger *logger = NULL;
	struct core_stats *core_stats = NULL;
	struct stats_time_cache *time = NULL;
	struct stats_event_cache *events = NULL;
	unsigned int time_index = 1;
	unsigned int event_index = 0;
	unsigned int index = 0;
	struct log_entry log_entry;

	if (mod_stats == NULL)
		return;

	core_stats = MOD_STATS_TO_CORE(mod_stats);
	dc = core_stats->dc;
	logger = dc->ctx->logger;
	time = core_stats->time;
	events = core_stats->events;

	DISPLAY_STATS_BEGIN(log_entry);

	DISPLAY_STATS("==Display Caps==\n");

	DISPLAY_STATS("==Display Stats==\n");

	DISPLAY_STATS("%10s %10s %10s %10s %10s"
			" %11s %11s %17s %10s %14s"
			" %10s %10s %10s %10s %10s"
			" %10s %10s %10s %10s\n",
		"render", "avgRender",
		"minWindow", "midPoint", "maxWindow",
		"vsyncToFlip", "flipToVsync", "vsyncsBetweenFlip",
		"numFrame", "insertDuration",
		"vTotalMin", "vTotalMax", "eventTrigs",
		"vSyncTime1", "vSyncTime2", "vSyncTime3",
		"vSyncTime4", "vSyncTime5", "flags");

	for (int i = 0; i < core_stats->entry_id; i++) {
		if (event_index < core_stats->event_index &&
				i == events[event_index].entry_id) {
			DISPLAY_STATS("==Event==%s\n", events[event_index].event_string);
			event_index++;
		} else if (time_index < core_stats->index &&
				i == time[time_index].entry_id) {
			DISPLAY_STATS("%10u %10u %10u %10u %10u"
					" %11u %11u %17u %10u %14u"
					" %10u %10u %10u %10u %10u"
					" %10u %10u %10u %10u\n",
				time[time_index].render_time_in_us,
				time[time_index].avg_render_time_in_us_last_ten,
				time[time_index].min_window,
				time[time_index].lfc_mid_point_in_us,
				time[time_index].max_window,
				time[time_index].vsync_to_flip_time_in_us,
				time[time_index].flip_to_vsync_time_in_us,
				time[time_index].num_vsync_between_flips,
				time[time_index].num_frames_inserted,
				time[time_index].inserted_duration_in_us,
				time[time_index].v_total_min,
				time[time_index].v_total_max,
				time[time_index].event_triggers,
				time[time_index].v_sync_time_in_us[0],
				time[time_index].v_sync_time_in_us[1],
				time[time_index].v_sync_time_in_us[2],
				time[time_index].v_sync_time_in_us[3],
				time[time_index].v_sync_time_in_us[4],
				time[time_index].flags);

			time_index++;
		}
	}

	DISPLAY_STATS_END(log_entry);
}