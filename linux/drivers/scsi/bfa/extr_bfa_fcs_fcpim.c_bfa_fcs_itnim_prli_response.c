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
typedef  scalar_t__ u32 ;
struct fchs_s {int dummy; } ;
struct fc_prli_params_s {int /*<<< orphan*/  confirm; int /*<<< orphan*/  task_retry_id; int /*<<< orphan*/  rec_support; int /*<<< orphan*/  retry; scalar_t__ initiator; } ;
struct TYPE_5__ {scalar_t__ type; struct fc_prli_params_s servparams; } ;
struct fc_prli_s {TYPE_2__ parampage; } ;
struct fc_ls_rjt_s {scalar_t__ reason_code; scalar_t__ reason_code_expl; } ;
struct fc_els_cmd_s {scalar_t__ els_code; } ;
struct bfa_fcxp_s {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  prli_rsp_rjt; int /*<<< orphan*/  prli_rsp_acc; int /*<<< orphan*/  prli_rsp_parse_err; int /*<<< orphan*/  initiator; int /*<<< orphan*/  prli_rsp_err; } ;
struct bfa_fcs_itnim_s {TYPE_3__ stats; int /*<<< orphan*/  fcs; int /*<<< orphan*/  conf_comp; int /*<<< orphan*/  task_retry_id; int /*<<< orphan*/  rec_support; int /*<<< orphan*/  seq_rec; TYPE_1__* rport; } ;
typedef  scalar_t__ bfa_status_t ;
struct TYPE_4__ {int /*<<< orphan*/  scsi_function; } ;

/* Variables and functions */
 int /*<<< orphan*/  BFA_FCS_ITNIM_SM_RSP_ERROR ; 
 int /*<<< orphan*/  BFA_FCS_ITNIM_SM_RSP_NOT_SUPP ; 
 int /*<<< orphan*/  BFA_FCS_ITNIM_SM_RSP_OK ; 
 scalar_t__ BFA_FCXP_RSP_PLD (struct bfa_fcxp_s*) ; 
 int /*<<< orphan*/  BFA_RPORT_INITIATOR ; 
 int /*<<< orphan*/  BFA_RPORT_TARGET ; 
 scalar_t__ BFA_STATUS_OK ; 
 scalar_t__ FC_ELS_ACC ; 
 scalar_t__ FC_LS_RJT_RSN_CMD_NOT_SUPP ; 
 scalar_t__ FC_PARSE_OK ; 
 int /*<<< orphan*/  bfa_sm_send_event (struct bfa_fcs_itnim_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_trc (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ fc_prli_rsp_parse (struct fc_prli_s*,scalar_t__) ; 

__attribute__((used)) static void
bfa_fcs_itnim_prli_response(void *fcsarg, struct bfa_fcxp_s *fcxp, void *cbarg,
			    bfa_status_t req_status, u32 rsp_len,
			    u32 resid_len, struct fchs_s *rsp_fchs)
{
	struct bfa_fcs_itnim_s *itnim = (struct bfa_fcs_itnim_s *) cbarg;
	struct fc_els_cmd_s *els_cmd;
	struct fc_prli_s *prli_resp;
	struct fc_ls_rjt_s *ls_rjt;
	struct fc_prli_params_s *sparams;

	bfa_trc(itnim->fcs, req_status);

	/*
	 * Sanity Checks
	 */
	if (req_status != BFA_STATUS_OK) {
		itnim->stats.prli_rsp_err++;
		bfa_sm_send_event(itnim, BFA_FCS_ITNIM_SM_RSP_ERROR);
		return;
	}

	els_cmd = (struct fc_els_cmd_s *) BFA_FCXP_RSP_PLD(fcxp);

	if (els_cmd->els_code == FC_ELS_ACC) {
		prli_resp = (struct fc_prli_s *) els_cmd;

		if (fc_prli_rsp_parse(prli_resp, rsp_len) != FC_PARSE_OK) {
			bfa_trc(itnim->fcs, rsp_len);
			/*
			 * Check if this  r-port is also in Initiator mode.
			 * If so, we need to set this ITN as a no-op.
			 */
			if (prli_resp->parampage.servparams.initiator) {
				bfa_trc(itnim->fcs, prli_resp->parampage.type);
				itnim->rport->scsi_function =
						BFA_RPORT_INITIATOR;
				itnim->stats.prli_rsp_acc++;
				itnim->stats.initiator++;
				bfa_sm_send_event(itnim,
						  BFA_FCS_ITNIM_SM_RSP_OK);
				return;
			}

			itnim->stats.prli_rsp_parse_err++;
			return;
		}
		itnim->rport->scsi_function = BFA_RPORT_TARGET;

		sparams = &prli_resp->parampage.servparams;
		itnim->seq_rec	     = sparams->retry;
		itnim->rec_support   = sparams->rec_support;
		itnim->task_retry_id = sparams->task_retry_id;
		itnim->conf_comp     = sparams->confirm;

		itnim->stats.prli_rsp_acc++;
		bfa_sm_send_event(itnim, BFA_FCS_ITNIM_SM_RSP_OK);
	} else {
		ls_rjt = (struct fc_ls_rjt_s *) BFA_FCXP_RSP_PLD(fcxp);

		bfa_trc(itnim->fcs, ls_rjt->reason_code);
		bfa_trc(itnim->fcs, ls_rjt->reason_code_expl);

		itnim->stats.prli_rsp_rjt++;
		if (ls_rjt->reason_code == FC_LS_RJT_RSN_CMD_NOT_SUPP) {
			bfa_sm_send_event(itnim, BFA_FCS_ITNIM_SM_RSP_NOT_SUPP);
			return;
		}
		bfa_sm_send_event(itnim, BFA_FCS_ITNIM_SM_RSP_ERROR);
	}
}