#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_36__   TYPE_9__ ;
typedef  struct TYPE_35__   TYPE_8__ ;
typedef  struct TYPE_34__   TYPE_7__ ;
typedef  struct TYPE_33__   TYPE_6__ ;
typedef  struct TYPE_32__   TYPE_5__ ;
typedef  struct TYPE_31__   TYPE_4__ ;
typedef  struct TYPE_30__   TYPE_3__ ;
typedef  struct TYPE_29__   TYPE_2__ ;
typedef  struct TYPE_28__   TYPE_1__ ;
typedef  struct TYPE_27__   TYPE_13__ ;
typedef  struct TYPE_26__   TYPE_12__ ;
typedef  struct TYPE_25__   TYPE_11__ ;
typedef  struct TYPE_24__   TYPE_10__ ;

/* Type definitions */
struct TYPE_29__ {int /*<<< orphan*/  port_name; } ;
struct TYPE_30__ {TYPE_2__ gpsc; } ;
struct ct_sns_req {TYPE_3__ req; } ;
struct TYPE_32__ {int /*<<< orphan*/  nport_handle; int /*<<< orphan*/  rsp_size; int /*<<< orphan*/  req_size; int /*<<< orphan*/  rsp_dma; int /*<<< orphan*/  rsp; int /*<<< orphan*/  req_dma; int /*<<< orphan*/  req; } ;
struct TYPE_33__ {TYPE_5__ ctarg; } ;
struct TYPE_34__ {int /*<<< orphan*/  timeout; TYPE_6__ u; } ;
struct TYPE_35__ {TYPE_7__ iocb_cmd; } ;
struct TYPE_25__ {char* name; int /*<<< orphan*/  (* free ) (TYPE_11__*) ;int /*<<< orphan*/  handle; int /*<<< orphan*/  done; TYPE_8__ u; int /*<<< orphan*/  gen2; int /*<<< orphan*/  gen1; int /*<<< orphan*/  type; } ;
typedef  TYPE_11__ srb_t ;
struct TYPE_28__ {int /*<<< orphan*/  online; } ;
struct TYPE_26__ {int /*<<< orphan*/  mgmt_svr_loop_id; TYPE_1__ flags; } ;
typedef  TYPE_12__ scsi_qla_host_t ;
struct TYPE_36__ {int /*<<< orphan*/  al_pa; int /*<<< orphan*/  area; int /*<<< orphan*/  domain; } ;
struct TYPE_24__ {TYPE_9__ b; } ;
struct TYPE_31__ {int /*<<< orphan*/  ct_sns_dma; int /*<<< orphan*/  ct_sns; } ;
struct TYPE_27__ {int flags; TYPE_10__ d_id; int /*<<< orphan*/  loop_id; int /*<<< orphan*/  port_name; TYPE_4__ ct_desc; int /*<<< orphan*/  fabric_port_name; int /*<<< orphan*/  login_gen; int /*<<< orphan*/  rscn_gen; } ;
typedef  TYPE_13__ fc_port_t ;

/* Variables and functions */
 int FCF_ASYNC_ACTIVE ; 
 int FCF_ASYNC_SENT ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GPSC_CMD ; 
 int /*<<< orphan*/  GPSC_REQ_SIZE ; 
 int /*<<< orphan*/  GPSC_RSP_SIZE ; 
 int QLA_FUNCTION_FAILED ; 
 int QLA_SUCCESS ; 
 int /*<<< orphan*/  SRB_CT_PTHRU_CMD ; 
 int /*<<< orphan*/  WWN_SIZE ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ql_dbg (int /*<<< orphan*/ ,TYPE_12__*,int,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ql_dbg_disc ; 
 int /*<<< orphan*/  qla24xx_async_gpsc_sp_done ; 
 struct ct_sns_req* qla24xx_prep_ct_fm_req (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qla2x00_async_iocb_timeout ; 
 scalar_t__ qla2x00_get_async_timeout (TYPE_12__*) ; 
 TYPE_11__* qla2x00_get_sp (TYPE_12__*,TYPE_13__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qla2x00_init_timer (TYPE_11__*,scalar_t__) ; 
 int qla2x00_start_sp (TYPE_11__*) ; 
 int /*<<< orphan*/  stub1 (TYPE_11__*) ; 

int qla24xx_async_gpsc(scsi_qla_host_t *vha, fc_port_t *fcport)
{
	int rval = QLA_FUNCTION_FAILED;
	struct ct_sns_req       *ct_req;
	srb_t *sp;

	if (!vha->flags.online || (fcport->flags & FCF_ASYNC_SENT))
		return rval;

	sp = qla2x00_get_sp(vha, fcport, GFP_KERNEL);
	if (!sp)
		goto done;

	sp->type = SRB_CT_PTHRU_CMD;
	sp->name = "gpsc";
	sp->gen1 = fcport->rscn_gen;
	sp->gen2 = fcport->login_gen;

	qla2x00_init_timer(sp, qla2x00_get_async_timeout(vha) + 2);

	/* CT_IU preamble  */
	ct_req = qla24xx_prep_ct_fm_req(fcport->ct_desc.ct_sns, GPSC_CMD,
		GPSC_RSP_SIZE);

	/* GPSC req */
	memcpy(ct_req->req.gpsc.port_name, fcport->fabric_port_name,
		WWN_SIZE);

	sp->u.iocb_cmd.u.ctarg.req = fcport->ct_desc.ct_sns;
	sp->u.iocb_cmd.u.ctarg.req_dma = fcport->ct_desc.ct_sns_dma;
	sp->u.iocb_cmd.u.ctarg.rsp = fcport->ct_desc.ct_sns;
	sp->u.iocb_cmd.u.ctarg.rsp_dma = fcport->ct_desc.ct_sns_dma;
	sp->u.iocb_cmd.u.ctarg.req_size = GPSC_REQ_SIZE;
	sp->u.iocb_cmd.u.ctarg.rsp_size = GPSC_RSP_SIZE;
	sp->u.iocb_cmd.u.ctarg.nport_handle = vha->mgmt_svr_loop_id;

	sp->u.iocb_cmd.timeout = qla2x00_async_iocb_timeout;
	sp->done = qla24xx_async_gpsc_sp_done;

	ql_dbg(ql_dbg_disc, vha, 0x205e,
	    "Async-%s %8phC hdl=%x loopid=%x portid=%02x%02x%02x.\n",
	    sp->name, fcport->port_name, sp->handle,
	    fcport->loop_id, fcport->d_id.b.domain,
	    fcport->d_id.b.area, fcport->d_id.b.al_pa);

	rval = qla2x00_start_sp(sp);
	if (rval != QLA_SUCCESS)
		goto done_free_sp;
	return rval;

done_free_sp:
	sp->free(sp);
	fcport->flags &= ~FCF_ASYNC_SENT;
done:
	fcport->flags &= ~FCF_ASYNC_ACTIVE;
	return rval;
}