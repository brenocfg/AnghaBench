#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_46__   TYPE_9__ ;
typedef  struct TYPE_45__   TYPE_8__ ;
typedef  struct TYPE_44__   TYPE_7__ ;
typedef  struct TYPE_43__   TYPE_6__ ;
typedef  struct TYPE_42__   TYPE_5__ ;
typedef  struct TYPE_41__   TYPE_4__ ;
typedef  struct TYPE_40__   TYPE_3__ ;
typedef  struct TYPE_39__   TYPE_2__ ;
typedef  struct TYPE_38__   TYPE_24__ ;
typedef  struct TYPE_37__   TYPE_21__ ;
typedef  struct TYPE_36__   TYPE_20__ ;
typedef  struct TYPE_35__   TYPE_1__ ;
typedef  struct TYPE_34__   TYPE_19__ ;
typedef  struct TYPE_33__   TYPE_18__ ;
typedef  struct TYPE_32__   TYPE_17__ ;
typedef  struct TYPE_31__   TYPE_16__ ;
typedef  struct TYPE_30__   TYPE_15__ ;
typedef  struct TYPE_29__   TYPE_14__ ;
typedef  struct TYPE_28__   TYPE_13__ ;
typedef  struct TYPE_27__   TYPE_12__ ;
typedef  struct TYPE_26__   TYPE_11__ ;
typedef  struct TYPE_25__   TYPE_10__ ;

