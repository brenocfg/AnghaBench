#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct msm_drm_private {int /*<<< orphan*/  kms; } ;
struct drm_encoder {TYPE_1__* dev; } ;
struct dpu_kms {int /*<<< orphan*/  catalog; } ;
struct TYPE_11__ {scalar_t__ intf_type; } ;
struct dpu_encoder_virt {TYPE_6__ disp_info; TYPE_3__* cur_master; } ;
struct TYPE_8__ {int /*<<< orphan*/  (* reset_ubwc ) (TYPE_4__*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* intf_audio_select ) (TYPE_4__*) ;} ;
struct TYPE_10__ {TYPE_2__ ops; } ;
struct TYPE_9__ {TYPE_4__* hw_mdptop; } ;
struct TYPE_7__ {struct msm_drm_private* dev_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPU_ERROR (char*) ; 
 scalar_t__ DRM_MODE_CONNECTOR_DisplayPort ; 
 int /*<<< orphan*/  _dpu_encoder_update_vsync_source (struct dpu_encoder_virt*,TYPE_6__*) ; 
 int /*<<< orphan*/  stub1 (TYPE_4__*) ; 
 int /*<<< orphan*/  stub2 (TYPE_4__*,int /*<<< orphan*/ ) ; 
 struct dpu_encoder_virt* to_dpu_encoder_virt (struct drm_encoder*) ; 
 struct dpu_kms* to_dpu_kms (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void _dpu_encoder_virt_enable_helper(struct drm_encoder *drm_enc)
{
	struct dpu_encoder_virt *dpu_enc = NULL;
	struct msm_drm_private *priv;
	struct dpu_kms *dpu_kms;

	if (!drm_enc || !drm_enc->dev || !drm_enc->dev->dev_private) {
		DPU_ERROR("invalid parameters\n");
		return;
	}

	priv = drm_enc->dev->dev_private;
	dpu_kms = to_dpu_kms(priv->kms);
	if (!dpu_kms) {
		DPU_ERROR("invalid dpu_kms\n");
		return;
	}

	dpu_enc = to_dpu_encoder_virt(drm_enc);
	if (!dpu_enc || !dpu_enc->cur_master) {
		DPU_ERROR("invalid dpu encoder/master\n");
		return;
	}

	if (dpu_enc->disp_info.intf_type == DRM_MODE_CONNECTOR_DisplayPort &&
	    dpu_enc->cur_master->hw_mdptop &&
	    dpu_enc->cur_master->hw_mdptop->ops.intf_audio_select)
		dpu_enc->cur_master->hw_mdptop->ops.intf_audio_select(
					dpu_enc->cur_master->hw_mdptop);

	if (dpu_enc->cur_master->hw_mdptop &&
			dpu_enc->cur_master->hw_mdptop->ops.reset_ubwc)
		dpu_enc->cur_master->hw_mdptop->ops.reset_ubwc(
				dpu_enc->cur_master->hw_mdptop,
				dpu_kms->catalog);

	_dpu_encoder_update_vsync_source(dpu_enc, &dpu_enc->disp_info);
}