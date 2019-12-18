#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct imm_ntfy_from_isp {int dummy; } ;
struct TYPE_13__ {struct imm_ntfy_from_isp* ntfy; } ;
struct TYPE_14__ {TYPE_1__ nack; } ;
struct TYPE_15__ {TYPE_2__ u; int /*<<< orphan*/  timeout; } ;
struct TYPE_16__ {TYPE_3__ iocb_cmd; } ;
struct TYPE_17__ {int type; char* name; int /*<<< orphan*/  (* free ) (TYPE_5__*) ;int /*<<< orphan*/  handle; int /*<<< orphan*/  done; TYPE_4__ u; } ;
typedef  TYPE_5__ srb_t ;
typedef  int /*<<< orphan*/  scsi_qla_host_t ;
struct TYPE_18__ {int /*<<< orphan*/  flags; int /*<<< orphan*/  port_name; int /*<<< orphan*/  fw_login_state; int /*<<< orphan*/  deleted; } ;
typedef  TYPE_6__ fc_port_t ;

/* Variables and functions */
 int /*<<< orphan*/  DSC_LS_LOGO_PEND ; 
 int /*<<< orphan*/  DSC_LS_PLOGI_PEND ; 
 int /*<<< orphan*/  DSC_LS_PRLI_PEND ; 
 int /*<<< orphan*/  FCF_ASYNC_SENT ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int QLA_FUNCTION_FAILED ; 
 int QLA_SUCCESS ; 
#define  SRB_NACK_LOGO 130 
#define  SRB_NACK_PLOGI 129 
#define  SRB_NACK_PRLI 128 
 int /*<<< orphan*/  ql_dbg (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ql_dbg_disc ; 
 int /*<<< orphan*/  qla2x00_async_iocb_timeout ; 
 int /*<<< orphan*/  qla2x00_async_nack_sp_done ; 
 scalar_t__ qla2x00_get_async_timeout (int /*<<< orphan*/ *) ; 
 TYPE_5__* qla2x00_get_sp (int /*<<< orphan*/ *,TYPE_6__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qla2x00_init_timer (TYPE_5__*,scalar_t__) ; 
 int qla2x00_start_sp (TYPE_5__*) ; 
 int /*<<< orphan*/  stub1 (TYPE_5__*) ; 

int qla24xx_async_notify_ack(scsi_qla_host_t *vha, fc_port_t *fcport,
	struct imm_ntfy_from_isp *ntfy, int type)
{
	int rval = QLA_FUNCTION_FAILED;
	srb_t *sp;
	char *c = NULL;

	fcport->flags |= FCF_ASYNC_SENT;
	switch (type) {
	case SRB_NACK_PLOGI:
		fcport->fw_login_state = DSC_LS_PLOGI_PEND;
		c = "PLOGI";
		break;
	case SRB_NACK_PRLI:
		fcport->fw_login_state = DSC_LS_PRLI_PEND;
		fcport->deleted = 0;
		c = "PRLI";
		break;
	case SRB_NACK_LOGO:
		fcport->fw_login_state = DSC_LS_LOGO_PEND;
		c = "LOGO";
		break;
	}

	sp = qla2x00_get_sp(vha, fcport, GFP_ATOMIC);
	if (!sp)
		goto done;

	sp->type = type;
	sp->name = "nack";

	sp->u.iocb_cmd.timeout = qla2x00_async_iocb_timeout;
	qla2x00_init_timer(sp, qla2x00_get_async_timeout(vha)+2);

	sp->u.iocb_cmd.u.nack.ntfy = ntfy;
	sp->done = qla2x00_async_nack_sp_done;

	ql_dbg(ql_dbg_disc, vha, 0x20f4,
	    "Async-%s %8phC hndl %x %s\n",
	    sp->name, fcport->port_name, sp->handle, c);

	rval = qla2x00_start_sp(sp);
	if (rval != QLA_SUCCESS)
		goto done_free_sp;

	return rval;

done_free_sp:
	sp->free(sp);
done:
	fcport->flags &= ~FCF_ASYNC_SENT;
	return rval;
}