/* Type definitions */
struct TYPE_29__ {int /*<<< orphan*/  xtalin_clock_inKhz; int /*<<< orphan*/  dchub_ref_clock_inKhz; int /*<<< orphan*/  dccg_ref_clock_inKhz; } ;
struct resource_pool {int audio_count; struct audio** audios; TYPE_1__** dscs; TYPE_17__* res_cap; TYPE_14__ ref_clocks; TYPE_20__* hubbub; TYPE_21__* dccg; struct dmcu* dmcu; struct abm* abm; } ;
struct dmcu {TYPE_5__* funcs; } ;
struct dce_hwseq {int dummy; } ;
struct TYPE_31__ {int link_active; } ;
struct dc_link {TYPE_16__ link_status; TYPE_19__* link_enc; } ;
struct TYPE_25__ {int /*<<< orphan*/  crystal_frequency; } ;
struct TYPE_26__ {TYPE_10__ pll_info; } ;
struct dc_bios {TYPE_8__* funcs; TYPE_11__ fw_info; scalar_t__ fw_info_valid; } ;
struct TYPE_33__ {int /*<<< orphan*/  (* enable_power_gating_plane ) (struct dce_hwseq*,int) ;int /*<<< orphan*/  (* init_pipes ) (struct dc*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* dsc_pg_control ) (struct dce_hwseq*,int /*<<< orphan*/ ,int) ;int /*<<< orphan*/  (* bios_golden_init ) (struct dc*) ;int /*<<< orphan*/  (* disable_vga ) (struct dce_hwseq*) ;} ;
struct TYPE_44__ {int /*<<< orphan*/  disable_clock_gate; } ;
struct TYPE_39__ {scalar_t__ power_down_display_on_boot; } ;
struct dc {int link_count; struct dce_hwseq* hwseq; TYPE_18__ hwss; TYPE_7__ debug; int /*<<< orphan*/  current_state; TYPE_2__ config; struct dc_link** links; TYPE_12__* ctx; struct resource_pool* res_pool; TYPE_24__* clk_mgr; } ;
struct audio {TYPE_3__* funcs; } ;
struct abm {int /*<<< orphan*/  dmcu_is_running; TYPE_4__* funcs; } ;
struct TYPE_46__ {int /*<<< orphan*/  (* get_dccg_ref_freq ) (TYPE_21__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* dccg_init ) (TYPE_21__*) ;} ;
struct TYPE_45__ {scalar_t__ (* is_accelerated_mode ) (struct dc_bios*) ;} ;
struct TYPE_43__ {int /*<<< orphan*/  (* init_clocks ) (TYPE_24__*) ;} ;
struct TYPE_42__ {int /*<<< orphan*/  (* is_dmcu_initialized ) (struct dmcu*) ;int /*<<< orphan*/  (* dmcu_init ) (struct dmcu*) ;} ;
struct TYPE_41__ {int /*<<< orphan*/  (* abm_init ) (struct abm*) ;int /*<<< orphan*/  (* init_backlight ) (struct abm*) ;} ;
struct TYPE_40__ {int /*<<< orphan*/  (* hw_init ) (struct audio*) ;} ;
struct TYPE_38__ {TYPE_6__* funcs; } ;
struct TYPE_37__ {TYPE_9__* funcs; } ;
struct TYPE_36__ {TYPE_13__* funcs; } ;
struct TYPE_35__ {int /*<<< orphan*/  inst; } ;
struct TYPE_34__ {TYPE_15__* funcs; } ;
struct TYPE_32__ {int num_dsc; } ;
struct TYPE_30__ {scalar_t__ (* is_dig_enabled ) (TYPE_19__*) ;int /*<<< orphan*/  (* hw_init ) (TYPE_19__*) ;} ;
struct TYPE_28__ {int /*<<< orphan*/  (* get_dchub_ref_freq ) (TYPE_20__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;
struct TYPE_27__ {struct dc_bios* dc_bios; int /*<<< orphan*/  dce_environment; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_CRITICAL (int) ; 
 int /*<<< orphan*/  DCCG_GATE_DISABLE_CNTL ; 
 int /*<<< orphan*/  DCCG_GATE_DISABLE_CNTL2 ; 
 int /*<<< orphan*/  DCFCLK_CNTL ; 
 int /*<<< orphan*/  DCFCLK_GATE_DIS ; 
 int /*<<< orphan*/  DCHUBBUB_GLOBAL_TIMER_CNTL ; 
 int /*<<< orphan*/  DCHUBBUB_GLOBAL_TIMER_ENABLE ; 
 int /*<<< orphan*/  DIO_MEM_PWR_CTRL ; 
 scalar_t__ IS_FPGA_MAXIMUS_DC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REFCLK_CNTL ; 
 int /*<<< orphan*/  REG_UPDATE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  REG_WRITE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_24__*) ; 
 scalar_t__ stub10 (TYPE_19__*) ; 
 int /*<<< orphan*/  stub11 (struct dce_hwseq*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ stub12 (struct dc_bios*) ; 
 int /*<<< orphan*/  stub13 (struct dc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub14 (struct audio*) ; 
 int /*<<< orphan*/  stub15 (struct abm*) ; 
 int /*<<< orphan*/  stub16 (struct abm*) ; 
 int /*<<< orphan*/  stub17 (struct dmcu*) ; 
 int /*<<< orphan*/  stub18 (struct dmcu*) ; 
 int /*<<< orphan*/  stub19 (struct dce_hwseq*,int) ; 
 int /*<<< orphan*/  stub2 (TYPE_21__*) ; 
 int /*<<< orphan*/  stub3 (struct dce_hwseq*,int) ; 
 scalar_t__ stub4 (struct dc_bios*) ; 
 int /*<<< orphan*/  stub5 (struct dce_hwseq*) ; 
 int /*<<< orphan*/  stub6 (struct dc*) ; 
 int /*<<< orphan*/  stub7 (TYPE_21__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub8 (TYPE_20__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub9 (TYPE_19__*) ; 

__attribute__((used)) static void dcn10_init_hw(struct dc *dc)
{
	int i;
	struct abm *abm = dc->res_pool->abm;
	struct dmcu *dmcu = dc->res_pool->dmcu;
	struct dce_hwseq *hws = dc->hwseq;
	struct dc_bios *dcb = dc->ctx->dc_bios;
	struct resource_pool *res_pool = dc->res_pool;

	if (dc->clk_mgr && dc->clk_mgr->funcs->init_clocks)
		dc->clk_mgr->funcs->init_clocks(dc->clk_mgr);

	// Initialize the dccg
	if (dc->res_pool->dccg && dc->res_pool->dccg->funcs->dccg_init)
		dc->res_pool->dccg->funcs->dccg_init(res_pool->dccg);

	if (IS_FPGA_MAXIMUS_DC(dc->ctx->dce_environment)) {

		REG_WRITE(REFCLK_CNTL, 0);
		REG_UPDATE(DCHUBBUB_GLOBAL_TIMER_CNTL, DCHUBBUB_GLOBAL_TIMER_ENABLE, 1);
		REG_WRITE(DIO_MEM_PWR_CTRL, 0);

		if (!dc->debug.disable_clock_gate) {
			/* enable all DCN clock gating */
			REG_WRITE(DCCG_GATE_DISABLE_CNTL, 0);

			REG_WRITE(DCCG_GATE_DISABLE_CNTL2, 0);

			REG_UPDATE(DCFCLK_CNTL, DCFCLK_GATE_DIS, 0);
		}

		//Enable ability to power gate / don't force power on permanently
		dc->hwss.enable_power_gating_plane(hws, true);

		return;
	}

	if (!dcb->funcs->is_accelerated_mode(dcb))
		dc->hwss.disable_vga(dc->hwseq);

	dc->hwss.bios_golden_init(dc);
	if (dc->ctx->dc_bios->fw_info_valid) {
		res_pool->ref_clocks.xtalin_clock_inKhz =
				dc->ctx->dc_bios->fw_info.pll_info.crystal_frequency;

		if (!IS_FPGA_MAXIMUS_DC(dc->ctx->dce_environment)) {
			if (res_pool->dccg && res_pool->hubbub) {

				(res_pool->dccg->funcs->get_dccg_ref_freq)(res_pool->dccg,
						dc->ctx->dc_bios->fw_info.pll_info.crystal_frequency,
						&res_pool->ref_clocks.dccg_ref_clock_inKhz);

				(res_pool->hubbub->funcs->get_dchub_ref_freq)(res_pool->hubbub,
						res_pool->ref_clocks.dccg_ref_clock_inKhz,
						&res_pool->ref_clocks.dchub_ref_clock_inKhz);
			} else {
				// Not all ASICs have DCCG sw component
				res_pool->ref_clocks.dccg_ref_clock_inKhz =
						res_pool->ref_clocks.xtalin_clock_inKhz;
				res_pool->ref_clocks.dchub_ref_clock_inKhz =
						res_pool->ref_clocks.xtalin_clock_inKhz;
			}
		}
	} else
		ASSERT_CRITICAL(false);

	for (i = 0; i < dc->link_count; i++) {
		/* Power up AND update implementation according to the
		 * required signal (which may be different from the
		 * default signal on connector).
		 */
		struct dc_link *link = dc->links[i];

		link->link_enc->funcs->hw_init(link->link_enc);

		/* Check for enabled DIG to identify enabled display */
		if (link->link_enc->funcs->is_dig_enabled &&
			link->link_enc->funcs->is_dig_enabled(link->link_enc))
			link->link_status.link_active = true;
	}

	/* Power gate DSCs */
#ifdef CONFIG_DRM_AMD_DC_DSC_SUPPORT
	for (i = 0; i < res_pool->res_cap->num_dsc; i++)
		if (dc->hwss.dsc_pg_control != NULL)
			dc->hwss.dsc_pg_control(hws, res_pool->dscs[i]->inst, false);
#endif

	/* If taking control over from VBIOS, we may want to optimize our first
	 * mode set, so we need to skip powering down pipes until we know which
	 * pipes we want to use.
	 * Otherwise, if taking control is not possible, we need to power
	 * everything down.
	 */
	if (dcb->funcs->is_accelerated_mode(dcb) || dc->config.power_down_display_on_boot) {
		dc->hwss.init_pipes(dc, dc->current_state);
	}

	for (i = 0; i < res_pool->audio_count; i++) {
		struct audio *audio = res_pool->audios[i];

		audio->funcs->hw_init(audio);
	}

	if (abm != NULL) {
		abm->funcs->init_backlight(abm);
		abm->funcs->abm_init(abm);
	}

	if (dmcu != NULL)
		dmcu->funcs->dmcu_init(dmcu);

	if (abm != NULL && dmcu != NULL)
		abm->dmcu_is_running = dmcu->funcs->is_dmcu_initialized(dmcu);

	/* power AFMT HDMI memory TODO: may move to dis/en output save power*/
	REG_WRITE(DIO_MEM_PWR_CTRL, 0);

	if (!dc->debug.disable_clock_gate) {
		/* enable all DCN clock gating */
		REG_WRITE(DCCG_GATE_DISABLE_CNTL, 0);

		REG_WRITE(DCCG_GATE_DISABLE_CNTL2, 0);

		REG_UPDATE(DCFCLK_CNTL, DCFCLK_GATE_DIS, 0);
	}

	dc->hwss.enable_power_gating_plane(dc->hwseq, true);
}