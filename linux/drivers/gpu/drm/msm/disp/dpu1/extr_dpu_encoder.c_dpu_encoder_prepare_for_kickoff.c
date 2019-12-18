#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct drm_encoder {int dummy; } ;
struct dpu_encoder_virt {unsigned int num_phys_encs; struct dpu_encoder_phys** phys_encs; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* prepare_for_kickoff ) (struct dpu_encoder_phys*) ;} ;
struct dpu_encoder_phys {scalar_t__ enable_state; TYPE_1__ ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPU_ATRACE_BEGIN (char*) ; 
 int /*<<< orphan*/  DPU_ATRACE_END (char*) ; 
 scalar_t__ DPU_ENC_ERR_NEEDS_HW_RESET ; 
 int /*<<< orphan*/  DPU_ENC_RC_EVENT_KICKOFF ; 
 int /*<<< orphan*/  DRMID (struct drm_encoder*) ; 
 int /*<<< orphan*/  dpu_encoder_helper_hw_reset (struct dpu_encoder_phys*) ; 
 int /*<<< orphan*/  dpu_encoder_resource_control (struct drm_encoder*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct dpu_encoder_phys*) ; 
 struct dpu_encoder_virt* to_dpu_encoder_virt (struct drm_encoder*) ; 
 int /*<<< orphan*/  trace_dpu_enc_prepare_kickoff (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_dpu_enc_prepare_kickoff_reset (int /*<<< orphan*/ ) ; 

void dpu_encoder_prepare_for_kickoff(struct drm_encoder *drm_enc)
{
	struct dpu_encoder_virt *dpu_enc;
	struct dpu_encoder_phys *phys;
	bool needs_hw_reset = false;
	unsigned int i;

	dpu_enc = to_dpu_encoder_virt(drm_enc);

	trace_dpu_enc_prepare_kickoff(DRMID(drm_enc));

	/* prepare for next kickoff, may include waiting on previous kickoff */
	DPU_ATRACE_BEGIN("enc_prepare_for_kickoff");
	for (i = 0; i < dpu_enc->num_phys_encs; i++) {
		phys = dpu_enc->phys_encs[i];
		if (phys) {
			if (phys->ops.prepare_for_kickoff)
				phys->ops.prepare_for_kickoff(phys);
			if (phys->enable_state == DPU_ENC_ERR_NEEDS_HW_RESET)
				needs_hw_reset = true;
		}
	}
	DPU_ATRACE_END("enc_prepare_for_kickoff");

	dpu_encoder_resource_control(drm_enc, DPU_ENC_RC_EVENT_KICKOFF);

	/* if any phys needs reset, reset all phys, in-order */
	if (needs_hw_reset) {
		trace_dpu_enc_prepare_kickoff_reset(DRMID(drm_enc));
		for (i = 0; i < dpu_enc->num_phys_encs; i++) {
			dpu_encoder_helper_hw_reset(dpu_enc->phys_encs[i]);
		}
	}
}