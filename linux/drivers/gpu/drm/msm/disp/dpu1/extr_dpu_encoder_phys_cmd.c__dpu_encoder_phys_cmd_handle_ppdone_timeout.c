#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct dpu_encoder_phys_cmd {int pp_timeout_report_cnt; } ;
struct dpu_encoder_phys {int /*<<< orphan*/  parent; TYPE_3__* parent_ops; int /*<<< orphan*/  enable_state; int /*<<< orphan*/  pending_kickoff_cnt; TYPE_2__* hw_ctl; TYPE_1__* hw_pp; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* handle_frame_done ) (int /*<<< orphan*/ ,struct dpu_encoder_phys*,int /*<<< orphan*/ ) ;} ;
struct TYPE_5__ {scalar_t__ idx; } ;
struct TYPE_4__ {scalar_t__ idx; } ;

/* Variables and functions */
 scalar_t__ CTL_0 ; 
 int /*<<< orphan*/  DPU_ENCODER_FRAME_EVENT_ERROR ; 
 int /*<<< orphan*/  DPU_ENCODER_FRAME_EVENT_PANEL_DEAD ; 
 int /*<<< orphan*/  DPU_ENC_ERR_NEEDS_HW_RESET ; 
 int /*<<< orphan*/  DRMID (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DRM_ERROR (char*,int /*<<< orphan*/ ,scalar_t__,scalar_t__,int,int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  INTR_IDX_RDPTR ; 
 scalar_t__ PINGPONG_0 ; 
 int PP_TIMEOUT_MAX_TRIALS ; 
 int /*<<< orphan*/  atomic_add_unless (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dpu_encoder_helper_unregister_irq (struct dpu_encoder_phys*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,struct dpu_encoder_phys*,int /*<<< orphan*/ ) ; 
 struct dpu_encoder_phys_cmd* to_dpu_encoder_phys_cmd (struct dpu_encoder_phys*) ; 
 int /*<<< orphan*/  trace_dpu_enc_phys_cmd_pdone_timeout (int /*<<< orphan*/ ,scalar_t__,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int _dpu_encoder_phys_cmd_handle_ppdone_timeout(
		struct dpu_encoder_phys *phys_enc)
{
	struct dpu_encoder_phys_cmd *cmd_enc =
			to_dpu_encoder_phys_cmd(phys_enc);
	u32 frame_event = DPU_ENCODER_FRAME_EVENT_ERROR;
	bool do_log = false;

	if (!phys_enc || !phys_enc->hw_pp || !phys_enc->hw_ctl)
		return -EINVAL;

	cmd_enc->pp_timeout_report_cnt++;
	if (cmd_enc->pp_timeout_report_cnt == PP_TIMEOUT_MAX_TRIALS) {
		frame_event |= DPU_ENCODER_FRAME_EVENT_PANEL_DEAD;
		do_log = true;
	} else if (cmd_enc->pp_timeout_report_cnt == 1) {
		do_log = true;
	}

	trace_dpu_enc_phys_cmd_pdone_timeout(DRMID(phys_enc->parent),
		     phys_enc->hw_pp->idx - PINGPONG_0,
		     cmd_enc->pp_timeout_report_cnt,
		     atomic_read(&phys_enc->pending_kickoff_cnt),
		     frame_event);

	/* to avoid flooding, only log first time, and "dead" time */
	if (do_log) {
		DRM_ERROR("id:%d pp:%d kickoff timeout %d cnt %d koff_cnt %d\n",
			  DRMID(phys_enc->parent),
			  phys_enc->hw_pp->idx - PINGPONG_0,
			  phys_enc->hw_ctl->idx - CTL_0,
			  cmd_enc->pp_timeout_report_cnt,
			  atomic_read(&phys_enc->pending_kickoff_cnt));

		dpu_encoder_helper_unregister_irq(phys_enc, INTR_IDX_RDPTR);
	}

	atomic_add_unless(&phys_enc->pending_kickoff_cnt, -1, 0);

	/* request a ctl reset before the next kickoff */
	phys_enc->enable_state = DPU_ENC_ERR_NEEDS_HW_RESET;

	if (phys_enc->parent_ops->handle_frame_done)
		phys_enc->parent_ops->handle_frame_done(
				phys_enc->parent, phys_enc, frame_event);

	return -ETIMEDOUT;
}