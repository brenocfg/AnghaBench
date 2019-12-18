#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct scsi_qla_host {TYPE_3__* hw; int /*<<< orphan*/  fcport_count; } ;
struct TYPE_12__ {int /*<<< orphan*/  (* free ) (TYPE_4__*) ;TYPE_6__* fcport; int /*<<< orphan*/  type; int /*<<< orphan*/  name; struct scsi_qla_host* vha; } ;
typedef  TYPE_4__ srb_t ;
struct TYPE_13__ {int logout_on_delete; int login_succ; int /*<<< orphan*/  fw_login_state; int /*<<< orphan*/  login_gen; int /*<<< orphan*/  deleted; int /*<<< orphan*/  disc_state; int /*<<< orphan*/  login_retry; int /*<<< orphan*/  d_id; int /*<<< orphan*/  send_els_logo; scalar_t__ plogi_nack_done_deadline; int /*<<< orphan*/  chip_reset; int /*<<< orphan*/  flags; int /*<<< orphan*/  port_name; } ;
struct TYPE_10__ {int /*<<< orphan*/  sess_lock; } ;
struct TYPE_11__ {TYPE_2__ tgt; TYPE_1__* base_qpair; } ;
struct TYPE_9__ {int /*<<< orphan*/  chip_reset; } ;

/* Variables and functions */
 int /*<<< orphan*/  DSC_LOGIN_COMPLETE ; 
 int /*<<< orphan*/  DSC_LS_PLOGI_COMP ; 
 int /*<<< orphan*/  DSC_LS_PORT_UNAVAIL ; 
 int /*<<< orphan*/  DSC_LS_PRLI_COMP ; 
 int /*<<< orphan*/  FCF_ASYNC_SENT ; 
 scalar_t__ HZ ; 
 int /*<<< orphan*/  IS_SW_RESV_ADDR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MBS_COMMAND_COMPLETE ; 
#define  SRB_NACK_LOGO 130 
#define  SRB_NACK_PLOGI 129 
#define  SRB_NACK_PRLI 128 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  ql_dbg (int /*<<< orphan*/ ,struct scsi_qla_host*,int,char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ql_dbg_disc ; 
 int /*<<< orphan*/  qla24xx_sched_upd_fcport (TYPE_6__*) ; 
 int /*<<< orphan*/  qlt_logo_completion_handler (TYPE_6__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (TYPE_4__*) ; 

__attribute__((used)) static void qla2x00_async_nack_sp_done(srb_t *sp, int res)
{
	struct scsi_qla_host *vha = sp->vha;
	unsigned long flags;

	ql_dbg(ql_dbg_disc, vha, 0x20f2,
	    "Async done-%s res %x %8phC  type %d\n",
	    sp->name, res, sp->fcport->port_name, sp->type);

	spin_lock_irqsave(&vha->hw->tgt.sess_lock, flags);
	sp->fcport->flags &= ~FCF_ASYNC_SENT;
	sp->fcport->chip_reset = vha->hw->base_qpair->chip_reset;

	switch (sp->type) {
	case SRB_NACK_PLOGI:
		sp->fcport->login_gen++;
		sp->fcport->fw_login_state = DSC_LS_PLOGI_COMP;
		sp->fcport->logout_on_delete = 1;
		sp->fcport->plogi_nack_done_deadline = jiffies + HZ;
		sp->fcport->send_els_logo = 0;
		break;

	case SRB_NACK_PRLI:
		sp->fcport->fw_login_state = DSC_LS_PRLI_COMP;
		sp->fcport->deleted = 0;
		sp->fcport->send_els_logo = 0;

		if (!sp->fcport->login_succ &&
		    !IS_SW_RESV_ADDR(sp->fcport->d_id)) {
			sp->fcport->login_succ = 1;

			vha->fcport_count++;
			spin_unlock_irqrestore(&vha->hw->tgt.sess_lock, flags);
			qla24xx_sched_upd_fcport(sp->fcport);
			spin_lock_irqsave(&vha->hw->tgt.sess_lock, flags);
		} else {
			sp->fcport->login_retry = 0;
			sp->fcport->disc_state = DSC_LOGIN_COMPLETE;
			sp->fcport->deleted = 0;
			sp->fcport->logout_on_delete = 1;
		}
		break;

	case SRB_NACK_LOGO:
		sp->fcport->login_gen++;
		sp->fcport->fw_login_state = DSC_LS_PORT_UNAVAIL;
		qlt_logo_completion_handler(sp->fcport, MBS_COMMAND_COMPLETE);
		break;
	}
	spin_unlock_irqrestore(&vha->hw->tgt.sess_lock, flags);

	sp->free(sp);
}