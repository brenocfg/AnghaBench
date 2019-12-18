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
struct dpu_encoder_phys_cmd {int /*<<< orphan*/  pending_vblank_cnt; int /*<<< orphan*/  pending_vblank_wq; } ;
struct dpu_encoder_phys {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  INTR_IDX_RDPTR ; 
 int /*<<< orphan*/  KICKOFF_TIMEOUT_MS ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int dpu_encoder_helper_wait_for_irq (struct dpu_encoder_phys*,int /*<<< orphan*/ ,struct dpu_encoder_wait_info*) ; 
 int /*<<< orphan*/  dpu_encoder_phys_cmd_is_master (struct dpu_encoder_phys*) ; 
 struct dpu_encoder_phys_cmd* to_dpu_encoder_phys_cmd (struct dpu_encoder_phys*) ; 

__attribute__((used)) static int dpu_encoder_phys_cmd_wait_for_vblank(
		struct dpu_encoder_phys *phys_enc)
{
	int rc = 0;
	struct dpu_encoder_phys_cmd *cmd_enc;
	struct dpu_encoder_wait_info wait_info;

	if (!phys_enc)
		return -EINVAL;

	cmd_enc = to_dpu_encoder_phys_cmd(phys_enc);

	/* only required for master controller */
	if (!dpu_encoder_phys_cmd_is_master(phys_enc))
		return rc;

	wait_info.wq = &cmd_enc->pending_vblank_wq;
	wait_info.atomic_cnt = &cmd_enc->pending_vblank_cnt;
	wait_info.timeout_ms = KICKOFF_TIMEOUT_MS;

	atomic_inc(&cmd_enc->pending_vblank_cnt);

	rc = dpu_encoder_helper_wait_for_irq(phys_enc, INTR_IDX_RDPTR,
			&wait_info);

	return rc;
}