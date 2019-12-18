#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_8__ ;
typedef  struct TYPE_19__   TYPE_7__ ;
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {int flags; int /*<<< orphan*/ * data; } ;
struct TYPE_16__ {TYPE_3__ logio; } ;
struct srb_iocb {TYPE_4__ u; } ;
struct TYPE_13__ {struct srb_iocb iocb_cmd; } ;
struct TYPE_19__ {int type; int /*<<< orphan*/  (* done ) (TYPE_7__*,int /*<<< orphan*/ ) ;TYPE_6__* qpair; int /*<<< orphan*/  handle; int /*<<< orphan*/  name; TYPE_1__ u; TYPE_8__* fcport; } ;
typedef  TYPE_7__ srb_t ;
struct TYPE_14__ {int /*<<< orphan*/  b24; } ;
struct TYPE_20__ {int flags; int /*<<< orphan*/  port_name; TYPE_2__ d_id; int /*<<< orphan*/  vha; } ;
typedef  TYPE_8__ fc_port_t ;
struct TYPE_18__ {int /*<<< orphan*/  qp_lock_ptr; TYPE_5__* req; } ;
struct TYPE_17__ {int num_outstanding_cmds; TYPE_7__** outstanding_cmds; } ;

/* Variables and functions */
 int FCF_ASYNC_ACTIVE ; 
 int FCF_ASYNC_SENT ; 
 int /*<<< orphan*/  MBS_COMMAND_ERROR ; 
 int /*<<< orphan*/  QLA_FUNCTION_TIMEOUT ; 
 int /*<<< orphan*/  QLA_LOGIO_LOGIN_RETRIED ; 
#define  SRB_CTRL_VP 135 
#define  SRB_CT_PTHRU_CMD 134 
#define  SRB_LOGIN_CMD 133 
 int SRB_LOGIN_RETRIED ; 
#define  SRB_LOGOUT_CMD 132 
#define  SRB_MB_IOCB 131 
#define  SRB_NACK_LOGO 130 
#define  SRB_NACK_PLOGI 129 
#define  SRB_NACK_PRLI 128 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ql_dbg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ql_dbg_disc ; 
 int qla24xx_async_abort_cmd (TYPE_7__*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  stub1 (TYPE_7__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (TYPE_7__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (TYPE_7__*,int /*<<< orphan*/ ) ; 

void
qla2x00_async_iocb_timeout(void *data)
{
	srb_t *sp = data;
	fc_port_t *fcport = sp->fcport;
	struct srb_iocb *lio = &sp->u.iocb_cmd;
	int rc, h;
	unsigned long flags;

	if (fcport) {
		ql_dbg(ql_dbg_disc, fcport->vha, 0x2071,
		    "Async-%s timeout - hdl=%x portid=%06x %8phC.\n",
		    sp->name, sp->handle, fcport->d_id.b24, fcport->port_name);

		fcport->flags &= ~(FCF_ASYNC_SENT | FCF_ASYNC_ACTIVE);
	} else {
		pr_info("Async-%s timeout - hdl=%x.\n",
		    sp->name, sp->handle);
	}

	switch (sp->type) {
	case SRB_LOGIN_CMD:
		rc = qla24xx_async_abort_cmd(sp, false);
		if (rc) {
			/* Retry as needed. */
			lio->u.logio.data[0] = MBS_COMMAND_ERROR;
			lio->u.logio.data[1] =
				lio->u.logio.flags & SRB_LOGIN_RETRIED ?
				QLA_LOGIO_LOGIN_RETRIED : 0;
			spin_lock_irqsave(sp->qpair->qp_lock_ptr, flags);
			for (h = 1; h < sp->qpair->req->num_outstanding_cmds;
			    h++) {
				if (sp->qpair->req->outstanding_cmds[h] ==
				    sp) {
					sp->qpair->req->outstanding_cmds[h] =
					    NULL;
					break;
				}
			}
			spin_unlock_irqrestore(sp->qpair->qp_lock_ptr, flags);
			sp->done(sp, QLA_FUNCTION_TIMEOUT);
		}
		break;
	case SRB_LOGOUT_CMD:
	case SRB_CT_PTHRU_CMD:
	case SRB_MB_IOCB:
	case SRB_NACK_PLOGI:
	case SRB_NACK_PRLI:
	case SRB_NACK_LOGO:
	case SRB_CTRL_VP:
		rc = qla24xx_async_abort_cmd(sp, false);
		if (rc) {
			spin_lock_irqsave(sp->qpair->qp_lock_ptr, flags);
			for (h = 1; h < sp->qpair->req->num_outstanding_cmds;
			    h++) {
				if (sp->qpair->req->outstanding_cmds[h] ==
				    sp) {
					sp->qpair->req->outstanding_cmds[h] =
					    NULL;
					break;
				}
			}
			spin_unlock_irqrestore(sp->qpair->qp_lock_ptr, flags);
			sp->done(sp, QLA_FUNCTION_TIMEOUT);
		}
		break;
	default:
		WARN_ON_ONCE(true);
		sp->done(sp, QLA_FUNCTION_TIMEOUT);
		break;
	}
}