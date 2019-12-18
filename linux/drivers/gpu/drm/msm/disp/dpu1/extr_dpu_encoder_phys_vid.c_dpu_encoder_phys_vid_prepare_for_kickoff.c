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
struct TYPE_2__ {int (* wait_reset_status ) (struct dpu_hw_ctl*) ;} ;
struct dpu_hw_ctl {int /*<<< orphan*/  idx; TYPE_1__ ops; } ;
struct dpu_encoder_phys {struct dpu_hw_ctl* hw_ctl; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPU_ERROR (char*) ; 
 int /*<<< orphan*/  DPU_ERROR_VIDENC (struct dpu_encoder_phys*,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  INTR_IDX_VSYNC ; 
 int /*<<< orphan*/  dpu_encoder_helper_unregister_irq (struct dpu_encoder_phys*,int /*<<< orphan*/ ) ; 
 int stub1 (struct dpu_hw_ctl*) ; 

__attribute__((used)) static void dpu_encoder_phys_vid_prepare_for_kickoff(
		struct dpu_encoder_phys *phys_enc)
{
	struct dpu_hw_ctl *ctl;
	int rc;

	if (!phys_enc) {
		DPU_ERROR("invalid encoder/parameters\n");
		return;
	}

	ctl = phys_enc->hw_ctl;
	if (!ctl || !ctl->ops.wait_reset_status)
		return;

	/*
	 * hw supports hardware initiated ctl reset, so before we kickoff a new
	 * frame, need to check and wait for hw initiated ctl reset completion
	 */
	rc = ctl->ops.wait_reset_status(ctl);
	if (rc) {
		DPU_ERROR_VIDENC(phys_enc, "ctl %d reset failure: %d\n",
				ctl->idx, rc);
		dpu_encoder_helper_unregister_irq(phys_enc, INTR_IDX_VSYNC);
	}
}