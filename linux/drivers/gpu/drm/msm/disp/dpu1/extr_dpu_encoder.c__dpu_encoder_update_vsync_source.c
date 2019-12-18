#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct msm_drm_private {int /*<<< orphan*/  kms; } ;
struct msm_display_info {int capabilities; scalar_t__ is_te_using_watchdog_timer; } ;
struct drm_encoder {TYPE_1__* dev; } ;
struct dpu_vsync_source_cfg {int pp_count; int /*<<< orphan*/  vsync_source; int /*<<< orphan*/ * ppnumber; int /*<<< orphan*/  member_0; } ;
struct dpu_kms {struct dpu_hw_mdp* hw_mdp; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* setup_vsync_source ) (struct dpu_hw_mdp*,struct dpu_vsync_source_cfg*) ;} ;
struct dpu_hw_mdp {TYPE_2__ ops; } ;
struct dpu_encoder_virt {int num_phys_encs; TYPE_3__** hw_pp; struct drm_encoder base; } ;
struct TYPE_6__ {int /*<<< orphan*/  idx; } ;
struct TYPE_4__ {struct msm_drm_private* dev_private; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_3__**) ; 
 int /*<<< orphan*/  DPU_ERROR (char*,...) ; 
 int /*<<< orphan*/  DPU_VSYNC0_SOURCE_GPIO ; 
 int /*<<< orphan*/  DPU_VSYNC_SOURCE_WD_TIMER_0 ; 
 int MSM_DISPLAY_CAP_CMD_MODE ; 
 int /*<<< orphan*/  stub1 (struct dpu_hw_mdp*,struct dpu_vsync_source_cfg*) ; 
 struct dpu_kms* to_dpu_kms (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void _dpu_encoder_update_vsync_source(struct dpu_encoder_virt *dpu_enc,
			struct msm_display_info *disp_info)
{
	struct dpu_vsync_source_cfg vsync_cfg = { 0 };
	struct msm_drm_private *priv;
	struct dpu_kms *dpu_kms;
	struct dpu_hw_mdp *hw_mdptop;
	struct drm_encoder *drm_enc;
	int i;

	if (!dpu_enc || !disp_info) {
		DPU_ERROR("invalid param dpu_enc:%d or disp_info:%d\n",
					dpu_enc != NULL, disp_info != NULL);
		return;
	} else if (dpu_enc->num_phys_encs > ARRAY_SIZE(dpu_enc->hw_pp)) {
		DPU_ERROR("invalid num phys enc %d/%d\n",
				dpu_enc->num_phys_encs,
				(int) ARRAY_SIZE(dpu_enc->hw_pp));
		return;
	}

	drm_enc = &dpu_enc->base;
	/* this pointers are checked in virt_enable_helper */
	priv = drm_enc->dev->dev_private;

	dpu_kms = to_dpu_kms(priv->kms);
	if (!dpu_kms) {
		DPU_ERROR("invalid dpu_kms\n");
		return;
	}

	hw_mdptop = dpu_kms->hw_mdp;
	if (!hw_mdptop) {
		DPU_ERROR("invalid mdptop\n");
		return;
	}

	if (hw_mdptop->ops.setup_vsync_source &&
			disp_info->capabilities & MSM_DISPLAY_CAP_CMD_MODE) {
		for (i = 0; i < dpu_enc->num_phys_encs; i++)
			vsync_cfg.ppnumber[i] = dpu_enc->hw_pp[i]->idx;

		vsync_cfg.pp_count = dpu_enc->num_phys_encs;
		if (disp_info->is_te_using_watchdog_timer)
			vsync_cfg.vsync_source = DPU_VSYNC_SOURCE_WD_TIMER_0;
		else
			vsync_cfg.vsync_source = DPU_VSYNC0_SOURCE_GPIO;

		hw_mdptop->ops.setup_vsync_source(hw_mdptop, &vsync_cfg);
	}
}