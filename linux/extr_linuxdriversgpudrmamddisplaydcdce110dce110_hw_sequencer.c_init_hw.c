#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_9__ ;
typedef  struct TYPE_23__   TYPE_8__ ;
typedef  struct TYPE_22__   TYPE_7__ ;
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;
typedef  struct TYPE_15__   TYPE_12__ ;
typedef  struct TYPE_14__   TYPE_11__ ;
typedef  struct TYPE_13__   TYPE_10__ ;

/* Type definitions */
struct transform {TYPE_1__* funcs; } ;
struct timing_generator {TYPE_5__* funcs; } ;
struct dc_link {TYPE_10__* link_enc; } ;
struct dc_bios {int dummy; } ;
struct TYPE_18__ {int /*<<< orphan*/  (* edp_power_control ) (struct dc_link*,int) ;int /*<<< orphan*/  (* enable_display_pipe_clock_gating ) (TYPE_11__*,int) ;int /*<<< orphan*/  (* enable_display_power_gating ) (struct dc*,int,struct dc_bios*,int /*<<< orphan*/ ) ;} ;
struct dc {int link_count; TYPE_12__* fbc_compressor; TYPE_7__* res_pool; TYPE_3__ hwss; struct dc_link** links; int /*<<< orphan*/  hwseq; TYPE_11__* ctx; } ;
struct audio {TYPE_6__* funcs; } ;
struct abm {TYPE_8__* funcs; } ;
struct TYPE_24__ {int /*<<< orphan*/  (* power_up_fbc ) (TYPE_12__*) ;} ;
struct TYPE_23__ {int /*<<< orphan*/  (* abm_init ) (struct abm*) ;int /*<<< orphan*/  (* init_backlight ) (struct abm*) ;} ;
struct TYPE_22__ {int pipe_count; int audio_count; struct abm* abm; struct audio** audios; struct timing_generator** timing_generators; struct transform** transforms; } ;
struct TYPE_21__ {int /*<<< orphan*/  (* hw_init ) (struct audio*) ;} ;
struct TYPE_20__ {int /*<<< orphan*/  (* set_blank ) (struct timing_generator*,int) ;int /*<<< orphan*/  (* disable_vga ) (struct timing_generator*) ;} ;
struct TYPE_19__ {int /*<<< orphan*/  (* hw_init ) (TYPE_10__*) ;} ;
struct TYPE_17__ {scalar_t__ id; } ;
struct TYPE_16__ {int /*<<< orphan*/  (* transform_reset ) (struct transform*) ;} ;
struct TYPE_15__ {TYPE_9__* funcs; } ;
struct TYPE_14__ {struct dc_bios* dc_bios; } ;
struct TYPE_13__ {TYPE_4__* funcs; TYPE_2__ connector; } ;

/* Variables and functions */
 scalar_t__ CONNECTOR_ID_EDP ; 
 int /*<<< orphan*/  PIPE_GATING_CONTROL_DISABLE ; 
 int /*<<< orphan*/  PIPE_GATING_CONTROL_INIT ; 
 int /*<<< orphan*/  dce_clock_gating_power_up (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  hwss_wait_for_blank_complete (struct timing_generator*) ; 
 int /*<<< orphan*/  stub1 (struct transform*) ; 
 int /*<<< orphan*/  stub10 (struct abm*) ; 
 int /*<<< orphan*/  stub11 (struct abm*) ; 
 int /*<<< orphan*/  stub12 (TYPE_12__*) ; 
 int /*<<< orphan*/  stub2 (struct dc*,int,struct dc_bios*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (struct dc*,int,struct dc_bios*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (TYPE_11__*,int) ; 
 int /*<<< orphan*/  stub5 (struct dc_link*,int) ; 
 int /*<<< orphan*/  stub6 (TYPE_10__*) ; 
 int /*<<< orphan*/  stub7 (struct timing_generator*) ; 
 int /*<<< orphan*/  stub8 (struct timing_generator*,int) ; 
 int /*<<< orphan*/  stub9 (struct audio*) ; 

__attribute__((used)) static void init_hw(struct dc *dc)
{
	int i;
	struct dc_bios *bp;
	struct transform *xfm;
	struct abm *abm;

	bp = dc->ctx->dc_bios;
	for (i = 0; i < dc->res_pool->pipe_count; i++) {
		xfm = dc->res_pool->transforms[i];
		xfm->funcs->transform_reset(xfm);

		dc->hwss.enable_display_power_gating(
				dc, i, bp,
				PIPE_GATING_CONTROL_INIT);
		dc->hwss.enable_display_power_gating(
				dc, i, bp,
				PIPE_GATING_CONTROL_DISABLE);
		dc->hwss.enable_display_pipe_clock_gating(
			dc->ctx,
			true);
	}

	dce_clock_gating_power_up(dc->hwseq, false);
	/***************************************/

	for (i = 0; i < dc->link_count; i++) {
		/****************************************/
		/* Power up AND update implementation according to the
		 * required signal (which may be different from the
		 * default signal on connector). */
		struct dc_link *link = dc->links[i];

		if (link->link_enc->connector.id == CONNECTOR_ID_EDP)
			dc->hwss.edp_power_control(link, true);

		link->link_enc->funcs->hw_init(link->link_enc);
	}

	for (i = 0; i < dc->res_pool->pipe_count; i++) {
		struct timing_generator *tg = dc->res_pool->timing_generators[i];

		tg->funcs->disable_vga(tg);

		/* Blank controller using driver code instead of
		 * command table. */
		tg->funcs->set_blank(tg, true);
		hwss_wait_for_blank_complete(tg);
	}

	for (i = 0; i < dc->res_pool->audio_count; i++) {
		struct audio *audio = dc->res_pool->audios[i];
		audio->funcs->hw_init(audio);
	}

	abm = dc->res_pool->abm;
	if (abm != NULL) {
		abm->funcs->init_backlight(abm);
		abm->funcs->abm_init(abm);
	}

	if (dc->fbc_compressor)
		dc->fbc_compressor->funcs->power_up_fbc(dc->fbc_compressor);

}