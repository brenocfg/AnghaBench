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
struct TYPE_29__ {int /*<<< orphan*/ * port_id; } ;
struct TYPE_30__ {TYPE_2__ gff_id; } ;
struct ct_sns_req {TYPE_3__ req; } ;
struct TYPE_34__ {int /*<<< orphan*/  nport_handle; int /*<<< orphan*/  rsp_size; int /*<<< orphan*/  req_size; int /*<<< orphan*/  rsp_dma; int /*<<< orphan*/  rsp; int /*<<< orphan*/  req_dma; int /*<<< orphan*/  req; } ;
struct TYPE_35__ {TYPE_7__ ctarg; } ;
struct TYPE_36__ {TYPE_8__ u; int /*<<< orphan*/  timeout; } ;
struct TYPE_24__ {TYPE_9__ iocb_cmd; } ;
struct TYPE_25__ {char* name; int /*<<< orphan*/  (* free ) (TYPE_11__*) ;int /*<<< orphan*/  handle; int /*<<< orphan*/  done; TYPE_10__ u; int /*<<< orphan*/  gen2; int /*<<< orphan*/  gen1; int /*<<< orphan*/  type; } ;
typedef  TYPE_11__ srb_t ;
struct TYPE_28__ {int /*<<< orphan*/  online; } ;
struct TYPE_26__ {TYPE_1__ flags; } ;
typedef  TYPE_12__ scsi_qla_host_t ;
struct TYPE_33__ {int /*<<< orphan*/  ct_sns_dma; int /*<<< orphan*/  ct_sns; } ;
struct TYPE_31__ {int /*<<< orphan*/  al_pa; int /*<<< orphan*/  area; int /*<<< orphan*/  domain; } ;
struct TYPE_32__ {TYPE_4__ b; } ;
struct TYPE_27__ {int flags; int /*<<< orphan*/  port_name; TYPE_6__ ct_desc; TYPE_5__ d_id; int /*<<< orphan*/  login_gen; int /*<<< orphan*/  rscn_gen; } ;
typedef  TYPE_13__ fc_port_t ;

/* Variables and functions */
 int FCF_ASYNC_SENT ; 
 int /*<<< orphan*/  GFF_ID_CMD ; 
 int /*<<< orphan*/  GFF_ID_REQ_SIZE ; 
 int /*<<< orphan*/  GFF_ID_RSP_SIZE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  NPH_SNS ; 
 int QLA_FUNCTION_FAILED ; 
 int QLA_SUCCESS ; 
 int /*<<< orphan*/  SRB_CT_PTHRU_CMD ; 
 int /*<<< orphan*/  ql_dbg (int /*<<< orphan*/ ,TYPE_12__*,int,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ql_dbg_disc ; 
 int /*<<< orphan*/  qla24xx_async_gffid_sp_done ; 
 int /*<<< orphan*/  qla2x00_async_iocb_timeout ; 
 scalar_t__ qla2x00_get_async_timeout (TYPE_12__*) ; 
 TYPE_11__* qla2x00_get_sp (TYPE_12__*,TYPE_13__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qla2x00_init_timer (TYPE_11__*,scalar_t__) ; 
 struct ct_sns_req* qla2x00_prep_ct_req (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int qla2x00_start_sp (TYPE_11__*) ; 
 int /*<<< orphan*/  stub1 (TYPE_11__*) ; 

int qla24xx_async_gffid(scsi_qla_host_t *vha, fc_port_t *fcport)
{
	int rval = QLA_FUNCTION_FAILED;
	struct ct_sns_req       *ct_req;
	srb_t *sp;

	if (!vha->flags.online || (fcport->flags & FCF_ASYNC_SENT))
		return rval;

	sp = qla2x00_get_sp(vha, fcport, GFP_KERNEL);
	if (!sp)
		return rval;

	fcport->flags |= FCF_ASYNC_SENT;
	sp->type = SRB_CT_PTHRU_CMD;
	sp->name = "gffid";
	sp->gen1 = fcport->rscn_gen;
	sp->gen2 = fcport->login_gen;

	sp->u.iocb_cmd.timeout = qla2x00_async_iocb_timeout;
	qla2x00_init_timer(sp, qla2x00_get_async_timeout(vha) + 2);

	/* CT_IU preamble  */
	ct_req = qla2x00_prep_ct_req(fcport->ct_desc.ct_sns, GFF_ID_CMD,
	    GFF_ID_RSP_SIZE);

	ct_req->req.gff_id.port_id[0] = fcport->d_id.b.domain;
	ct_req->req.gff_id.port_id[1] = fcport->d_id.b.area;
	ct_req->req.gff_id.port_id[2] = fcport->d_id.b.al_pa;

	sp->u.iocb_cmd.u.ctarg.req = fcport->ct_desc.ct_sns;
	sp->u.iocb_cmd.u.ctarg.req_dma = fcport->ct_desc.ct_sns_dma;
	sp->u.iocb_cmd.u.ctarg.rsp = fcport->ct_desc.ct_sns;
	sp->u.iocb_cmd.u.ctarg.rsp_dma = fcport->ct_desc.ct_sns_dma;
	sp->u.iocb_cmd.u.ctarg.req_size = GFF_ID_REQ_SIZE;
	sp->u.iocb_cmd.u.ctarg.rsp_size = GFF_ID_RSP_SIZE;
	sp->u.iocb_cmd.u.ctarg.nport_handle = NPH_SNS;

	sp->done = qla24xx_async_gffid_sp_done;

	ql_dbg(ql_dbg_disc, vha, 0x2132,
	    "Async-%s hdl=%x  %8phC.\n", sp->name,
	    sp->handle, fcport->port_name);

	rval = qla2x00_start_sp(sp);
	if (rval != QLA_SUCCESS)
		goto done_free_sp;

	return rval;
done_free_sp:
	sp->free(sp);
	fcport->flags &= ~FCF_ASYNC_SENT;
	return rval;
}