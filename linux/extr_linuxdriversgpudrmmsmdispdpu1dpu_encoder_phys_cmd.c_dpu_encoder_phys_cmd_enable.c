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
struct dpu_encoder_phys_cmd {int dummy; } ;
struct dpu_encoder_phys {scalar_t__ enable_state; TYPE_1__* hw_pp; } ;
struct TYPE_2__ {scalar_t__ idx; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPU_DEBUG_CMDENC (struct dpu_encoder_phys_cmd*,char*,scalar_t__) ; 
 scalar_t__ DPU_ENC_ENABLED ; 
 int /*<<< orphan*/  DPU_ERROR (char*) ; 
 scalar_t__ PINGPONG_0 ; 
 int /*<<< orphan*/  dpu_encoder_phys_cmd_enable_helper (struct dpu_encoder_phys*) ; 
 struct dpu_encoder_phys_cmd* to_dpu_encoder_phys_cmd (struct dpu_encoder_phys*) ; 

__attribute__((used)) static void dpu_encoder_phys_cmd_enable(struct dpu_encoder_phys *phys_enc)
{
	struct dpu_encoder_phys_cmd *cmd_enc =
		to_dpu_encoder_phys_cmd(phys_enc);

	if (!phys_enc || !phys_enc->hw_pp) {
		DPU_ERROR("invalid phys encoder\n");
		return;
	}

	DPU_DEBUG_CMDENC(cmd_enc, "pp %d\n", phys_enc->hw_pp->idx - PINGPONG_0);

	if (phys_enc->enable_state == DPU_ENC_ENABLED) {
		DPU_ERROR("already enabled\n");
		return;
	}

	dpu_encoder_phys_cmd_enable_helper(phys_enc);
	phys_enc->enable_state = DPU_ENC_ENABLED;
}