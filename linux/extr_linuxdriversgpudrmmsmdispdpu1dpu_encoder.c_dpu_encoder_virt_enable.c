#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct drm_encoder {int dummy; } ;
struct drm_display_mode {int /*<<< orphan*/  vdisplay; int /*<<< orphan*/  hdisplay; } ;
struct TYPE_9__ {int capabilities; } ;
struct TYPE_8__ {TYPE_2__* crtc; } ;
struct dpu_encoder_virt {int num_phys_encs; struct dpu_encoder_phys* cur_master; int /*<<< orphan*/  misr_frame_count; TYPE_4__ disp_info; scalar_t__ misr_enable; struct dpu_encoder_phys** phys_encs; TYPE_3__ base; } ;
struct TYPE_10__ {int /*<<< orphan*/  (* enable ) (struct dpu_encoder_phys*) ;int /*<<< orphan*/  (* setup_misr ) (struct dpu_encoder_phys*,int,int /*<<< orphan*/ ) ;scalar_t__ (* is_master ) (struct dpu_encoder_phys*) ;} ;
struct dpu_encoder_phys {TYPE_5__ ops; } ;
struct TYPE_7__ {TYPE_1__* state; } ;
struct TYPE_6__ {struct drm_display_mode adjusted_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPU_DEBUG_ENC (struct dpu_encoder_virt*,char*,int) ; 
 int /*<<< orphan*/  DPU_ENC_RC_EVENT_KICKOFF ; 
 int /*<<< orphan*/  DPU_ERROR (char*,...) ; 
 int /*<<< orphan*/  DPU_ERROR_ENC (struct dpu_encoder_virt*,char*,int) ; 
 int /*<<< orphan*/  DRMID (struct drm_encoder*) ; 
 int MSM_DISPLAY_CAP_VID_MODE ; 
 int /*<<< orphan*/  _dpu_encoder_virt_enable_helper (struct drm_encoder*) ; 
 int dpu_encoder_resource_control (struct drm_encoder*,int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 (struct dpu_encoder_phys*) ; 
 int /*<<< orphan*/  stub2 (struct dpu_encoder_phys*) ; 
 int /*<<< orphan*/  stub3 (struct dpu_encoder_phys*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (struct dpu_encoder_phys*) ; 
 struct dpu_encoder_virt* to_dpu_encoder_virt (struct drm_encoder*) ; 
 int /*<<< orphan*/  trace_dpu_enc_enable (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dpu_encoder_virt_enable(struct drm_encoder *drm_enc)
{
	struct dpu_encoder_virt *dpu_enc = NULL;
	int i, ret = 0;
	struct drm_display_mode *cur_mode = NULL;

	if (!drm_enc) {
		DPU_ERROR("invalid encoder\n");
		return;
	}
	dpu_enc = to_dpu_encoder_virt(drm_enc);
	cur_mode = &dpu_enc->base.crtc->state->adjusted_mode;

	trace_dpu_enc_enable(DRMID(drm_enc), cur_mode->hdisplay,
			     cur_mode->vdisplay);

	dpu_enc->cur_master = NULL;
	for (i = 0; i < dpu_enc->num_phys_encs; i++) {
		struct dpu_encoder_phys *phys = dpu_enc->phys_encs[i];

		if (phys && phys->ops.is_master && phys->ops.is_master(phys)) {
			DPU_DEBUG_ENC(dpu_enc, "master is now idx %d\n", i);
			dpu_enc->cur_master = phys;
			break;
		}
	}

	if (!dpu_enc->cur_master) {
		DPU_ERROR("virt encoder has no master! num_phys %d\n", i);
		return;
	}

	ret = dpu_encoder_resource_control(drm_enc, DPU_ENC_RC_EVENT_KICKOFF);
	if (ret) {
		DPU_ERROR_ENC(dpu_enc, "dpu resource control failed: %d\n",
				ret);
		return;
	}

	for (i = 0; i < dpu_enc->num_phys_encs; i++) {
		struct dpu_encoder_phys *phys = dpu_enc->phys_encs[i];

		if (!phys)
			continue;

		if (phys != dpu_enc->cur_master) {
			if (phys->ops.enable)
				phys->ops.enable(phys);
		}

		if (dpu_enc->misr_enable && (dpu_enc->disp_info.capabilities &
		     MSM_DISPLAY_CAP_VID_MODE) && phys->ops.setup_misr)
			phys->ops.setup_misr(phys, true,
						dpu_enc->misr_frame_count);
	}

	if (dpu_enc->cur_master->ops.enable)
		dpu_enc->cur_master->ops.enable(dpu_enc->cur_master);

	_dpu_encoder_virt_enable_helper(drm_enc);
}