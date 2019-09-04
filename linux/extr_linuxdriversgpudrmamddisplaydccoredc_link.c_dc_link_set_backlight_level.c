#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_9__ ;
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct dmcu {TYPE_3__* funcs; } ;
struct dc_stream_state {scalar_t__ bl_pwm_level; } ;
struct dc_link {int /*<<< orphan*/  connector_signal; TYPE_2__* ctx; } ;
struct dc {TYPE_8__* current_state; TYPE_1__* res_pool; } ;
struct abm {TYPE_9__* funcs; } ;
struct TYPE_18__ {int /*<<< orphan*/  (* set_backlight_level ) (struct abm*,scalar_t__,scalar_t__,unsigned int,int) ;} ;
struct TYPE_16__ {TYPE_6__* pipe_ctx; } ;
struct TYPE_17__ {TYPE_7__ res_ctx; } ;
struct TYPE_14__ {TYPE_4__* tg; } ;
struct TYPE_15__ {TYPE_5__ stream_res; struct dc_stream_state const* stream; } ;
struct TYPE_13__ {int inst; } ;
struct TYPE_12__ {int (* is_dmcu_initialized ) (struct dmcu*) ;} ;
struct TYPE_11__ {int /*<<< orphan*/  logger; struct dc* dc; } ;
struct TYPE_10__ {struct dmcu* dmcu; struct abm* abm; } ;

/* Variables and functions */
 int /*<<< orphan*/  DC_LOGGER_INIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DC_LOG_BACKLIGHT (char*,scalar_t__,scalar_t__) ; 
 scalar_t__ EDP_BACKLIGHT_RAMP_DISABLE_LEVEL ; 
 int MAX_PIPES ; 
 scalar_t__ dc_is_embedded_signal (int /*<<< orphan*/ ) ; 
 int stub1 (struct dmcu*) ; 
 int /*<<< orphan*/  stub2 (struct abm*,scalar_t__,scalar_t__,unsigned int,int) ; 

bool dc_link_set_backlight_level(const struct dc_link *link, uint32_t level,
		uint32_t frame_ramp, const struct dc_stream_state *stream)
{
	struct dc  *core_dc = link->ctx->dc;
	struct abm *abm = core_dc->res_pool->abm;
	struct dmcu *dmcu = core_dc->res_pool->dmcu;
	unsigned int controller_id = 0;
	bool use_smooth_brightness = true;
	int i;
	DC_LOGGER_INIT(link->ctx->logger);

	if ((dmcu == NULL) ||
		(abm == NULL) ||
		(abm->funcs->set_backlight_level == NULL))
		return false;

	if (stream) {
		if (stream->bl_pwm_level == EDP_BACKLIGHT_RAMP_DISABLE_LEVEL)
			frame_ramp = 0;

		((struct dc_stream_state *)stream)->bl_pwm_level = level;
	}

	use_smooth_brightness = dmcu->funcs->is_dmcu_initialized(dmcu);

	DC_LOG_BACKLIGHT("New Backlight level: %d (0x%X)\n", level, level);

	if (dc_is_embedded_signal(link->connector_signal)) {
		if (stream != NULL) {
			for (i = 0; i < MAX_PIPES; i++) {
				if (core_dc->current_state->res_ctx.
						pipe_ctx[i].stream
						== stream)
					/* DMCU -1 for all controller id values,
					 * therefore +1 here
					 */
					controller_id =
						core_dc->current_state->
						res_ctx.pipe_ctx[i].stream_res.tg->inst +
						1;
			}
		}
		abm->funcs->set_backlight_level(
				abm,
				level,
				frame_ramp,
				controller_id,
				use_smooth_brightness);
	}

	return true;
}