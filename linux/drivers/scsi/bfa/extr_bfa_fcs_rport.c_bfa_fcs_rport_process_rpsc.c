#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct fchs_s {int /*<<< orphan*/  ox_id; int /*<<< orphan*/  s_id; int /*<<< orphan*/  d_id; } ;
struct fc_rpsc_speed_info_s {int port_speed_cap; int /*<<< orphan*/  port_op_speed; } ;
struct bfa_port_attr_s {int /*<<< orphan*/  speed; } ;
struct bfa_fcxp_s {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  rpsc_rcvd; } ;
struct bfa_fcs_rport_s {TYPE_1__ stats; struct bfa_fcs_lport_s* port; } ;
struct bfa_fcs_lport_s {int /*<<< orphan*/  lp_tag; TYPE_2__* fabric; TYPE_3__* fcs; } ;
struct TYPE_7__ {int /*<<< orphan*/  bfa; } ;
struct TYPE_6__ {int /*<<< orphan*/  vf_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  BFA_FALSE ; 
 int /*<<< orphan*/  FC_CLASS_3 ; 
 int /*<<< orphan*/  FC_MAX_PDUSZ ; 
 int RPSC_SPEED_CAP_1G ; 
 int RPSC_SPEED_CAP_2G ; 
 int RPSC_SPEED_CAP_4G ; 
 int RPSC_SPEED_CAP_8G ; 
 int /*<<< orphan*/  bfa_fcport_get_attr (int /*<<< orphan*/ ,struct bfa_port_attr_s*) ; 
 struct bfa_fcxp_s* bfa_fcs_fcxp_alloc (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_fcs_lport_get_fcid (struct bfa_fcs_lport_s*) ; 
 int /*<<< orphan*/  bfa_fcxp_get_reqbuf (struct bfa_fcxp_s*) ; 
 int /*<<< orphan*/  bfa_fcxp_send (struct bfa_fcxp_s*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct fchs_s*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_trc (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fc_bfa_speed_to_rpsc_operspeed (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fc_rpsc_acc_build (struct fchs_s*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct fc_rpsc_speed_info_s*) ; 

__attribute__((used)) static void
bfa_fcs_rport_process_rpsc(struct bfa_fcs_rport_s *rport,
			struct fchs_s *rx_fchs, u16 len)
{
	struct bfa_fcxp_s *fcxp;
	struct fchs_s	fchs;
	struct bfa_fcs_lport_s *port = rport->port;
	struct fc_rpsc_speed_info_s speeds;
	struct bfa_port_attr_s pport_attr;

	bfa_trc(port->fcs, rx_fchs->s_id);
	bfa_trc(port->fcs, rx_fchs->d_id);

	rport->stats.rpsc_rcvd++;
	speeds.port_speed_cap =
		RPSC_SPEED_CAP_1G | RPSC_SPEED_CAP_2G | RPSC_SPEED_CAP_4G |
		RPSC_SPEED_CAP_8G;

	/*
	 * get curent speed from pport attributes from BFA
	 */
	bfa_fcport_get_attr(port->fcs->bfa, &pport_attr);

	speeds.port_op_speed = fc_bfa_speed_to_rpsc_operspeed(pport_attr.speed);

	fcxp = bfa_fcs_fcxp_alloc(port->fcs, BFA_FALSE);
	if (!fcxp)
		return;

	len = fc_rpsc_acc_build(&fchs, bfa_fcxp_get_reqbuf(fcxp),
				rx_fchs->s_id, bfa_fcs_lport_get_fcid(port),
				rx_fchs->ox_id, &speeds);

	bfa_fcxp_send(fcxp, NULL, port->fabric->vf_id, port->lp_tag, BFA_FALSE,
			FC_CLASS_3, len, &fchs, NULL, NULL, FC_MAX_PDUSZ, 0);
}