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
typedef  int /*<<< orphan*/  u8 ;
struct fchs_s {int /*<<< orphan*/  ox_id; int /*<<< orphan*/  s_id; } ;
struct bfa_fcxp_s {int dummy; } ;
struct bfa_fcs_rport_s {int /*<<< orphan*/  fcs; struct bfa_fcs_lport_s* port; } ;
struct bfa_fcs_lport_s {int /*<<< orphan*/  lp_tag; TYPE_1__* fabric; } ;
struct TYPE_2__ {int /*<<< orphan*/  vf_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  BFA_FALSE ; 
 int /*<<< orphan*/  FC_CLASS_3 ; 
 int /*<<< orphan*/  FC_MAX_PDUSZ ; 
 struct bfa_fcxp_s* bfa_fcs_fcxp_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_fcs_lport_get_fcid (struct bfa_fcs_lport_s*) ; 
 int /*<<< orphan*/  bfa_fcxp_get_reqbuf (struct bfa_fcxp_s*) ; 
 int /*<<< orphan*/  bfa_fcxp_send (struct bfa_fcxp_s*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct fchs_s*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_trc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int fc_ls_rjt_build (struct fchs_s*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bfa_fcs_rport_send_ls_rjt(struct bfa_fcs_rport_s *rport, struct fchs_s *rx_fchs,
			  u8 reason_code, u8 reason_code_expl)
{
	struct bfa_fcs_lport_s *port = rport->port;
	struct fchs_s	fchs;
	struct bfa_fcxp_s *fcxp;
	int		len;

	bfa_trc(rport->fcs, rx_fchs->s_id);

	fcxp = bfa_fcs_fcxp_alloc(rport->fcs, BFA_FALSE);
	if (!fcxp)
		return;

	len = fc_ls_rjt_build(&fchs, bfa_fcxp_get_reqbuf(fcxp),
				rx_fchs->s_id, bfa_fcs_lport_get_fcid(port),
				rx_fchs->ox_id, reason_code, reason_code_expl);

	bfa_fcxp_send(fcxp, NULL, port->fabric->vf_id, port->lp_tag,
			BFA_FALSE, FC_CLASS_3, len, &fchs, NULL, NULL,
			FC_MAX_PDUSZ, 0);
}