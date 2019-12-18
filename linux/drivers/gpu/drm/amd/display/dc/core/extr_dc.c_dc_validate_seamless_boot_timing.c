#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct timing_generator {TYPE_3__* funcs; } ;
struct dc_sink {struct dc_link* link; } ;
struct dc_link {int /*<<< orphan*/  connector_signal; TYPE_8__* link_enc; } ;
struct dc_crtc_timing {unsigned int pix_clk_100hz; } ;
struct dc {TYPE_5__* res_pool; } ;
struct TYPE_17__ {TYPE_1__* funcs; } ;
struct TYPE_16__ {TYPE_2__* funcs; } ;
struct TYPE_15__ {TYPE_4__* funcs; } ;
struct TYPE_14__ {unsigned int pipe_count; unsigned int stream_enc_count; unsigned int timing_generator_count; TYPE_6__* dp_clock_source; struct timing_generator** timing_generators; TYPE_7__** stream_enc; } ;
struct TYPE_13__ {int /*<<< orphan*/  (* get_pixel_clk_frequency_100hz ) (TYPE_6__*,unsigned int,unsigned int*) ;} ;
struct TYPE_12__ {int /*<<< orphan*/  (* is_matching_timing ) (struct timing_generator*,struct dc_crtc_timing*) ;} ;
struct TYPE_11__ {unsigned int (* dig_source_otg ) (TYPE_7__*) ;} ;
struct TYPE_10__ {unsigned int (* get_dig_frontend ) (TYPE_8__*) ;int /*<<< orphan*/  (* is_dig_enabled ) (TYPE_8__*) ;} ;

/* Variables and functions */
 scalar_t__ dc_is_dp_signal (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_8__*) ; 
 unsigned int stub2 (TYPE_8__*) ; 
 unsigned int stub3 (TYPE_7__*) ; 
 int /*<<< orphan*/  stub4 (struct timing_generator*,struct dc_crtc_timing*) ; 
 int /*<<< orphan*/  stub5 (TYPE_6__*,unsigned int,unsigned int*) ; 

bool dc_validate_seamless_boot_timing(const struct dc *dc,
				const struct dc_sink *sink,
				struct dc_crtc_timing *crtc_timing)
{
	struct timing_generator *tg;
	struct dc_link *link = sink->link;
	unsigned int enc_inst, tg_inst;

	/* Check for enabled DIG to identify enabled display */
	if (!link->link_enc->funcs->is_dig_enabled(link->link_enc))
		return false;

	/* Check for which front end is used by this encoder.
	 * Note the inst is 1 indexed, where 0 is undefined.
	 * Note that DIG_FE can source from different OTG but our
	 * current implementation always map 1-to-1, so this code makes
	 * the same assumption and doesn't check OTG source.
	 */
	enc_inst = link->link_enc->funcs->get_dig_frontend(link->link_enc);

	/* Instance should be within the range of the pool */
	if (enc_inst >= dc->res_pool->pipe_count)
		return false;

	if (enc_inst >= dc->res_pool->stream_enc_count)
		return false;

	tg_inst = dc->res_pool->stream_enc[enc_inst]->funcs->dig_source_otg(
		dc->res_pool->stream_enc[enc_inst]);

	if (tg_inst >= dc->res_pool->timing_generator_count)
		return false;

	tg = dc->res_pool->timing_generators[tg_inst];

	if (!tg->funcs->is_matching_timing)
		return false;

	if (!tg->funcs->is_matching_timing(tg, crtc_timing))
		return false;

	if (dc_is_dp_signal(link->connector_signal)) {
		unsigned int pix_clk_100hz;

		dc->res_pool->dp_clock_source->funcs->get_pixel_clk_frequency_100hz(
			dc->res_pool->dp_clock_source,
			tg_inst, &pix_clk_100hz);

		if (crtc_timing->pix_clk_100hz != pix_clk_100hz)
			return false;

	}

	return true;
}