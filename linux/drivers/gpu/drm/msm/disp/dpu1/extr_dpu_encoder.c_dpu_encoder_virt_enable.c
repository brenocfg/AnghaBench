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
struct drm_encoder {int dummy; } ;
struct drm_display_mode {int /*<<< orphan*/  vdisplay; int /*<<< orphan*/  hdisplay; } ;
struct TYPE_10__ {TYPE_2__* crtc; } ;
struct dpu_encoder_virt {int enabled; int /*<<< orphan*/  enc_lock; TYPE_6__* cur_master; TYPE_7__* cur_slave; TYPE_3__ base; } ;
struct TYPE_11__ {int /*<<< orphan*/  (* enable ) (TYPE_7__*) ;} ;
struct TYPE_14__ {TYPE_4__ ops; } ;
struct TYPE_12__ {int /*<<< orphan*/  (* enable ) (TYPE_6__*) ;} ;
struct TYPE_13__ {TYPE_5__ ops; } ;
struct TYPE_9__ {TYPE_1__* state; } ;
struct TYPE_8__ {struct drm_display_mode adjusted_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPU_ENC_RC_EVENT_KICKOFF ; 
 int /*<<< orphan*/  DPU_ERROR (char*) ; 
 int /*<<< orphan*/  DPU_ERROR_ENC (struct dpu_encoder_virt*,char*,int) ; 
 int /*<<< orphan*/  DRMID (struct drm_encoder*) ; 
 int /*<<< orphan*/  _dpu_encoder_virt_enable_helper (struct drm_encoder*) ; 
 int dpu_encoder_resource_control (struct drm_encoder*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (TYPE_7__*) ; 
 int /*<<< orphan*/  stub2 (TYPE_6__*) ; 
 struct dpu_encoder_virt* to_dpu_encoder_virt (struct drm_encoder*) ; 
 int /*<<< orphan*/  trace_dpu_enc_enable (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dpu_encoder_virt_enable(struct drm_encoder *drm_enc)
{
	struct dpu_encoder_virt *dpu_enc = NULL;
	int ret = 0;
	struct drm_display_mode *cur_mode = NULL;

	if (!drm_enc) {
		DPU_ERROR("invalid encoder\n");
		return;
	}
	dpu_enc = to_dpu_encoder_virt(drm_enc);

	mutex_lock(&dpu_enc->enc_lock);
	cur_mode = &dpu_enc->base.crtc->state->adjusted_mode;

	trace_dpu_enc_enable(DRMID(drm_enc), cur_mode->hdisplay,
			     cur_mode->vdisplay);

	/* always enable slave encoder before master */
	if (dpu_enc->cur_slave && dpu_enc->cur_slave->ops.enable)
		dpu_enc->cur_slave->ops.enable(dpu_enc->cur_slave);

	if (dpu_enc->cur_master && dpu_enc->cur_master->ops.enable)
		dpu_enc->cur_master->ops.enable(dpu_enc->cur_master);

	ret = dpu_encoder_resource_control(drm_enc, DPU_ENC_RC_EVENT_KICKOFF);
	if (ret) {
		DPU_ERROR_ENC(dpu_enc, "dpu resource control failed: %d\n",
				ret);
		goto out;
	}

	_dpu_encoder_virt_enable_helper(drm_enc);

	dpu_enc->enabled = true;

out:
	mutex_unlock(&dpu_enc->enc_lock);
}