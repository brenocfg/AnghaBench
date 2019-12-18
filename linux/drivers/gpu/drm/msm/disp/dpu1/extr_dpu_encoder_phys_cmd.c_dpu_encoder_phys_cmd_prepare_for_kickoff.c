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
struct dpu_encoder_phys {int /*<<< orphan*/  pending_kickoff_cnt; TYPE_1__* hw_pp; int /*<<< orphan*/  parent; } ;
struct TYPE_2__ {scalar_t__ idx; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPU_DEBUG_CMDENC (struct dpu_encoder_phys_cmd*,char*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DPU_ERROR (char*) ; 
 int /*<<< orphan*/  DRMID (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DRM_ERROR (char*,int /*<<< orphan*/ ,int,scalar_t__) ; 
 scalar_t__ PINGPONG_0 ; 
 int _dpu_encoder_phys_cmd_wait_for_idle (struct dpu_encoder_phys*) ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct dpu_encoder_phys_cmd* to_dpu_encoder_phys_cmd (struct dpu_encoder_phys*) ; 

__attribute__((used)) static void dpu_encoder_phys_cmd_prepare_for_kickoff(
		struct dpu_encoder_phys *phys_enc)
{
	struct dpu_encoder_phys_cmd *cmd_enc =
			to_dpu_encoder_phys_cmd(phys_enc);
	int ret;

	if (!phys_enc || !phys_enc->hw_pp) {
		DPU_ERROR("invalid encoder\n");
		return;
	}
	DRM_DEBUG_KMS("id:%u pp:%d pending_cnt:%d\n", DRMID(phys_enc->parent),
		      phys_enc->hw_pp->idx - PINGPONG_0,
		      atomic_read(&phys_enc->pending_kickoff_cnt));

	/*
	 * Mark kickoff request as outstanding. If there are more than one,
	 * outstanding, then we have to wait for the previous one to complete
	 */
	ret = _dpu_encoder_phys_cmd_wait_for_idle(phys_enc);
	if (ret) {
		/* force pending_kickoff_cnt 0 to discard failed kickoff */
		atomic_set(&phys_enc->pending_kickoff_cnt, 0);
		DRM_ERROR("failed wait_for_idle: id:%u ret:%d pp:%d\n",
			  DRMID(phys_enc->parent), ret,
			  phys_enc->hw_pp->idx - PINGPONG_0);
	}

	DPU_DEBUG_CMDENC(cmd_enc, "pp:%d pending_cnt %d\n",
			phys_enc->hw_pp->idx - PINGPONG_0,
			atomic_read(&phys_enc->pending_kickoff_cnt));
}