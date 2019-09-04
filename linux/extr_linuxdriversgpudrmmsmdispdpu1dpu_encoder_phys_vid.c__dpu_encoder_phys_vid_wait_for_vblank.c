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
struct dpu_encoder_wait_info {int /*<<< orphan*/  timeout_ms; int /*<<< orphan*/ * atomic_cnt; int /*<<< orphan*/ * wq; } ;
struct dpu_encoder_phys {int /*<<< orphan*/  parent; TYPE_1__* parent_ops; int /*<<< orphan*/  pending_kickoff_cnt; int /*<<< orphan*/  pending_kickoff_wq; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* handle_frame_done ) (int /*<<< orphan*/ ,struct dpu_encoder_phys*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DPU_ENCODER_FRAME_EVENT_DONE ; 
 int EINVAL ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  INTR_IDX_VSYNC ; 
 int /*<<< orphan*/  KICKOFF_TIMEOUT_MS ; 
 int /*<<< orphan*/  dpu_encoder_helper_report_irq_timeout (struct dpu_encoder_phys*,int /*<<< orphan*/ ) ; 
 int dpu_encoder_helper_wait_for_irq (struct dpu_encoder_phys*,int /*<<< orphan*/ ,struct dpu_encoder_wait_info*) ; 
 int /*<<< orphan*/  dpu_encoder_phys_vid_is_master (struct dpu_encoder_phys*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,struct dpu_encoder_phys*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,struct dpu_encoder_phys*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int _dpu_encoder_phys_vid_wait_for_vblank(
		struct dpu_encoder_phys *phys_enc, bool notify)
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
		if (notify && phys_enc->parent_ops->handle_frame_done)
			phys_enc->parent_ops->handle_frame_done(
					phys_enc->parent, phys_enc,
					DPU_ENCODER_FRAME_EVENT_DONE);
		return 0;
	}

	/* Wait for kickoff to complete */
	ret = dpu_encoder_helper_wait_for_irq(phys_enc, INTR_IDX_VSYNC,
			&wait_info);

	if (ret == -ETIMEDOUT) {
		dpu_encoder_helper_report_irq_timeout(phys_enc, INTR_IDX_VSYNC);
	} else if (!ret && notify && phys_enc->parent_ops->handle_frame_done)
		phys_enc->parent_ops->handle_frame_done(
				phys_enc->parent, phys_enc,
				DPU_ENCODER_FRAME_EVENT_DONE);

	return ret;
}