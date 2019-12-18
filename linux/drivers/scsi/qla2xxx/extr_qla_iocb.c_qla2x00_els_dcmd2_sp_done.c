#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;
typedef  struct TYPE_11__   TYPE_10__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  comp; } ;
struct TYPE_14__ {TYPE_10__ els_plogi; } ;
struct srb_iocb {TYPE_3__ u; int /*<<< orphan*/  timer; } ;
struct scsi_qla_host {int /*<<< orphan*/  dpc_flags; } ;
struct TYPE_15__ {TYPE_6__* sp; } ;
struct TYPE_16__ {TYPE_4__ iosb; } ;
struct qla_work_evt {TYPE_5__ u; } ;
struct event_arg {TYPE_6__* sp; int /*<<< orphan*/ * data; TYPE_7__* fcport; } ;
struct TYPE_13__ {struct srb_iocb iocb_cmd; } ;
struct TYPE_17__ {int flags; int /*<<< orphan*/  (* free ) (TYPE_6__*) ;TYPE_2__ u; int /*<<< orphan*/  handle; int /*<<< orphan*/  name; struct scsi_qla_host* vha; TYPE_7__* fcport; } ;
typedef  TYPE_6__ srb_t ;
struct TYPE_12__ {int /*<<< orphan*/  b24; } ;
struct TYPE_18__ {int flags; int /*<<< orphan*/  port_name; TYPE_1__ d_id; } ;
typedef  TYPE_7__ fc_port_t ;
typedef  int /*<<< orphan*/  ea ;

/* Variables and functions */
 int FCF_ASYNC_ACTIVE ; 
 int FCF_ASYNC_SENT ; 
 int /*<<< orphan*/  MBS_COMMAND_COMPLETE ; 
 int /*<<< orphan*/  QLA_EVT_UNMAP ; 
 int /*<<< orphan*/  RELOGIN_NEEDED ; 
 int SRB_WAKEUP_ON_COMP ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct event_arg*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ql_dbg (int /*<<< orphan*/ ,struct scsi_qla_host*,int,char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ql_dbg_disc ; 
 int /*<<< orphan*/  qla24xx_handle_plogi_done_event (struct scsi_qla_host*,struct event_arg*) ; 
 struct qla_work_evt* qla2x00_alloc_work (struct scsi_qla_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qla2x00_els_dcmd2_free (struct scsi_qla_host*,TYPE_10__*) ; 
 int /*<<< orphan*/  qla2x00_post_work (struct scsi_qla_host*,struct qla_work_evt*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (TYPE_6__*) ; 

__attribute__((used)) static void qla2x00_els_dcmd2_sp_done(srb_t *sp, int res)
{
	fc_port_t *fcport = sp->fcport;
	struct srb_iocb *lio = &sp->u.iocb_cmd;
	struct scsi_qla_host *vha = sp->vha;
	struct event_arg ea;
	struct qla_work_evt *e;

	ql_dbg(ql_dbg_disc, vha, 0x3072,
	    "%s ELS done rc %d hdl=%x, portid=%06x %8phC\n",
	    sp->name, res, sp->handle, fcport->d_id.b24, fcport->port_name);

	fcport->flags &= ~(FCF_ASYNC_SENT|FCF_ASYNC_ACTIVE);
	del_timer(&sp->u.iocb_cmd.timer);

	if (sp->flags & SRB_WAKEUP_ON_COMP)
		complete(&lio->u.els_plogi.comp);
	else {
		if (res) {
			set_bit(RELOGIN_NEEDED, &vha->dpc_flags);
		} else {
			memset(&ea, 0, sizeof(ea));
			ea.fcport = fcport;
			ea.data[0] = MBS_COMMAND_COMPLETE;
			ea.sp = sp;
			qla24xx_handle_plogi_done_event(vha, &ea);
		}

		e = qla2x00_alloc_work(vha, QLA_EVT_UNMAP);
		if (!e) {
			struct srb_iocb *elsio = &sp->u.iocb_cmd;

			qla2x00_els_dcmd2_free(vha, &elsio->u.els_plogi);
			sp->free(sp);
			return;
		}
		e->u.iosb.sp = sp;
		qla2x00_post_work(vha, e);
	}
}