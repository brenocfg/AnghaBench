#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct dpu_encoder_wait_info {int /*<<< orphan*/  timeout_ms; int /*<<< orphan*/ * atomic_cnt; int /*<<< orphan*/ * wq; } ;
struct dpu_encoder_phys_cmd {int dummy; } ;
struct dpu_encoder_phys {int /*<<< orphan*/  pending_ctlstart_cnt; int /*<<< orphan*/  pending_kickoff_wq; int /*<<< orphan*/  hw_ctl; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPU_ERROR (char*) ; 
 int /*<<< orphan*/  DPU_ERROR_CMDENC (struct dpu_encoder_phys_cmd*,char*) ; 
 int EINVAL ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  INTR_IDX_CTL_START ; 
 int /*<<< orphan*/  KICKOFF_TIMEOUT_MS ; 
 int dpu_encoder_helper_wait_for_irq (struct dpu_encoder_phys*,int /*<<< orphan*/ ,struct dpu_encoder_wait_info*) ; 
 struct dpu_encoder_phys_cmd* to_dpu_encoder_phys_cmd (struct dpu_encoder_phys*) ; 

__attribute__((used)) static int _dpu_encoder_phys_cmd_wait_for_ctl_start(
		struct dpu_encoder_phys *phys_enc)
{
	struct dpu_encoder_phys_cmd *cmd_enc =
			to_dpu_encoder_phys_cmd(phys_enc);
	struct dpu_encoder_wait_info wait_info;
	int ret;

	if (!phys_enc || !phys_enc->hw_ctl) {
		DPU_ERROR("invalid argument(s)\n");
		return -EINVAL;
	}

	wait_info.wq = &phys_enc->pending_kickoff_wq;
	wait_info.atomic_cnt = &phys_enc->pending_ctlstart_cnt;
	wait_info.timeout_ms = KICKOFF_TIMEOUT_MS;

	ret = dpu_encoder_helper_wait_for_irq(phys_enc, INTR_IDX_CTL_START,
			&wait_info);
	if (ret == -ETIMEDOUT) {
		DPU_ERROR_CMDENC(cmd_enc, "ctl start interrupt wait failed\n");
		ret = -EINVAL;
	} else if (!ret)
		ret = 0;

	return ret;
}