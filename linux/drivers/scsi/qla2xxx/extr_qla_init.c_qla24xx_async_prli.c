#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_7__ ;
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {int /*<<< orphan*/  flags; } ;
struct TYPE_17__ {TYPE_3__ logio; } ;
struct srb_iocb {TYPE_4__ u; int /*<<< orphan*/  timeout; } ;
struct TYPE_14__ {int /*<<< orphan*/  online; } ;
struct scsi_qla_host {int /*<<< orphan*/  dpc_flags; TYPE_1__ flags; } ;
struct TYPE_15__ {struct srb_iocb iocb_cmd; } ;
struct TYPE_19__ {char* name; int /*<<< orphan*/  (* free ) (TYPE_6__*) ;int /*<<< orphan*/  handle; int /*<<< orphan*/  done; TYPE_2__ u; int /*<<< orphan*/  type; } ;
typedef  TYPE_6__ srb_t ;
struct TYPE_18__ {int /*<<< orphan*/  b24; } ;
struct TYPE_20__ {scalar_t__ fw_login_state; int /*<<< orphan*/  flags; scalar_t__ fc4f_nvme; int /*<<< orphan*/  login_retry; TYPE_5__ d_id; int /*<<< orphan*/  loop_id; int /*<<< orphan*/  port_name; scalar_t__ logout_completed; } ;
typedef  TYPE_7__ fc_port_t ;

/* Variables and functions */
 scalar_t__ DSC_LS_PLOGI_PEND ; 
 scalar_t__ DSC_LS_PRLI_PEND ; 
 int /*<<< orphan*/  FCF_ASYNC_SENT ; 
 int /*<<< orphan*/  FCF_LOGIN_NEEDED ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int QLA_FUNCTION_FAILED ; 
 int QLA_SUCCESS ; 
 int /*<<< orphan*/  RELOGIN_NEEDED ; 
 int /*<<< orphan*/  SRB_LOGIN_NVME_PRLI ; 
 int /*<<< orphan*/  SRB_PRLI_CMD ; 
 int /*<<< orphan*/  ql_dbg (int /*<<< orphan*/ ,struct scsi_qla_host*,int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ql_dbg_disc ; 
 int /*<<< orphan*/  qla2x00_async_iocb_timeout ; 
 int /*<<< orphan*/  qla2x00_async_prli_sp_done ; 
 scalar_t__ qla2x00_get_async_timeout (struct scsi_qla_host*) ; 
 TYPE_6__* qla2x00_get_sp (struct scsi_qla_host*,TYPE_7__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qla2x00_init_timer (TYPE_6__*,scalar_t__) ; 
 int qla2x00_start_sp (TYPE_6__*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (TYPE_6__*) ; 

int
qla24xx_async_prli(struct scsi_qla_host *vha, fc_port_t *fcport)
{
	srb_t *sp;
	struct srb_iocb *lio;
	int rval = QLA_FUNCTION_FAILED;

	if (!vha->flags.online)
		return rval;

	if (fcport->fw_login_state == DSC_LS_PLOGI_PEND ||
	    fcport->fw_login_state == DSC_LS_PRLI_PEND)
		return rval;

	sp = qla2x00_get_sp(vha, fcport, GFP_KERNEL);
	if (!sp)
		return rval;

	fcport->flags |= FCF_ASYNC_SENT;
	fcport->logout_completed = 0;

	sp->type = SRB_PRLI_CMD;
	sp->name = "prli";

	lio = &sp->u.iocb_cmd;
	lio->timeout = qla2x00_async_iocb_timeout;
	qla2x00_init_timer(sp, qla2x00_get_async_timeout(vha) + 2);

	sp->done = qla2x00_async_prli_sp_done;
	lio->u.logio.flags = 0;

	if  (fcport->fc4f_nvme)
		lio->u.logio.flags |= SRB_LOGIN_NVME_PRLI;

	ql_dbg(ql_dbg_disc, vha, 0x211b,
	    "Async-prli - %8phC hdl=%x, loopid=%x portid=%06x retries=%d %s.\n",
	    fcport->port_name, sp->handle, fcport->loop_id, fcport->d_id.b24,
	    fcport->login_retry, fcport->fc4f_nvme ? "nvme" : "fc");

	rval = qla2x00_start_sp(sp);
	if (rval != QLA_SUCCESS) {
		fcport->flags |= FCF_LOGIN_NEEDED;
		set_bit(RELOGIN_NEEDED, &vha->dpc_flags);
		goto done_free_sp;
	}

	return rval;

done_free_sp:
	sp->free(sp);
	fcport->flags &= ~FCF_ASYNC_SENT;
	return rval;
}