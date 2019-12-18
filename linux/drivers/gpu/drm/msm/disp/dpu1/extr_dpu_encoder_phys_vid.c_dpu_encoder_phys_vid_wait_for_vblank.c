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
struct dpu_encoder_phys {int /*<<< orphan*/  pending_kickoff_cnt; int /*<<< orphan*/  pending_kickoff_wq; } ;

/* Variables and functions */
 int EINVAL ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  INTR_IDX_VSYNC ; 
 int /*<<< orphan*/  KICKOFF_TIMEOUT_MS ; 
 int /*<<< orphan*/  dpu_encoder_helper_report_irq_timeout (struct dpu_encoder_phys*,int /*<<< orphan*/ ) ; 
 int dpu_encoder_helper_wait_for_irq (struct dpu_encoder_phys*,int /*<<< orphan*/ ,struct dpu_encoder_wait_info*) ; 
 int /*<<< orphan*/  dpu_encoder_phys_vid_is_master (struct dpu_encoder_phys*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

__attribute__((used)) static int dpu_encoder_phys_vid_wait_for_vblank(
		struct dpu_encoder_phys *phys_enc)
{
	struct dpu_encoder_wait_info wait_info;
	int ret;

	if (!phys_enc) {
		pr_err("invalid encoder\n");
		return -EINVAL;
	}

	wait_info.wq = &phys_enc->pending_kickoff_wq;
	wait_info.atomic_cnt = &phys_enc->pending_kickoff_cnt;
	wait_info.timeout_ms = KICKOFF_TIMEOUT_MS;

	if (!dpu_encoder_phys_vid_is_master(phys_enc)) {
		return 0;
	}

	/* Wait for kickoff to complete */
	ret = dpu_encoder_helper_wait_for_irq(phys_enc, INTR_IDX_VSYNC,
			&wait_info);

	if (ret == -ETIMEDOUT) {
		dpu_encoder_helper_report_irq_timeout(phys_enc, INTR_IDX_VSYNC);
	}

	return ret;
}