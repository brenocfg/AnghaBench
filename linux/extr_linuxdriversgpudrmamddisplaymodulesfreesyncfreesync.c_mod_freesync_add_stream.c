#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct persistent_data_flag {int save_per_edid; int save_per_link; } ;
struct mod_freesync_caps {unsigned int min_refresh_in_micro_hz; unsigned int max_refresh_in_micro_hz; scalar_t__ supported; } ;
struct mod_freesync {int dummy; } ;
struct TYPE_8__ {unsigned long long pix_clk_khz; int /*<<< orphan*/  v_total; int /*<<< orphan*/  h_total; } ;
struct dc_stream_state {int ignore_msa_timing_param; int /*<<< orphan*/  sink; TYPE_1__ timing; } ;
struct dc {int /*<<< orphan*/  ctx; } ;
struct TYPE_12__ {int lcd_freesync_default_value; scalar_t__ lcd_freesync_default_set; } ;
struct core_freesync {size_t num_entities; TYPE_7__* map; TYPE_5__ opts; struct dc* dc; } ;
struct TYPE_13__ {int enable_for_gaming; int enable_for_static; int enable_for_video; } ;
struct TYPE_10__ {int ramp_is_active; } ;
struct TYPE_9__ {scalar_t__ update_duration_in_ns; } ;
struct TYPE_11__ {int fullscreen; int static_screen; int video; TYPE_3__ static_ramp; TYPE_2__ time; } ;
struct TYPE_14__ {TYPE_6__ user_enable; TYPE_4__ state; struct mod_freesync_caps* caps; struct dc_stream_state* stream; } ;

/* Variables and functions */
 int /*<<< orphan*/  FREESYNC_REGISTRY_NAME ; 
 size_t MOD_FREESYNC_MAX_CONCURRENT_STREAMS ; 
 struct core_freesync* MOD_FREESYNC_TO_CORE (struct mod_freesync*) ; 
 int /*<<< orphan*/  dc_stream_retain (struct dc_stream_state*) ; 
 unsigned long long div_u64 (unsigned long long,int /*<<< orphan*/ ) ; 
 scalar_t__ dm_read_persistent_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int*,int,struct persistent_data_flag*) ; 
 int /*<<< orphan*/  dm_write_persistent_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int*,int,struct persistent_data_flag*) ; 

bool mod_freesync_add_stream(struct mod_freesync *mod_freesync,
		struct dc_stream_state *stream, struct mod_freesync_caps *caps)
{
	struct dc  *dc = NULL;
	struct core_freesync *core_freesync = NULL;
	int persistent_freesync_enable = 0;
	struct persistent_data_flag flag;
	unsigned int nom_refresh_rate_uhz;
	unsigned long long temp;

	if (mod_freesync == NULL)
		return false;

	core_freesync = MOD_FREESYNC_TO_CORE(mod_freesync);
	dc = core_freesync->dc;

	flag.save_per_edid = true;
	flag.save_per_link = false;

	if (core_freesync->num_entities < MOD_FREESYNC_MAX_CONCURRENT_STREAMS) {

		dc_stream_retain(stream);

		temp = stream->timing.pix_clk_khz;
		temp *= 1000ULL * 1000ULL * 1000ULL;
		temp = div_u64(temp, stream->timing.h_total);
		temp = div_u64(temp, stream->timing.v_total);

		nom_refresh_rate_uhz = (unsigned int) temp;

		core_freesync->map[core_freesync->num_entities].stream = stream;
		core_freesync->map[core_freesync->num_entities].caps = caps;

		core_freesync->map[core_freesync->num_entities].state.
			fullscreen = false;
		core_freesync->map[core_freesync->num_entities].state.
			static_screen = false;
		core_freesync->map[core_freesync->num_entities].state.
			video = false;
		core_freesync->map[core_freesync->num_entities].state.time.
			update_duration_in_ns = 0;
		core_freesync->map[core_freesync->num_entities].state.
			static_ramp.ramp_is_active = false;

		/* get persistent data from registry */
		if (dm_read_persistent_data(dc->ctx, stream->sink,
					FREESYNC_REGISTRY_NAME,
					"userenable", &persistent_freesync_enable,
					sizeof(int), &flag)) {
			core_freesync->map[core_freesync->num_entities].user_enable.
				enable_for_gaming =
				(persistent_freesync_enable & 1) ? true : false;
			core_freesync->map[core_freesync->num_entities].user_enable.
				enable_for_static =
				(persistent_freesync_enable & 2) ? true : false;
			core_freesync->map[core_freesync->num_entities].user_enable.
				enable_for_video =
				(persistent_freesync_enable & 4) ? true : false;
		/* If FreeSync display and LCDFreeSyncDefault is set, use as default values write back to userenable */
		} else if (caps->supported && (core_freesync->opts.lcd_freesync_default_set)) {
			core_freesync->map[core_freesync->num_entities].user_enable.enable_for_gaming =
				(core_freesync->opts.lcd_freesync_default_value & 1) ? true : false;
			core_freesync->map[core_freesync->num_entities].user_enable.enable_for_static =
				(core_freesync->opts.lcd_freesync_default_value & 2) ? true : false;
			core_freesync->map[core_freesync->num_entities].user_enable.enable_for_video =
				(core_freesync->opts.lcd_freesync_default_value & 4) ? true : false;
			dm_write_persistent_data(dc->ctx, stream->sink,
						FREESYNC_REGISTRY_NAME,
						"userenable", &core_freesync->opts.lcd_freesync_default_value,
						sizeof(int), &flag);
		} else {
			core_freesync->map[core_freesync->num_entities].user_enable.
					enable_for_gaming = false;
			core_freesync->map[core_freesync->num_entities].user_enable.
					enable_for_static = false;
			core_freesync->map[core_freesync->num_entities].user_enable.
					enable_for_video = false;
		}

		if (caps->supported &&
			nom_refresh_rate_uhz >= caps->min_refresh_in_micro_hz &&
			nom_refresh_rate_uhz <= caps->max_refresh_in_micro_hz)
			stream->ignore_msa_timing_param = 1;

		core_freesync->num_entities++;
		return true;
	}
	return false;
}