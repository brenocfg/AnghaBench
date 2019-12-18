#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_9__ ;
typedef  struct TYPE_19__   TYPE_8__ ;
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;
typedef  struct TYPE_11__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct dmcu {TYPE_3__* funcs; } ;
struct dc_link {int /*<<< orphan*/  connector_signal; TYPE_2__* ctx; } ;
struct dc {TYPE_9__* current_state; TYPE_1__* res_pool; } ;
struct abm {TYPE_10__* funcs; } ;
struct TYPE_19__ {TYPE_7__* pipe_ctx; } ;
struct TYPE_20__ {TYPE_8__ res_ctx; } ;
struct TYPE_17__ {TYPE_5__* tg; } ;
struct TYPE_18__ {int /*<<< orphan*/ * plane_state; TYPE_6__ stream_res; TYPE_4__* stream; } ;
struct TYPE_16__ {int inst; } ;
struct TYPE_15__ {struct dc_link const* link; } ;
struct TYPE_14__ {int (* is_dmcu_initialized ) (struct dmcu*) ;} ;
struct TYPE_13__ {int /*<<< orphan*/  logger; struct dc* dc; } ;
struct TYPE_12__ {struct dmcu* dmcu; struct abm* abm; } ;
struct TYPE_11__ {int /*<<< orphan*/  (* set_backlight_level_pwm ) (struct abm*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DC_LOGGER_INIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DC_LOG_BACKLIGHT (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int MAX_PIPES ; 
 scalar_t__ dc_is_embedded_signal (int /*<<< orphan*/ ) ; 
 int stub1 (struct dmcu*) ; 
 int /*<<< orphan*/  stub2 (struct abm*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int) ; 

bool dc_link_set_backlight_level(const struct dc_link *link,
		uint32_t backlight_pwm_u16_16,
		uint32_t frame_ramp)
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
		(abm->funcs->set_backlight_level_pwm == NULL))
		return false;

	use_smooth_brightness = dmcu->funcs->is_dmcu_initialized(dmcu);

	DC_LOG_BACKLIGHT("New Backlight level: %d (0x%X)\n",
			backlight_pwm_u16_16, backlight_pwm_u16_16);

	if (dc_is_embedded_signal(link->connector_signal)) {
		for (i = 0; i < MAX_PIPES; i++) {
			if (core_dc->current_state->res_ctx.pipe_ctx[i].stream) {
				if (core_dc->current_state->res_ctx.
						pipe_ctx[i].stream->link
						== link) {
					/* DMCU -1 for all controller id values,
					 * therefore +1 here
					 */
					controller_id =
						core_dc->current_state->
						res_ctx.pipe_ctx[i].stream_res.tg->inst +
						1;

					/* Disable brightness ramping when the display is blanked
					 * as it can hang the DMCU
					 */
					if (core_dc->current_state->res_ctx.pipe_ctx[i].plane_state == NULL)
						frame_ramp = 0;
				}
			}
		}
		abm->funcs->set_backlight_level_pwm(
				abm,
				backlight_pwm_u16_16,
				frame_ramp,
				controller_id,
				use_smooth_brightness);
	}

	return true;
}