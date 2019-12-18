#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_28__   TYPE_9__ ;
typedef  struct TYPE_27__   TYPE_8__ ;
typedef  struct TYPE_26__   TYPE_7__ ;
typedef  struct TYPE_25__   TYPE_6__ ;
typedef  struct TYPE_24__   TYPE_5__ ;
typedef  struct TYPE_23__   TYPE_4__ ;
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;
typedef  struct TYPE_19__   TYPE_17__ ;
typedef  struct TYPE_18__   TYPE_11__ ;

/* Type definitions */
typedef  size_t uint16_t ;
struct TYPE_26__ {scalar_t__ rsvd_1; } ;
struct TYPE_19__ {TYPE_7__ b; } ;
struct TYPE_27__ {TYPE_17__ d_id; int /*<<< orphan*/  fabric_port_name; } ;
typedef  TYPE_8__ sw_info_t ;
struct qla_hw_data {size_t max_fibre_devices; int /*<<< orphan*/  ms_iocb_dma; int /*<<< orphan*/  ms_iocb; TYPE_11__* ct_sns; TYPE_1__* isp_ops; int /*<<< orphan*/  ct_sns_dma; } ;
struct TYPE_24__ {int /*<<< orphan*/  port_name; } ;
struct TYPE_25__ {TYPE_5__ gfpn_id; } ;
struct ct_sns_rsp {TYPE_6__ rsp; } ;
struct TYPE_22__ {int /*<<< orphan*/  port_id; } ;
struct TYPE_23__ {TYPE_3__ port_id; } ;
struct ct_sns_req {TYPE_4__ req; } ;
struct ct_arg {int /*<<< orphan*/  nport_handle; int /*<<< orphan*/  rsp_size; int /*<<< orphan*/  req_size; int /*<<< orphan*/  rsp_dma; int /*<<< orphan*/  req_dma; int /*<<< orphan*/  iocb; } ;
struct TYPE_28__ {struct qla_hw_data* hw; } ;
typedef  TYPE_9__ scsi_qla_host_t ;
typedef  int /*<<< orphan*/  ms_iocb_entry_t ;
struct TYPE_21__ {struct ct_sns_rsp rsp; } ;
struct TYPE_20__ {int /*<<< orphan*/ * (* prep_ms_iocb ) (TYPE_9__*,struct ct_arg*) ;} ;
struct TYPE_18__ {TYPE_2__ p; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFPN_ID_CMD ; 
 int /*<<< orphan*/  GFPN_ID_REQ_SIZE ; 
 int /*<<< orphan*/  GFPN_ID_RSP_SIZE ; 
 int /*<<< orphan*/  IS_IIDMA_CAPABLE (struct qla_hw_data*) ; 
 int /*<<< orphan*/  NPH_SNS ; 
 int QLA_FUNCTION_FAILED ; 
 int QLA_SUCCESS ; 
 int /*<<< orphan*/  WWN_SIZE ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  port_id_to_be_id (TYPE_17__) ; 
 int /*<<< orphan*/  ql_dbg (int /*<<< orphan*/ ,TYPE_9__*,int,char*,int) ; 
 int /*<<< orphan*/  ql_dbg_disc ; 
 int qla2x00_chk_ms_status (TYPE_9__*,int /*<<< orphan*/ *,struct ct_sns_rsp*,char*) ; 
 int qla2x00_issue_iocb (TYPE_9__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct ct_sns_req* qla2x00_prep_ct_req (TYPE_11__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * stub1 (TYPE_9__*,struct ct_arg*) ; 

int
qla2x00_gfpn_id(scsi_qla_host_t *vha, sw_info_t *list)
{
	int		rval = QLA_SUCCESS;
	uint16_t	i;
	struct qla_hw_data *ha = vha->hw;
	ms_iocb_entry_t	*ms_pkt;
	struct ct_sns_req	*ct_req;
	struct ct_sns_rsp	*ct_rsp;
	struct ct_arg arg;

	if (!IS_IIDMA_CAPABLE(ha))
		return QLA_FUNCTION_FAILED;

	arg.iocb = ha->ms_iocb;
	arg.req_dma = ha->ct_sns_dma;
	arg.rsp_dma = ha->ct_sns_dma;
	arg.req_size = GFPN_ID_REQ_SIZE;
	arg.rsp_size = GFPN_ID_RSP_SIZE;
	arg.nport_handle = NPH_SNS;

	for (i = 0; i < ha->max_fibre_devices; i++) {
		/* Issue GFPN_ID */
		/* Prepare common MS IOCB */
		ms_pkt = ha->isp_ops->prep_ms_iocb(vha, &arg);

		/* Prepare CT request */
		ct_req = qla2x00_prep_ct_req(ha->ct_sns, GFPN_ID_CMD,
		    GFPN_ID_RSP_SIZE);
		ct_rsp = &ha->ct_sns->p.rsp;

		/* Prepare CT arguments -- port_id */
		ct_req->req.port_id.port_id = port_id_to_be_id(list[i].d_id);

		/* Execute MS IOCB */
		rval = qla2x00_issue_iocb(vha, ha->ms_iocb, ha->ms_iocb_dma,
		    sizeof(ms_iocb_entry_t));
		if (rval != QLA_SUCCESS) {
			/*EMPTY*/
			ql_dbg(ql_dbg_disc, vha, 0x2023,
			    "GFPN_ID issue IOCB failed (%d).\n", rval);
			break;
		} else if (qla2x00_chk_ms_status(vha, ms_pkt, ct_rsp,
		    "GFPN_ID") != QLA_SUCCESS) {
			rval = QLA_FUNCTION_FAILED;
			break;
		} else {
			/* Save fabric portname */
			memcpy(list[i].fabric_port_name,
			    ct_rsp->rsp.gfpn_id.port_name, WWN_SIZE);
		}

		/* Last device exit. */
		if (list[i].d_id.b.rsvd_1 != 0)
			break;
	}

	return (rval);
}