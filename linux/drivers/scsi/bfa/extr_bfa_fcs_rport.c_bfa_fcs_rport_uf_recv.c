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
typedef  int /*<<< orphan*/  u16 ;
struct fchs_s {scalar_t__ s_id; scalar_t__ d_id; scalar_t__ type; } ;
struct fc_els_cmd_s {scalar_t__ els_code; } ;
struct bfa_fcs_rport_s {int /*<<< orphan*/  itnim; int /*<<< orphan*/  fcs; struct bfa_fcs_lport_s* port; } ;
struct bfa_fcs_lport_s {int dummy; } ;

/* Variables and functions */
#define  FC_ELS_ADISC 132 
#define  FC_ELS_LOGO 131 
#define  FC_ELS_PRLI 130 
#define  FC_ELS_PRLO 129 
#define  FC_ELS_RPSC 128 
 int /*<<< orphan*/  FC_LS_RJT_EXP_NO_ADDL_INFO ; 
 int /*<<< orphan*/  FC_LS_RJT_RSN_CMD_NOT_SUPP ; 
 scalar_t__ FC_TYPE_ELS ; 
 int /*<<< orphan*/  adisc_rcvd ; 
 int /*<<< orphan*/  bfa_fcs_fcpim_uf_recv (int /*<<< orphan*/ ,struct fchs_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_fcs_lport_is_initiator (struct bfa_fcs_lport_s*) ; 
 int /*<<< orphan*/  bfa_fcs_rport_process_adisc (struct bfa_fcs_rport_s*,struct fchs_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_fcs_rport_process_logo (struct bfa_fcs_rport_s*,struct fchs_s*) ; 
 int /*<<< orphan*/  bfa_fcs_rport_process_prli (struct bfa_fcs_rport_s*,struct fchs_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_fcs_rport_process_rpsc (struct bfa_fcs_rport_s*,struct fchs_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_fcs_rport_send_ls_rjt (struct bfa_fcs_rport_s*,struct fchs_s*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_stats (struct bfa_fcs_lport_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_trc (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  plogi_rcvd ; 
 int /*<<< orphan*/  prli_rcvd ; 
 int /*<<< orphan*/  prlo_rcvd ; 
 int /*<<< orphan*/  rpsc_rcvd ; 
 int /*<<< orphan*/  un_handled_els_rcvd ; 

void
bfa_fcs_rport_uf_recv(struct bfa_fcs_rport_s *rport,
			struct fchs_s *fchs, u16 len)
{
	struct bfa_fcs_lport_s *port = rport->port;
	struct fc_els_cmd_s	*els_cmd;

	bfa_trc(rport->fcs, fchs->s_id);
	bfa_trc(rport->fcs, fchs->d_id);
	bfa_trc(rport->fcs, fchs->type);

	if (fchs->type != FC_TYPE_ELS)
		return;

	els_cmd = (struct fc_els_cmd_s *) (fchs + 1);

	bfa_trc(rport->fcs, els_cmd->els_code);

	switch (els_cmd->els_code) {
	case FC_ELS_LOGO:
		bfa_stats(port, plogi_rcvd);
		bfa_fcs_rport_process_logo(rport, fchs);
		break;

	case FC_ELS_ADISC:
		bfa_stats(port, adisc_rcvd);
		bfa_fcs_rport_process_adisc(rport, fchs, len);
		break;

	case FC_ELS_PRLO:
		bfa_stats(port, prlo_rcvd);
		if (bfa_fcs_lport_is_initiator(port))
			bfa_fcs_fcpim_uf_recv(rport->itnim, fchs, len);
		break;

	case FC_ELS_PRLI:
		bfa_stats(port, prli_rcvd);
		bfa_fcs_rport_process_prli(rport, fchs, len);
		break;

	case FC_ELS_RPSC:
		bfa_stats(port, rpsc_rcvd);
		bfa_fcs_rport_process_rpsc(rport, fchs, len);
		break;

	default:
		bfa_stats(port, un_handled_els_rcvd);
		bfa_fcs_rport_send_ls_rjt(rport, fchs,
					  FC_LS_RJT_RSN_CMD_NOT_SUPP,
					  FC_LS_RJT_EXP_NO_ADDL_INFO);
		break;
	}
}